#ifndef BLUEPRINT_TITLEBAR_H
#define BLUEPRINT_TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include <QToolButton>
#include <QFile>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent);
    void Initialize() noexcept ;

private:
    void applyStyleSheetFromFile(const QString& filePath);
    void createMenuButtons(QHBoxLayout* layout);
    QMenu* createFileMenu();
    QMenu* createEditMenu();
    QMenu* createViewerMenu();
    QMenu* createNavMenu();
    QMenu* createHelpMenu();
    void createWindowControlButtons(QHBoxLayout* layout);

    QLabel* createIconLabel() noexcept ;
    QPushButton* createSettingBtn() noexcept ;
    QPushButton* createMinimizeBtn() noexcept ;
    QPushButton* createMaximizeBtn() noexcept ;
    QPushButton* createCloseBtn() noexcept ;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void requestSetting();
    void requestMinimize();
    void requestClose();

private:
    QPushButton* m_maximizeBtn;
    void toggleMaximizeRestore() noexcept ;
};


#endif //BLUEPRINT_TITLEBAR_H
