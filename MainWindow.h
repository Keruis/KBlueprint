#ifndef BLUEPRINT_MAINWINDOW_H
#define BLUEPRINT_MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QListWidget>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QFileDialog>
#include <QSplitter>
#include <QTextEdit>
#include "Title/TitleBar.h"
#include "BlueprintMain/include/BlueprintClass.h"
#include "Panels/Explorer/explorer.h"
#include "Panels/Terminal/terminal.h"
#include "Panels/RenderPreviewWidget/RenderPreviewWidget.h"
#include "RadialMenu/RadialMenu.h"
#include "Panels/Auxiliary/BottomBar.h"
#include "Panels/Auxiliary/LeftToolBar.h"
#include "widgets/DynamicWidgetContainer.h"

#include "Expand_MoeChat/ChatWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    enum ResizeDirection {
        NoResize,
        ResizeLeft,
        ResizeRight,
        ResizeTop,
        ResizeBottom,
        ResizeLeftTop,
        ResizeRightTop,
        ResizeLeftBottom,
        ResizeRightBottom
    };
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void Initialization() noexcept ;
    void Shutdown() noexcept ;

    Blueprint::BlueprintClass* GetBlueprint() noexcept ;

protected:
    void paintEvent(QPaintEvent* event) override ;
    void mousePressEvent(QMouseEvent *event) override ;
    void mouseMoveEvent(QMouseEvent *event) override ;
    void mouseReleaseEvent(QMouseEvent *event) override ;
    void keyPressEvent(QKeyEvent* event) override ;

private:
    void initCoreModules() noexcept;
    void initWindowProperties() noexcept;
    QVBoxLayout* initMainLayout(QWidget* central) noexcept;
    QWidget* initCenterContent() noexcept;
    void setupSignalSlots() noexcept;
    void loadStyleSheet(const QString& path) noexcept;

    ResizeDirection calculateResizeDirection(const QPoint &pos) noexcept ;
    TitleBar* createTitleBar() noexcept ;
    QSplitter* createMainSplitter() noexcept ;
    void showOptionMenu(const QPoint &pos);

    void toggleTerminal();
    void changeFilePath();

    void showPageIfNotCurrent(const QString& name);

private:
    ChatWindow* m_moeChat;

    Utils::Xml* m_ConfigurationRoot;

    QPixmap m_background;

    TitleBar* m_title;
    BottomBar* m_bottomBar;
    LeftToolBar* m_leftToolBar;
    Explorer *m_explorer;

    Terminal* m_terminal;
    bool m_terminalVisible = true;
    QList<int> m_lastTerminalSplitterSizes;

    RenderPreviewWidget* m_renderPreview;
    ResizeDirection m_resizeDir = NoResize;
    QPoint m_dragStartPos;
    QRect m_startGeometry;
    QPoint m_dragPosition;
    Ui::MainWindow* m_ui;
    Blueprint::BlueprintClass* m_blueprint;

    DynamicWidgetContainer* m_blueprintContainer;
};


#endif
