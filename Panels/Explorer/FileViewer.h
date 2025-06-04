#ifndef BLUEPRINT_FILEVIEWER_H
#define BLUEPRINT_FILEVIEWER_H

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>


class FileViewer : public QWidget {
    Q_OBJECT

public:
    explicit FileViewer(const QString& filePath, QWidget* parent = nullptr);
    ~FileViewer() override ;

private:
    QTextEdit* m_textEdit;
};


#endif //BLUEPRINT_FILEVIEWER_H
