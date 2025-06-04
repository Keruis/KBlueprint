#include "FileViewer.h"

FileViewer::FileViewer(const QString& filePath, QWidget* parent)
        : QWidget(parent), m_textEdit(new QTextEdit(this)) {

    setWindowTitle(QFileInfo(filePath).fileName());
    setWindowFlags(windowFlags() | Qt::Window);
    setMinimumSize(600, 400);

    setParent(parent);
    setAttribute(Qt::WA_DeleteOnClose);

    // 布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_textEdit);

    // 读取文件内容
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_textEdit->setPlainText(file.readAll());
        file.close();
    } else {
        m_textEdit->setPlainText("无法打开文件:\n" + file.errorString());
    }
}

FileViewer::~FileViewer() {

}
