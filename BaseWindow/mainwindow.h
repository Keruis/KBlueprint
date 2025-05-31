#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWhatsThisClickedEvent>
#include <QWidget>
#include <qpushbutton.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void setupUI();
  void setupLeftSidebar();
  void setupMainArea();
  void setupRightSidebar();
  void setupStatusBar();
  void updateStatusBarInfo();
  void toggleTerminalVisibility();

  QDockWidget *leftSidebar;
  QListWidget *leftSidebarList;
  QTreeWidget *explorer;
  QStackedWidget *leftStackedWidget;

  QSplitter *splitter;
  QTextEdit *editor;

  QDockWidget *rightSidebar;
  QListWidget *rightSidebarList;
  QStackedWidget *rightStackedWidget;

  QDockWidget *terminalPanel;
  QTextEdit *terminal;
  QAction *toggleTerminalAction;

  QPushButton *terminalLabel;
  QPushButton *helpButton;
  QPushButton *settingsButton;
  QLabel *cpuInfoLabel;
  QLabel *memInfoLabel;
  QTimer *statusUpdateTimer;
};
#endif // MAINWINDOW_H
