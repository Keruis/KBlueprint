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
#include <QPushButton>
#include <QEvent>

#include "FileViewer.h"
#include "explorerHeader.h"

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

    FileViewer* GetFileViewer() noexcept ;

protected:
    bool eventFilter(QObject* obj, QEvent* event) {
        if (event->type() == QEvent::Enter) {
            m_header->setButtonsVisible(true);
        } else if (event->type() == QEvent::Leave) {
            m_header->setButtonsVisible(false);
        }
        return QWidget::eventFilter(obj, event);
    }
signals:
    void openFile();

private:
    void populateTreeFromDirectory(const QString& path, QTreeWidgetItem* parent) ;
    QWidget* createExplorerTree() noexcept ;

private:
    QTreeWidget* m_treeWidget = nullptr;
    ExplorerHeader* m_header = nullptr;
    FileViewer* m_fileViewer = nullptr;

    QString m_rootPath;
    QStackedWidget* m_leftStackedWidget;

private slots:
    void onItemClicked(QTreeWidgetItem* item, int colum);
};


#endif //BLUEPRINT_EXPLORER_H
