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

    connect(m_treeWidget, &QTreeWidget::itemDoubleClicked, this, &Explorer::onItemClicked);

    m_treeWidget->setStyleSheet(R"(
        QTreeWidget {
            background-color: rgba(0, 0, 0, 0);
        }

        QScrollBar:vertical {
            background: rgba(45, 45, 45, 100);  /* 半透明背景 */
            width: 8px;
            border: none;
        }

        QScrollBar::handle:vertical {
            background: rgba(85, 85, 85, 180);  /* 滚动块更明显 */
            min-height: 20px;
            border-radius: 0;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: transparent;
            border: none;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0px;
            subcontrol-origin: margin;
        }

        QScrollBar:horizontal {
            background: #2d2d2d;
            height: 8px;
            margin: 0px 0px 0px 0px;
            border: none;
        }
        QScrollBar::handle:horizontal {
            background: #555;
            min-width: 20px;
            border-radius: 0px;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 0px;
            subcontrol-origin: margin;
        }
    )");
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

    m_treeWidget = new QTreeWidget();
    m_treeWidget->setHeaderHidden(true);
    m_treeWidget->setColumnCount(1);
    m_treeWidget->installEventFilter(this);
    m_treeWidget->setStyleSheet(R"(
        QTreeWidget {
            background-color: rgba(0, 0, 0, 0);
        }

        QScrollBar:vertical {
            background: rgba(45, 45, 45, 100);  /* 半透明背景 */
            width: 8px;
            border: none;
        }

        QScrollBar::handle:vertical {
            background: rgba(85, 85, 85, 180);  /* 滚动块更明显 */
            min-height: 20px;
            border-radius: 0;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: transparent;
            border: none;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0px;
            subcontrol-origin: margin;
        }

        QScrollBar:horizontal {
            background: #2d2d2d;
            height: 8px;
            margin: 0px 0px 0px 0px;
            border: none;
        }
        QScrollBar::handle:horizontal {
            background: #555;
            min-width: 20px;
            border-radius: 0px;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 0px;
            subcontrol-origin: margin;
        }
    )");

    auto* rootNode = new QTreeWidgetItem(m_treeWidget);
    rootNode->setText(0, m_rootPath);
    rootNode->setIcon(0, QFileIconProvider().icon(QFileIconProvider::Folder));

    populateTreeFromDirectory(m_rootPath, rootNode);

    connect(m_header, &ExplorerHeader::expandRequested, m_treeWidget, &QTreeWidget::expandAll);
    connect(m_header, &ExplorerHeader::collapseRequested, m_treeWidget, &QTreeWidget::collapseAll);

    layout->addWidget(m_header);
    layout->addWidget(m_treeWidget);

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

    currentTree->clear();

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