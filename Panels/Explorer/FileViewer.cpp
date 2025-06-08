#include "FileViewer.h"
#include <QVBoxLayout>
#include <QFile>
#include <QFileInfo>

FileViewer::FileViewer(QWidget* parent)
        : QWidget(parent),
        m_tabWidget(new QTabWidget(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tabWidget);

    m_tabWidget->setTabsClosable(true);
    m_tabWidget->setDocumentMode(true); // 更扁平的外观
    m_tabWidget->setMovable(true);      // 可拖动 tab

    m_tabWidget->setStyleSheet(R"(
    QTabBar::tab {
        background: #2d2d2d;
        color: #cccccc;
        padding: 6px 12px;
        border: 1px solid #444;
        border-bottom: none;
        border-radius: 4px 4px 0 0;
        margin-right: 1px;
    }
    QTabBar::tab:selected {
        background: #1e1e1e;
        color: white;
        font-weight: bold;
    }
    QTabBar::tab:hover {
        background: #3d3d3d;
    }
    QTabWidget::pane {
        border: 1px solid #444;
        top: -1px;
    }
)");

    connect(m_tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
        QString filePath = m_openedFiles.key(static_cast<QTextEdit*>(m_tabWidget->widget(index)));
        if (!filePath.isEmpty()) {
            closeFile(filePath);
        }
    });
}

FileViewer::~FileViewer() {
    m_openedFiles.clear();
}

void FileViewer::openFile(const QString& filePath) {
    if (m_openedFiles.contains(filePath)) {
        m_tabWidget->setCurrentWidget(m_openedFiles[filePath]);
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextEdit* editor = new QTextEdit;
    editor->setReadOnly(true);
    editor->setPlainText(QString::fromUtf8(file.readAll()));
    file.close();

    QFileInfo info(filePath);
    m_tabWidget->addTab(editor, info.fileName());
    m_tabWidget->setCurrentWidget(editor);
    m_tabWidget->setTabToolTip(m_tabWidget->indexOf(editor), filePath);

    m_openedFiles[filePath] = editor;
}

void FileViewer::closeFile(const QString& filePath) {
    if (!m_openedFiles.contains(filePath))
        return;

    QTextEdit* editor = m_openedFiles[filePath];
    int index = m_tabWidget->indexOf(editor);

    if (index != -1) {
        m_tabWidget->removeTab(index);
    }

    m_openedFiles.remove(filePath);
    delete editor;
}

void FileViewer::closeCurrentFile() {
    int index = m_tabWidget->currentIndex();
    if (index != -1) {
        QString filePath = m_openedFiles.key(static_cast<QTextEdit*>(m_tabWidget->widget(index)));
        closeFile(filePath);
    }
}

bool FileViewer::hasFile(const QString& filePath) const {
    return m_openedFiles.contains(filePath);
}
