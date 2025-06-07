#include "TitleBar.h"


TitleBar::TitleBar(QWidget* parent)
        : QWidget(parent)
{
    setFixedHeight(30);
    setStyleSheet("background-color: #FFFFFF; color: #FFFFFF;");
}

void TitleBar::Initialize() noexcept {
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(12); // 控制整体间距

    auto iconLabel = createIconLabel();

    // 创建菜单按钮
    auto fileBtn = new QPushButton("文件", this);
    auto editBtn = new QPushButton("编辑", this);
    auto viewBtn = new QPushButton("视图", this);
    auto navBtn  = new QPushButton("导航", this);
    auto helpBtn = new QPushButton("帮助", this);

    // 设置统一样式
    auto style = QString(
            "QPushButton {"
            "   border: none;"
            "   background-color: transparent;"
            "   color: white;"
            "   font-weight: bold;"
            "   padding: 0 6px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #5A5A5A;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #3A3A3A;"
            "}"
    );

    fileBtn->setStyleSheet(style);
    editBtn->setStyleSheet(style);
    viewBtn->setStyleSheet(style);
    navBtn->setStyleSheet(style);
    helpBtn->setStyleSheet(style);

    // 创建右侧按钮
    auto settingBtn = createSettingBtn();
    auto minimizeBtn = createMinimizeBtn();
    auto maximizeBtn = createMaximizeBtn();
    auto closeBtn = createCloseBtn();

    // 添加控件到布局
    layout->addWidget(iconLabel);

    // 添加菜单按钮
    layout->addSpacing(10); // 图标与菜单间距
    layout->addWidget(fileBtn);
    layout->addWidget(editBtn);
    layout->addWidget(viewBtn);
    layout->addWidget(navBtn);
    layout->addWidget(helpBtn);

    layout->addStretch(); // 推动右边按钮到最右侧

    // 添加右侧控制按钮
    layout->addWidget(settingBtn);
    layout->addWidget(minimizeBtn);
    layout->addWidget(maximizeBtn);
    layout->addWidget(closeBtn);

    // 信号连接
    connect(settingBtn, &QPushButton::clicked, this, &TitleBar::requestSetting);
    connect(minimizeBtn, &QPushButton::clicked, this, &TitleBar::requestMinimize);
    connect(maximizeBtn, &QPushButton::clicked, this, &TitleBar::toggleMaximizeRestore);
    connect(closeBtn, &QPushButton::clicked, this, &TitleBar::requestClose);
}

QLabel *TitleBar::createIconLabel() noexcept {
    auto iconLabel = new QLabel(this);

    QPixmap pixmap(":/icons/titleIcon.png");
    iconLabel->setPixmap(pixmap.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedSize(30, 30);

    iconLabel->setAttribute(Qt::WA_TranslucentBackground);
    iconLabel->setStyleSheet("background: transparent;");

    return iconLabel;
}

QPushButton *TitleBar::createSettingBtn() noexcept {
    auto settingBtn = new QPushButton(this);
    settingBtn->setIcon(QIcon(":/icons/settings.svg"));
    settingBtn->setIconSize(QSize(20, 20));
    settingBtn->setFlat(true);
    settingBtn->setFixedSize(24, 24);
    settingBtn->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background-color: transparent;"
            "   border-radius: 5px;"
            "}"

            "QPushButton:hover {"
            "   background-color: #5A5A5A;"
            "}"

            "QPushButton:pressed {"
            "   background-color: #3A3A3A;"
            "}"
    );
    return settingBtn;
}

QPushButton *TitleBar::createMinimizeBtn() noexcept {
    auto minimizeBtn = new QPushButton(this);
    minimizeBtn->setIcon(QIcon(":/icons/minimize.svg"));
    minimizeBtn->setIconSize(QSize(20, 20));
    minimizeBtn->setFlat(true);
    minimizeBtn->setFixedSize(24, 24);
    minimizeBtn->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background-color: transparent;"
            "   border-radius: 12px;"
            "}"

            "QPushButton:hover {"
            "   background-color: #5A5A5A;"
            "}"

            "QPushButton:pressed {"
            "   background-color: #3A3A3A;"
            "}"
    );
    return minimizeBtn;
}

QPushButton *TitleBar::createMaximizeBtn() noexcept {
    m_maximizeBtn = new QPushButton(this);
    m_maximizeBtn->setIcon(QIcon(":/icons/maximize.svg"));
    m_maximizeBtn->setIconSize(QSize(20, 20));
    m_maximizeBtn->setFlat(true);
    m_maximizeBtn->setFixedSize(24, 24);
    m_maximizeBtn->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background-color: transparent;"
            "   border-radius: 12px;"
            "}"

            "QPushButton:hover {"
            "   background-color: #5A5A5A;"
            "}"

            "QPushButton:pressed {"
            "   background-color: #3A3A3A;"
            "}"
    );
    return m_maximizeBtn;
}

QPushButton *TitleBar::createCloseBtn() noexcept {
    auto closeBtn = new QPushButton(this);
    closeBtn->setIcon(QIcon(":/icons/close.svg"));
    closeBtn->setIconSize(QSize(20, 20));
    closeBtn->setFlat(true);
    closeBtn->setFixedSize(24, 24);
    closeBtn->setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   background-color: transparent;"
            "   border-radius: 12px;"
            "}"

            "QPushButton:hover {"
            "   background-color: #5A5A5A;"
            "}"

            "QPushButton:pressed {"
            "   background-color: #3A3A3A;"
            "}"
    );
    return closeBtn;
}

void TitleBar::toggleMaximizeRestore() noexcept {
    QWidget* win = window(); // 获取顶层窗口

    if (win->isMaximized()) {
        win->showNormal();
        m_maximizeBtn->setIcon(QIcon(":/icons/maximize.svg")); // 还原图标
    } else {
        win->showMaximized();
        m_maximizeBtn->setIcon(QIcon(":/icons/restore.svg")); // 最大化图标替换为还原图标
    }
}

void TitleBar::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor("#5A5A5A"));
    QWidget::paintEvent(event);
}