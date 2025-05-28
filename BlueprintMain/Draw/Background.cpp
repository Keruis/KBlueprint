#include "Background.h"

void BlueprintBackground::DrawBackground(QPainter *painter, const QRectF &rect) noexcept {
    // 绘制网格背景
    QPen lightPen(QColor(60, 60, 60), 1);  // 浅色网格线
    QPen darkPen(QColor(25, 25, 25), 2);   // 深色网格线

    // 获取当前视图的矩形区域
    QRectF viewRect = rect;

    // 绘制小网格线
    painter->setPen(lightPen);
    for (qreal x = std::floor(viewRect.left() / m_gridSize) * m_gridSize; x < viewRect.right(); x += m_gridSize) {
        painter->drawLine(QLineF(x, viewRect.top(), x, viewRect.bottom()));
    }
    for (qreal y = std::floor(viewRect.top() / m_gridSize) * m_gridSize; y < viewRect.bottom(); y += m_gridSize) {
        painter->drawLine(QLineF(viewRect.left(), y, viewRect.right(), y));
    }

    // 绘制大网格线（每隔5个小网格）
    painter->setPen(darkPen);
    for (qreal x = std::floor(viewRect.left() / (m_gridSize * 5)) * (m_gridSize * 5); x < viewRect.right(); x += m_gridSize * 5) {
        painter->drawLine(QLineF(x, viewRect.top(), x, viewRect.bottom()));
    }
    for (qreal y = std::floor(viewRect.top() / (m_gridSize * 5)) * (m_gridSize * 5); y < viewRect.bottom(); y += m_gridSize * 5) {
        painter->drawLine(QLineF(viewRect.left(), y, viewRect.right(), y));
    }
}

int BlueprintBackground::GetGridSize() noexcept {
    return m_gridSize;
}

void BlueprintBackground::SetGridSize(int gridSize) noexcept {
    m_gridSize = gridSize;
}
