#include "TitleBar.h"


TitleBar::TitleBar(QWidget* parent)
        : QWidget(parent)
{
    setFixedHeight(30);
    setStyleSheet("background-color: #CCCCCC; color: #CCCCCC;");
}

void TitleBar::Initialize() noexcept {
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 0, 5, 0);
    auto iconLabel = createIconLabel();
    auto settingBtn = createSettingBtn();
    auto minimizeBtn = createMinimizeBtn();
    auto maximizeBtn = createMaximizeBtn();
    auto closeBtn = createCloseBtn();

    layout->addWidget(iconLabel);
    layout->addStretch();
    layout->addWidget(settingBtn);
    layout->addWidget(minimizeBtn);
    layout->addWidget(maximizeBtn);
    layout->addWidget(closeBtn);

    connect(settingBtn, &QPushButton::clicked, this, &TitleBar::requestSetting);
    connect(minimizeBtn, &QPushButton::clicked, this, &TitleBar::requestMinimize);
    connect(maximizeBtn, &QPushButton::clicked, this, &TitleBar::toggleMaximizeRestore);
    connect(closeBtn, &QPushButton::clicked, this, &TitleBar::requestClose);
}

QLabel *TitleBar::createIconLabel() noexcept {
    auto iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(":/icons/aspect-ratio(1).svg").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setFixedSize(24, 24);
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
    minimizeBtn->setIcon(QIcon(":/icons/arrows-minimize.svg"));
    minimizeBtn->setIconSize(QSize(16, 16));
    minimizeBtn->setFlat(true);
    minimizeBtn->setFixedSize(24, 24);
    minimizeBtn->setStyleSheet(
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
    return minimizeBtn;
}

QPushButton *TitleBar::createMaximizeBtn() noexcept {
    m_maximizeBtn = new QPushButton(this);
    m_maximizeBtn->setIcon(QIcon(":/icons/arrows-maximize.svg"));
    m_maximizeBtn->setIconSize(QSize(16, 16));
    m_maximizeBtn->setFlat(true);
    m_maximizeBtn->setFixedSize(24, 24);
    m_maximizeBtn->setStyleSheet(
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
    return m_maximizeBtn;
}

QPushButton *TitleBar::createCloseBtn() noexcept {
    auto closeBtn = new QPushButton(this);
    closeBtn->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    closeBtn->setIconSize(QSize(16, 16));
    closeBtn->setFlat(true);
    closeBtn->setFixedSize(24, 24);
    closeBtn->setStyleSheet(
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
    return closeBtn;
}

void TitleBar::toggleMaximizeRestore() noexcept {
    QWidget* win = window(); // 获取顶层窗口

    if (win->isMaximized()) {
        win->showNormal();
        m_maximizeBtn->setIcon(QIcon(":/icons/arrows-maximize.svg")); // 还原图标
    } else {
        win->showMaximized();
        m_maximizeBtn->setIcon(QIcon(":/icons/aspect-ratio.svg")); // 最大化图标替换为还原图标
    }
}