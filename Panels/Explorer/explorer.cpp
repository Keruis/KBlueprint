#include "explorer.h"

Explorer::Explorer(QWidget* parent)
    : QWidget(parent),
      m_leftSidebarList(new QListWidget(this)),
      m_leftStackedWidget(new QStackedWidget(this))
{

}

void Explorer::Initialize(QHBoxLayout* sidebarLayout) noexcept {
    // 初始化控件
    m_leftSidebarList->setFixedWidth(48);
    m_leftSidebarList->setIconSize(QSize(24, 24));
    m_leftSidebarList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_leftSidebarList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);


    addSidebarPage("📁", createExplorerTree());
    addSidebarPage("🔍", new QLabel("Search View"));
    addSidebarPage("Git", new QLabel("Git View"));
    addSidebarPage("💡", new QLabel("Other View"));

    sidebarLayout->addWidget(m_leftSidebarList);
    sidebarLayout->addWidget(m_leftStackedWidget);

    m_leftSidebarList->setMinimumWidth(48);
    m_leftStackedWidget->setMinimumWidth(48);


    connect(m_leftSidebarList, &QListWidget::currentRowChanged,
            m_leftStackedWidget, &QStackedWidget::setCurrentIndex);
}

void Explorer::addSidebarPage(const QString& iconText, QWidget* widget) noexcept {
    auto* item = new QListWidgetItem(iconText);
    item->setTextAlignment(Qt::AlignHCenter);
    m_leftSidebarList->addItem(item);
    m_leftStackedWidget->addWidget(widget);
}

void Explorer::addSidebarPage(const QIcon& icon, const QString& tooltip, QWidget* widget) noexcept {
    auto* item = new QListWidgetItem();
    item->setIcon(icon);
    item->setToolTip(tooltip); // 鼠标悬停可见
    item->setTextAlignment(Qt::AlignHCenter);
    item->setText(""); // 不显示文字，只显示图标
    m_leftSidebarList->addItem(item);
    m_leftStackedWidget->addWidget(widget);
}

QTreeWidget* Explorer::createExplorerTree() noexcept {
    auto* explorer = new QTreeWidget();
    explorer->setHeaderLabel("EXPLORER");

    auto src = new QTreeWidgetItem(explorer);
    src->setText(0, "📁 src");
    src->addChild(new QTreeWidgetItem(QStringList("📄 main.js")));
    src->addChild(new QTreeWidgetItem(QStringList("📄 utils.js")));

    auto pub = new QTreeWidgetItem(explorer);
    pub->setText(0, "📁 public");
    pub->addChild(new QTreeWidgetItem(QStringList("📄 index.html")));
    pub->addChild(new QTreeWidgetItem(QStringList("📄 style.css")));

    explorer->addTopLevelItem(src);
    explorer->addTopLevelItem(pub);
    explorer->addTopLevelItem(new QTreeWidgetItem(QStringList("📄 README.md")));

    return explorer;
}

