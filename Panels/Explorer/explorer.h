#ifndef BLUEPRINT_EXPLORER_H
#define BLUEPRINT_EXPLORER_H

#include <QWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QVariant>

#include "FileViewer.h"

class Explorer : public QWidget {
    Q_OBJECT

public:
    explicit Explorer(QWidget* parent = nullptr);
    void Initialize(QHBoxLayout* sidebarLayout) noexcept ;
    void addSidebarPage(QWidget* widget) noexcept ;

    QString GetRootPath() const noexcept;
    void SetRootPath(const QString& rootPath) noexcept ;
    void loadNewPath(const QString& newRootPath) noexcept ;

    void SetCurrentIndex(int index) noexcept ;

private:
    void populateTreeFromDirectory(const QString& path, QTreeWidgetItem* parent) ;
    QTreeWidget* createExplorerTree() noexcept ;

private:
    QString m_rootPath;
    QListWidget* m_leftSidebarList;
    QStackedWidget* m_leftStackedWidget;

private slots:
    void onItemClicked(QTreeWidgetItem* item, int colum);
};


#endif //BLUEPRINT_EXPLORER_H
