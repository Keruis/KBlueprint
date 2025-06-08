#include "TitleBar.h"


TitleBar::TitleBar(QWidget* parent)
        : QWidget(parent)
{
    setFixedHeight(30);
    applyStyleSheetFromFile(":/darkstyle.qss");
}

void TitleBar::Initialize() noexcept {
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(12);

    layout->addWidget(createIconLabel());
    layout->addSpacing(10);

    createMenuButtons(layout);
    layout->addStretch();
    createWindowControlButtons(layout);
}

void TitleBar::applyStyleSheetFromFile(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QFile::ReadOnly)) {
        QString style = QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}

void TitleBar::createMenuButtons(QHBoxLayout* layout) {
    struct MenuItem {
        QString name;
        QMenu* (TitleBar::*menuCreator)();
    };

    std::vector<MenuItem> items = {
            {"文件", &TitleBar::createFileMenu},
            {"编辑", &TitleBar::createEditMenu},
            {"视图", &TitleBar::createViewerMenu},
            {"导航", &TitleBar::createNavMenu},
            {"帮助", &TitleBar::createHelpMenu}
    };

    for (const auto& item : items) {
        QToolButton* btn = new QToolButton(this);
        btn->setText(item.name);
        btn->setPopupMode(QToolButton::InstantPopup);
        btn->setMenu((this->*item.menuCreator)());
        layout->addWidget(btn);
    }
}

QMenu* TitleBar::createFileMenu() {
    auto menu = new QMenu(this);
    menu->addAction("新建文件", this, []() { qDebug() << "[文件] -> 新建文件"; });
    menu->addAction("打开文件", this, []() { qDebug() << "[文件] -> 打开文件"; });
    menu->addSeparator();
    menu->addAction("保存", this, []() { qDebug() << "[文件] -> 保存"; });
    menu->addAction("另存为", this, []() { qDebug() << "[文件] -> 另存为"; });
    menu->addSeparator();
    menu->addAction("退出", this, []() { qDebug() << "[文件] -> 退出"; qApp->quit(); });
    return menu;
}

QMenu* TitleBar::createEditMenu() {
    auto menu = new QMenu(this);
    menu->addAction("复制", this, []() { qDebug() << "[编辑] -> 复制"; });
    menu->addAction("粘贴", this, []() { qDebug() << "[编辑] -> 粘贴"; });
    menu->addAction("剪切", this, []() { qDebug() << "[编辑] -> 剪切"; });
    return menu;
}

QMenu* TitleBar::createViewerMenu() {
    auto menu = new QMenu(this);
    menu->addAction("放大", this, []() { qDebug() << "[视图] -> 放大"; });
    menu->addAction("缩小", this, []() { qDebug() << "[视图] -> 缩小"; });
    menu->addAction("全屏", this, []() { qDebug() << "[视图] -> 全屏"; });
    return menu;
}

QMenu* TitleBar::createNavMenu() {
    auto menu = new QMenu(this);
    menu->addAction("转到定义", this, []() { qDebug() << "[导航] -> 转到定义"; });
    menu->addAction("跳转到行", this, []() { qDebug() << "[导航] -> 跳转到行"; });
    return menu;
}

QMenu* TitleBar::createHelpMenu() {
    auto menu = new QMenu(this);
    menu->addAction("文档", this, []() { qDebug() << "[帮助] -> 文档"; });
    menu->addAction("关于", this, []() { qDebug() << "[帮助] -> 关于"; });
    return menu;
}

void TitleBar::createWindowControlButtons(QHBoxLayout* layout) {
    auto settingBtn = createSettingBtn();
    auto minimizeBtn = createMinimizeBtn();
    auto maximizeBtn = createMaximizeBtn();
    auto closeBtn = createCloseBtn();

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
            "   background-color: #505050;"
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
            "   background-color: #505050;"
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
            "   background-color: #505050;"
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
            "   background-color: #505050;"
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