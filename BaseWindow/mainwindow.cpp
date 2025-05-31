#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>
#include <QStatusBar>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <qapplication.h>
#include <qfile.h>

// 需要一个你写个加载qss的了,我就不把我的main.cpp移动过来了
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("VS Code Clone - Qt");
  resize(1000, 600);
  setupUI();
}
void MainWindow::setupUI() {
  setupLeftSidebar();
  setupMainArea();
  setupRightSidebar();
  setupStatusBar();
}

void MainWindow::setupLeftSidebar() {
  // 左侧边栏
  leftSidebar = new QDockWidget("Sidebar", this);
  QWidget *sidebarContainer = new QWidget();
  QHBoxLayout *sidebarLayout = new QHBoxLayout(sidebarContainer);
  sidebarLayout->setContentsMargins(0, 0, 0, 0);
  sidebarLayout->setSpacing(0);

  // 选项
  leftSidebarList = new QListWidget();
  leftSidebarList->addItem("📁");
  leftSidebarList->addItem("🔍");
  leftSidebarList->addItem("Git");
  leftSidebarList->addItem("💡");
  leftSidebarList->addItem("⚙️");
  leftSidebarList->setFixedWidth(48);

  // 文件树
  explorer = new QTreeWidget();
  explorer->setHeaderLabel("EXPLORER");

  QTreeWidgetItem *src = new QTreeWidgetItem(explorer);
  src->setText(0, "📁 src");

  QTreeWidgetItem *item1 = new QTreeWidgetItem(src);
  item1->setText(0, "📄 main.js");

  QTreeWidgetItem *item2 = new QTreeWidgetItem(src);
  item2->setText(0, "📄 utils.js");

  QTreeWidgetItem *pub = new QTreeWidgetItem(explorer);
  pub->setText(0, "📁 public");

  QTreeWidgetItem *item3 = new QTreeWidgetItem(pub);
  item3->setText(0, "📄 index.html");

  QTreeWidgetItem *item4 = new QTreeWidgetItem(pub);
  item4->setText(0, "📄 style.css");

  QTreeWidgetItem *item5 = new QTreeWidgetItem(explorer);
  item5->setText(0, "📄 README.md");

  // 创建一个 QStackedWidget 用于切换页面
  leftStackedWidget = new QStackedWidget();

  // 创建不同的页面
  QWidget *emptyPage = new QWidget();
  emptyPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(emptyPage->layout())
      ->addWidget(new QLabel("Other View"));

  QWidget *gitPage = new QWidget();
  gitPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(gitPage->layout())
      ->addWidget(new QLabel("Git View"));

  QWidget *searchPage = new QWidget();
  searchPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(searchPage->layout())
      ->addWidget(new QLabel("Search View"));

  QWidget *settingsPage = new QWidget();
  settingsPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(settingsPage->layout())
      ->addWidget(new QLabel("Settings View"));

  // 添加页面到 QStackedWidget
  leftStackedWidget->addWidget(explorer);     // 文件树作为第一个页面
  leftStackedWidget->addWidget(searchPage);   // 搜索页面
  leftStackedWidget->addWidget(gitPage);      // Git 页面
  leftStackedWidget->addWidget(emptyPage);    // 其他页面
  leftStackedWidget->addWidget(settingsPage); // 设置页面

  // 将 QListWidget 和 QStackedWidget 添加到布局中
  sidebarLayout->addWidget(leftSidebarList);
  sidebarLayout->addWidget(leftStackedWidget);

  leftSidebar->setWidget(sidebarContainer);

  addDockWidget(Qt::LeftDockWidgetArea, leftSidebar);

  connect(leftSidebarList, &QListWidget::currentRowChanged, leftStackedWidget,
          &QStackedWidget::setCurrentIndex);
}

void MainWindow::setupMainArea() {
  splitter = new QSplitter(Qt::Vertical, this);
  QWidget *topWidget = new QWidget();
  QVBoxLayout *topLayout = new QVBoxLayout(topWidget);

  // 顶部标题栏
  QLabel *header = new QLabel("文件资源管理器 - 当前路径：/example-project");
  header->setStyleSheet(
      "background-color: #2d2d2d; color: white; padding: 5px;");
  header->setFixedHeight(30);

  // 编辑器
  editor = new QTextEdit();
  editor->setPlainText("蓝图嵌入以及节点绑定区");

  // 添加标题栏和编辑器到布局
  topLayout->addWidget(header);
  topLayout->addWidget(editor);
  topWidget->setLayout(topLayout);
  splitter->addWidget(topWidget);

  // 终端面板
  terminalPanel = new QDockWidget(this);
  terminal = new QTextEdit();
  terminal->setReadOnly(true);
  terminal->setText("$ npm run dev\nVITE v3.0.9 ready in 1234 ms\nLocal: "
                    "http://localhost:5173");
  terminalPanel->setWidget(terminal);
  terminalPanel->setAllowedAreas(Qt::BottomDockWidgetArea);

  // 将终端面板添加到主窗口的底部停靠区域
  addDockWidget(Qt::BottomDockWidgetArea, terminalPanel);

  // 添加 splitter 到主窗口
  setCentralWidget(splitter);

  // 添加一个按钮来控制终端面板的显示和隐藏
  toggleTerminalAction = new QAction("Toggle Terminal", this);
  toggleTerminalAction->setShortcut(QKeySequence("Ctrl+`"));
  addAction(toggleTerminalAction);

  // 连接信号和槽
  connect(toggleTerminalAction, &QAction::triggered, this,
          &MainWindow::toggleTerminalVisibility);

  editor->setObjectName("editor");
  terminal->setObjectName("terminal");
  terminalPanel->setObjectName("terminalPanel");
}

