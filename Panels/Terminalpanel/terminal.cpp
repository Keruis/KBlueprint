#include "terminal.h"

Terminal::Terminal(QWidget *parent)
    : QWidget(parent)
{

}

void Terminal::Initialize() noexcept {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 顶部标题栏
    QLabel* title = new QLabel("Terminal");
    title->setFixedHeight(24);
    layout->addWidget(title);

    // 终端输出区域
    m_terminalOutput = new QPlainTextEdit;
    m_terminalOutput->setReadOnly(true);
    m_terminalOutput->setPlaceholderText("Terminal output here...");
    m_terminalOutput->setStyleSheet(
//            "background-color: transparent;"
            "color: white;"
            "font-family: Consolas;"
            );

    QWidget* terminalContainer = new QWidget;
    QVBoxLayout* terminalContainerLayout = new QVBoxLayout(terminalContainer);
    terminalContainerLayout->setContentsMargins(12, 6, 12, 6);
    terminalContainerLayout->setSpacing(0);
    terminalContainerLayout->addWidget(m_terminalOutput);

    layout->addWidget(terminalContainer);

    // 底部状态栏
    QWidget* statusBar = new QWidget;
    QHBoxLayout* statusLayout = new QHBoxLayout(statusBar);
    statusLayout->setContentsMargins(4, 2, 4, 2);
    statusLayout->setSpacing(8);

    m_pathLabel = new QLabel("Path: /your/project/path");
    m_cpuLabel = new QLabel("CPU: 0%");
    m_memLabel = new QLabel("Memory: %1 MB");

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=, this]() {
        double cpuUsage = m_cpuUsage.GetCPUUsage();
        double memUsage = m_cpuUsage.GetMemoryUsageMB();
        m_cpuLabel->setText(QString("CPU: %1%").arg(cpuUsage, 0, 'f', 1));
        m_memLabel->setText(QString("Memory: %1 MB").arg(memUsage, 0, 'f', 1));
    });
    timer->start(1000);


    statusLayout->addWidget(m_pathLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(m_cpuLabel);
    statusLayout->addWidget(m_memLabel);

    layout->addWidget(statusBar);

    this->setMinimumHeight(120);
    m_terminalOutput->setMinimumHeight(80);
}