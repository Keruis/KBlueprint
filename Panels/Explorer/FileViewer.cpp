#include "FileViewer.h"
#include <QVBoxLayout>
#include <QFile>
#include <QFileInfo>

FileViewer::FileViewer(QWidget* parent)
        : QWidget(parent), m_tabWidget(new QTabWidget(this)) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tabWidget);

    m_tabWidget->setTabsClosable(true);

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
