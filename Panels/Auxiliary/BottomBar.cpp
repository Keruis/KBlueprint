#include "BottomBar.h"

BottomBar::BottomBar(QWidget *parent)
    : QWidget(parent)
{

}

BottomBar::~BottomBar() {

}

void BottomBar::Initialize() noexcept {
    this->setFixedHeight(20);

    QHBoxLayout* bottomLayout = new QHBoxLayout(this);
    bottomLayout->setContentsMargins(8, 0, 8, 0);
    bottomLayout->setSpacing(8);

    setupStatusBar();
    setupResourceMonitor();
    update();
}

void BottomBar::setupStatusBar() noexcept {
    QWidget* statusBar = new QWidget;
    QHBoxLayout* statusLayout = new QHBoxLayout(statusBar);
    statusLayout->setContentsMargins(4, 2, 4, 2);
    statusLayout->setSpacing(8);

    m_pathLabel = new QLabel("Path: /your/project/path");
    m_cpuLabel = new QLabel("CPU: 0%");
    m_memLabel = new QLabel("Memory: 0 MB");

    statusLayout->addWidget(m_pathLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(m_cpuLabel);
    statusLayout->addWidget(m_memLabel);
    layout()->addWidget(statusBar);
}

void BottomBar::setupResourceMonitor() noexcept {
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        double cpuUsage = m_cpuUsage.GetCPUUsage();
        double memUsage = m_cpuUsage.GetMemoryUsageMB();
        m_cpuLabel->setText(QString("CPU: %1%").arg(cpuUsage, 0, 'f', 1));
        m_memLabel->setText(QString("Memory: %1 MB").arg(memUsage, 0, 'f', 1));
    });
    timer->start(1000);
}

void BottomBar::SetPath(const QString &path) noexcept {
    if (m_pathLabel) {
        m_pathLabel->setText(path);
    }
}

void BottomBar::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(QColor(255, 255, 255, 60));
    pen.setWidth(1);

    painter.setPen(pen);

    painter.drawLine(rect().left(), rect().top(), rect().right(), rect().top());
}

