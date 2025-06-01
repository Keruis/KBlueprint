#ifndef BLUEPRINT_EXPLORER_H
#define BLUEPRINT_EXPLORER_H

#include <QWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>

class Explorer : public QWidget {
    Q_OBJECT

public:
    explicit Explorer(QWidget* parent = nullptr);
    void Initialize(QHBoxLayout* sidebarLayout) noexcept ;
    void addSidebarPage(const QIcon& icon, const QString& tooltip, QWidget* widget) noexcept ;
    void addSidebarPage(const QString& iconText, QWidget* widget) noexcept ;

private:
    QTreeWidget* createExplorerTree() noexcept ;

private:
    QListWidget* m_leftSidebarList;
    QStackedWidget* m_leftStackedWidget;
};


#endif //BLUEPRINT_EXPLORER_H