void MainWindow::setupRightSidebar() {
  rightSidebar = new QDockWidget("Right Sidebar", this);
  QWidget *sidebarContainer = new QWidget();
  QHBoxLayout *sidebarLayout = new QHBoxLayout(sidebarContainer);
  sidebarLayout->setContentsMargins(0, 0, 0, 0);
  sidebarLayout->setSpacing(0);

  // 图标列表
  rightSidebarList = new QListWidget();
  rightSidebarList->addItem("🔍");
  rightSidebarList->addItem("💡");
  rightSidebarList->addItem("⚙️");
  rightSidebarList->setFixedWidth(48);

  rightStackedWidget = new QStackedWidget();

  QWidget *searchPage = new QWidget();
  searchPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(searchPage->layout())
      ->addWidget(new QLabel("Search View"));

  QWidget *debugPage = new QWidget();
  debugPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(debugPage->layout())
      ->addWidget(new QLabel("Debug View"));

  QWidget *settingsPage = new QWidget();
  settingsPage->setLayout(new QVBoxLayout());
  static_cast<QVBoxLayout *>(settingsPage->layout())
      ->addWidget(new QLabel("Settings View"));

  rightStackedWidget->addWidget(searchPage);
  rightStackedWidget->addWidget(debugPage);
  rightStackedWidget->addWidget(settingsPage);

  sidebarLayout->addWidget(rightStackedWidget);
  sidebarLayout->addWidget(rightSidebarList);

  rightSidebar->setWidget(sidebarContainer);
  addDockWidget(Qt::RightDockWidgetArea, rightSidebar);

  // 切换页面逻辑
  connect(rightSidebarList, &QListWidget::currentRowChanged, rightStackedWidget,
          &QStackedWidget::setCurrentIndex);
}
void MainWindow::setupStatusBar() {
  QWidget *statusBarPanel = new QWidget(this);
  QHBoxLayout *panelLayout = new QHBoxLayout(statusBarPanel);
  panelLayout->setContentsMargins(4, 0, 4, 0);
  panelLayout->setSpacing(8);

  terminalLabel = new QPushButton("终端");
  settingsButton = new QPushButton("设置");
  helpButton = new QPushButton("帮助");

  panelLayout->addWidget(terminalLabel);
  panelLayout->addWidget(settingsButton);
  panelLayout->addWidget(helpButton);

  panelLayout->addSpacerItem(
      new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

  cpuInfoLabel = new QLabel(" CPU: --% ");
  memInfoLabel = new QLabel(" Memory: --% ");

  statusBar()->addWidget(statusBarPanel, 1);

  statusBar()->addPermanentWidget(cpuInfoLabel);
  statusBar()->addPermanentWidget(memInfoLabel);
  statusBar()->setSizeGripEnabled(false);

  statusUpdateTimer = new QTimer(this);
  connect(statusUpdateTimer, &QTimer::timeout, this,
          &MainWindow::updateStatusBarInfo);
  statusUpdateTimer->start(1000);

  connect(terminalLabel, &QPushButton::clicked, this,
          &MainWindow::toggleTerminalVisibility);
}
void MainWindow::toggleTerminalVisibility() {
  if (terminalPanel->isHidden()) {
    terminalPanel->show();
    // 更新终端按钮样式为选中状态
    terminalLabel->setProperty("selected", true);
  } else {
    terminalPanel->hide();
    // 更新终端按钮样式为非选中状态
    terminalLabel->setProperty("selected", false);
  }
  terminalLabel->style()->unpolish(terminalLabel);
  terminalLabel->style()->polish(terminalLabel);
}

void MainWindow::updateStatusBarInfo() {
  int cpuUsage = 20;
  int memUsage = 10;

  cpuInfoLabel->setText(QString("CPU: %1%").arg(cpuUsage));
  memInfoLabel->setText(QString("Memory: %1%").arg(memUsage));
}

MainWindow::~MainWindow() {}
