#include "explorer.h"

Explorer::Explorer(QWidget* parent)
    : QWidget(parent),
      m_leftSidebarList(new QListWidget(this)),
      m_leftStackedWidget(new QStackedWidget(this))
{

}

void Explorer::Initialize(QHBoxLayout* sidebarLayout) noexcept {
    // 初始化控件
//    m_leftSidebarList->setFixedWidth(48);
//    m_leftSidebarList->setIconSize(QSize(24, 24));
//    m_leftSidebarList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    m_leftSidebarList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);


    addSidebarPage("📁", createExplorerTree());
    addSidebarPage("🔍", new QLabel("Search View"));
    addSidebarPage("Git", new QLabel("Git View"));
    addSidebarPage("💡", new QLabel("Other View"));

//    sidebarLayout->addWidget(m_leftSidebarList);
    sidebarLayout->addWidget(m_leftStackedWidget);

//    m_leftSidebarList->setMinimumWidth(48);
//    m_leftStackedWidget->setMinimumWidth(48);

    m_leftStackedWidget->setCurrentIndex(0);

//    connect(m_leftSidebarList, &QListWidget::currentRowChanged,
//            m_leftStackedWidget, &QStackedWidget::setCurrentIndex);
//
//    connect(
//        static_cast<QTreeWidget*>(m_leftStackedWidget->currentWidget()),
//        &QTreeWidget::itemDoubleClicked,
//        this,
//        &Explorer::onItemClicked
//    );
}

void Explorer::addSidebarPage(const QString& iconText, QWidget* widget) noexcept {
//    auto* item = new QListWidgetItem(iconText);
//    item->setTextAlignment(Qt::AlignHCenter);
//    m_leftSidebarList->addItem(item);
    m_leftStackedWidget->addWidget(widget);
}

void Explorer::addSidebarPage(const QIcon& icon, const QString& tooltip, QWidget* widget) noexcept {
    auto* item = new QListWidgetItem();
    item->setIcon(icon);
    item->setToolTip(tooltip);
    item->setTextAlignment(Qt::AlignHCenter);
    item->setText("");
    m_leftSidebarList->addItem(item);
    m_leftStackedWidget->addWidget(widget);
}

void Explorer::populateTreeFromDirectory(const QString& path, QTreeWidgetItem* parent) {
    QDir dir(path);
    if (!dir.exists()) {
        qWarning() << "Directory not found:" << path; // 路径检查
        return;
    }

    QFileInfoList entries = dir.entryInfoList(
            QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs | QDir::NoSymLinks
    );

    for (const QFileInfo& info : entries) {
        QTreeWidgetItem* item = new QTreeWidgetItem(parent);
        item->setText(0, info.fileName());

        // 设置图标
        QFileIconProvider iconProvider;
        item->setIcon(0, iconProvider.icon(info));
        item->setData(0, Qt::UserRole, QVariant::fromValue(info));

        qDebug() << "Added:" << info.filePath()
                 << "Type:" << (info.isFile() ? "File" : "Directory");

        if (info.isDir()) {
            populateTreeFromDirectory(info.filePath(), item);
        }
    }
}

QTreeWidget* Explorer::createExplorerTree() noexcept {
    auto* explorer = new QTreeWidget();
    explorer->setHeaderLabel("EXPLORER");
    explorer->setColumnCount(1);

    QTreeWidgetItem* rootNode = new QTreeWidgetItem(explorer);
    rootNode->setText(0, m_rootPath);
    rootNode->setIcon(0, QFileIconProvider().icon(QFileIconProvider::Folder));

    populateTreeFromDirectory(m_rootPath, rootNode);

    //explorer->expandAll();

    return explorer;
}

QString Explorer::GetRootPath() const noexcept {
    return m_rootPath;
}

void Explorer::SetRootPath(const QString &rootPath) noexcept {
    m_rootPath = rootPath;
}

void Explorer::loadNewPath(const QString& newPath) noexcept {
    SetRootPath(newPath);

    QTreeWidget* currentTree = qobject_cast<QTreeWidget*>(m_leftStackedWidget->currentWidget());
    if (!currentTree) {
        qWarning() << "No valid tree widget found!";
        return;
    }

    // 清空当前树内容
    currentTree->clear();

    // 创建新的根节点
    QTreeWidgetItem* newRoot = new QTreeWidgetItem(currentTree);
    newRoot->setText(0, m_rootPath);
    newRoot->setIcon(0, QFileIconProvider().icon(QFileIconProvider::Folder));

    // 填充子节点
    populateTreeFromDirectory(m_rootPath, newRoot);
}

void Explorer::onItemClicked(QTreeWidgetItem *item, int colum) {
    QFileInfo fileInfo = item->data(0, Qt::UserRole).value<QFileInfo>();

    if (fileInfo.isFile()) {
        QString filePath = fileInfo.absoluteFilePath();

        FileViewer* viewer = new FileViewer(filePath, this);
        viewer->show();
    }
}

void Explorer::SetCurrentIndex(int index) noexcept {
    if (index >= 0 && index < m_leftStackedWidget->count())
        m_leftStackedWidget->setCurrentIndex(index);
}