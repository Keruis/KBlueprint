#include "RadialMenu.h"

RadialMenu::RadialMenu(QWidget* parent)
    : QWidget(parent),
      m_radius(100),
      m_innerRadius(40),
      m_segmentCount(5)
{
    setWindowFlags(Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(m_radius * 2, m_radius * 2);
    setMouseTracking(true);
}

void RadialMenu::paintEvent(QPaintEvent *) {
    setCursor(Qt::BlankCursor);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int gapAngle = 5;
    const int spanAngle = (360 / m_segmentCount) - gapAngle;
    int angle = 0;

    for (int i = 0; i < m_segmentCount; ++i) {
        QPainterPath path;
        path.moveTo(rect().center());

        QRectF outerRect(0, 0, width(), height());
        QRectF innerRect(
                width()/2 - m_innerRadius,
                height()/2 - m_innerRadius,
                m_innerRadius * 2,
                m_innerRadius * 2
        );

        path.arcMoveTo(outerRect, angle);
        path.arcTo(outerRect, angle, spanAngle);
        path.arcTo(innerRect, angle + spanAngle, -spanAngle);
        path.closeSubpath();

        QColor color = (i == m_hoveredIndex)
                       ? QColor(180, 180, 180)  // 高亮灰
                       : QColor(100, 100, 100); // 默认灰
        painter.setBrush(color);
        painter.drawPath(path);

        angle += spanAngle + gapAngle;
    }
}

void RadialMenu::mousePressEvent(QMouseEvent *event) {
    if (m_hoveredIndex != -1) {
        emit segmentClicked(m_hoveredIndex);
        close();
        deleteLater();
    }
    close();
    deleteLater();
}

void RadialMenu::mouseMoveEvent(QMouseEvent *event) {
    QTimer* m_hoverTimer = new QTimer(this);
    connect(m_hoverTimer, &QTimer::timeout, this, &RadialMenu::updateHoveredByDirection);
    m_hoverTimer->start(16);
}

void RadialMenu::closeEvent(QCloseEvent *event) {
    unsetCursor();
    QWidget::closeEvent(event);
}

void RadialMenu::updateHoveredByDirection() {
    QPoint globalMousePos = QCursor::pos();
    QPoint globalCenter = mapToGlobal(rect().center()); // 把本地中心点转成全局坐标

    QPointF delta = globalMousePos - globalCenter;

    if (delta.manhattanLength() < 5) {
        m_hoveredIndex = -1;
        update();
        return;
    }

    double angle = std::atan2(-delta.y(), delta.x()) * 180 / M_PI;
    if (angle < 0) angle += 360;

    qDebug() << "鼠标角度:" << angle;

    int index = getHoveredSegmentFromAngle(angle);
    if (index != m_hoveredIndex) {
        m_hoveredIndex = index;
        update();
    }
}

int RadialMenu::getHoveredSegmentFromAngle(double angle) const {
    const int totalSegments = m_segmentCount;
    const int gapAngle = 5;
    const int spanAngle = (360 / totalSegments) - gapAngle;
    const int fullSpan = spanAngle + gapAngle;

    for (int i = 0; i < totalSegments; ++i) {
        int startAngle = i * fullSpan;
        int endAngle = startAngle + spanAngle;

        // 处理跨 360° 情况
        if (startAngle <= angle && angle < endAngle)
            return i;
        else if (endAngle > 360 && angle < (endAngle - 360))
            return i;
    }

    return -1; // 未命中任何 segment
}