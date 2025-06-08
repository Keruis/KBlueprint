#include "explorer.h"

Explorer::Explorer(QWidget* parent)
    : QWidget(parent),
      m_leftStackedWidget(new QStackedWidget(this)),
      m_fileViewer(new FileViewer(this)),
      m_header(new ExplorerHeader(this))
{
    this->installEventFilter(this);
}

void Explorer::Initialize(QHBoxLayout* sidebarLayout) noexcept {
    // 初始化控件
    addSidebarPage(createExplorerTree());
    addSidebarPage(new QLabel("audio View"));
    addSidebarPage(new QLabel("blueprint View"));
    addSidebarPage(new QLabel("Other View"));

    sidebarLayout->addWidget(m_leftStackedWidget);

    m_leftStackedWidget->setCurrentIndex(0);

    connect(
        static_cast<QTreeWidget*>(m_leftStackedWidget->currentWidget()),
        &QTreeWidget::itemDoubleClicked,
        this,
        &Explorer::onItemClicked
    );
}

void Explorer::addSidebarPage(QWidget* widget) noexcept {
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

QWidget* Explorer::createExplorerTree() noexcept {
    auto* container = new QWidget(this);
    auto* layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_header->setButtonsVisible(false);
    m_header->installEventFilter(this);

    auto* explorer = new QTreeWidget();
    explorer->setHeaderHidden(true);
    explorer->setColumnCount(1);
    explorer->installEventFilter(this);

    auto* rootNode = new QTreeWidgetItem(explorer);
    rootNode->setText(0, m_rootPath);
    rootNode->setIcon(0, QFileIconProvider().icon(QFileIconProvider::Folder));

    populateTreeFromDirectory(m_rootPath, rootNode);

    connect(m_header, &ExplorerHeader::expandRequested, explorer, &QTreeWidget::expandAll);
    connect(m_header, &ExplorerHeader::collapseRequested, explorer, &QTreeWidget::collapseAll);

    layout->addWidget(m_header);
    layout->addWidget(explorer);

    return container;
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

        m_fileViewer->openFile(filePath);
        qDebug() << "clicked file : " << filePath;
    }

    emit openFile();
}

void Explorer::SetCurrentIndex(int index) noexcept {
    if (index >= 0 && index < m_leftStackedWidget->count())
        m_leftStackedWidget->setCurrentIndex(index);
}

FileViewer *Explorer::GetFileViewer() noexcept {
    return m_fileViewer;
}