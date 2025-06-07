#ifndef BLUEPRINT_FILEVIEWER_H
#define BLUEPRINT_FILEVIEWER_H


#include <QWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QMap>
#include <QString>

class FileViewer : public QWidget {
Q_OBJECT
public:
    explicit FileViewer(QWidget* parent = nullptr);
    ~FileViewer();

    void openFile(const QString& filePath);
    void closeFile(const QString& filePath);
    void closeCurrentFile();
    bool hasFile(const QString& filePath) const;

private:
    QTabWidget* m_tabWidget;

    QMap<QString, QTextEdit*> m_openedFiles;
};


#endif //BLUEPRINT_FILEVIEWER_H
