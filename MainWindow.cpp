#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDockWidget>
#include <QPushButton>
#include <QStringList>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_background(":resource/Honkai-Impact-3rd.png"),
      m_explorer(new Explorer(parent)),
      m_bottomBar(new BottomBar(parent)),
      m_leftToolBar(new LeftToolBar(parent)),
      m_terminal(new Terminal(parent)),
      m_renderPreview(new RenderPreviewWidget(parent)),
      m_ui(new Ui::MainWindow()),                    //NOLINT
      m_blueprint(std::make_unique<Blueprint::BlueprintClass>())
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::Initialization() noexcept {
    // 初始化组件
    m_blueprint->Initialization();
    m_terminal->Initialize();

    // 本身属性
    setContentsMargins(4, 0, 4, 4);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);

    // 创建 Central Widget 和外层垂直布局
    QWidget* central = new QWidget;
    QVBoxLayout* mainVLayout = new QVBoxLayout(central);
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);

    // === 顶部标题栏 ===
    m_title = createTitleBar();
    mainVLayout->addWidget(m_title);

    // === 中间内容区域（左边工具栏 + 主区域）===
    QHBoxLayout* centerHLayout = new QHBoxLayout;
    centerHLayout->setContentsMargins(0, 0, 0, 0);
    centerHLayout->setSpacing(0);

    // 左边工具栏
    m_leftToolBar->Initialize();

    // 右边主区域（蓝图 + 终端）
    QWidget* rightContent = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightContent);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    QSplitter* verticalSplitter = new QSplitter(Qt::Vertical);
    QSplitter* mainAreaSplitter = createMainSplitter(); // 蓝图+预览
    verticalSplitter->addWidget(mainAreaSplitter);
    verticalSplitter->addWidget(m_terminal);
    verticalSplitter->setStretchFactor(0, 1);
    verticalSplitter->setStretchFactor(1, 0);
    verticalSplitter->setCollapsible(1, true);

    rightLayout->addWidget(verticalSplitter);
    centerHLayout->addWidget(m_leftToolBar);
    centerHLayout->addWidget(rightContent);

    mainVLayout->addLayout(centerHLayout); // 中间加入主垂直布局

    // === 底部状态栏 ===
    m_bottomBar->Initialize();
    mainVLayout->addWidget(m_bottomBar); // 最下方添加状态栏

    // 设置 central widget
    setCentralWidget(central);

    // 保存终端高度
    connect(verticalSplitter, &QSplitter::splitterMoved, this,
            [=](int, int) {
                m_lastTerminalSplitterSizes = verticalSplitter->sizes();
    });

    connect(m_leftToolBar, &LeftToolBar::buttonClicked, m_explorer, &Explorer::SetCurrentIndex);
}

void MainWindow::Shutdown() noexcept { }

std::unique_ptr<Blueprint::BlueprintClass> &MainWindow::GetBlueprint() noexcept {
    return m_blueprint;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    //QPainter painter(this);
    //painter.drawPixmap(rect(), m_background);
    QMainWindow::paintEvent(event);
}

void MainWindow::toggleTerminal() {
    QSplitter* splitter = qobject_cast<QSplitter*>(m_terminal->parentWidget());
    if (!splitter) return;

    if (m_terminalVisible) {
        // 折叠：记录当前尺寸
        m_lastTerminalSplitterSizes = splitter->sizes();

        QList<int> sizes = m_lastTerminalSplitterSizes;
        sizes[0] += sizes[1];
        sizes[1] = 0;
        splitter->setSizes(sizes);
    } else {
        // 还原：使用上次记录的尺寸
        if (!m_lastTerminalSplitterSizes.isEmpty()) {
            splitter->setSizes(m_lastTerminalSplitterSizes);
        } else {
            // 如果没有记录，用默认比例
            QList<int> sizes;
            sizes << height() * 0.75 << height() * 0.25;
            splitter->setSizes(sizes);
        }
    }

    m_terminalVisible = !m_terminalVisible;
}

void MainWindow::changeFilePath() {
    QString folderPath = QFileDialog::getExistingDirectory(
            this,
            tr("选择文件夹"),
            m_explorer->GetRootPath(),
            QFileDialog::ShowDirsOnly
    );

    if (!folderPath.isEmpty()) {
        m_explorer->loadNewPath(folderPath);
        m_bottomBar->SetPath(folderPath);
        qDebug() << "Selected Folder:" << folderPath;
        update();
    }
}

void MainWindow::showOptionMenu(const QPoint &pos) {
    RadialMenu* radialMenu = new RadialMenu(this);

    connect(radialMenu, &RadialMenu::segmentClicked, this, [=, this](int index){
        qDebug() << "你点击了第" << index << "个菜单选项";
        switch (index) {
            case 0:
                toggleTerminal();
                break;

            case 1:
                changeFilePath();
                break;
        }
    });

    QPoint center = rect().center();
    radialMenu->move(mapToGlobal(center) - QPoint(radialMenu->width()/2, radialMenu->height()/2));
    radialMenu->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_resizeDir = calculateResizeDirection(event->pos());
        if (m_resizeDir != NoResize) {
            m_dragStartPos = event->globalPos();
            m_startGeometry = geometry();
            event->accept();
            return;
        } else {
            // 只有点标题栏区域，才允许拖动窗口
            if (m_title && m_title->geometry().contains(event->pos())) {
                m_dragPosition = event->globalPos() - frameGeometry().topLeft();
                event->accept();
                return;
            }
        }
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (m_resizeDir != NoResize) {
            QPoint delta = event->globalPos() - m_dragStartPos;
            QRect geom = m_startGeometry;

            switch (m_resizeDir) {
                case ResizeLeft:     geom.setLeft(geom.left() + delta.x()); break;
                case ResizeRight:    geom.setRight(geom.right() + delta.x()); break;
                case ResizeTop:      geom.setTop(geom.top() + delta.y()); break;
                case ResizeBottom:   geom.setBottom(geom.bottom() + delta.y()); break;
                case ResizeLeftTop:
                    geom.setLeft(geom.left() + delta.x());
                    geom.setTop(geom.top() + delta.y());
                    break;
                case ResizeRightTop:
                    geom.setRight(geom.right() + delta.x());
                    geom.setTop(geom.top() + delta.y());
                    break;
                case ResizeLeftBottom:
                    geom.setLeft(geom.left() + delta.x());
                    geom.setBottom(geom.bottom() + delta.y());
                    break;
                case ResizeRightBottom:
                    geom.setRight(geom.right() + delta.x());
                    geom.setBottom(geom.bottom() + delta.y());
                    break;
                default: break;
            }

            if (geom.width() < minimumWidth()) geom.setWidth(minimumWidth());
            if (geom.height() < minimumHeight()) geom.setHeight(minimumHeight());

            setGeometry(geom);
            unsetCursor();
        } else {
            if (!m_dragPosition.isNull()) {
                move(event->globalPos() - m_dragPosition);
            }
            unsetCursor();
        }
        event->accept();
    } else {
        ResizeDirection dir = calculateResizeDirection(event->pos());
        switch (dir) {
            case ResizeLeft: case ResizeRight:
                setCursor(Qt::SizeHorCursor); break;
            case ResizeTop: case ResizeBottom:
                setCursor(Qt::SizeVerCursor); break;
            case ResizeLeftTop: case ResizeRightBottom:
                setCursor(Qt::SizeFDiagCursor); break;
            case ResizeRightTop: case ResizeLeftBottom:
                setCursor(Qt::SizeBDiagCursor); break;
            default:
                unsetCursor(); break;
        }
    }
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    m_dragPosition = QPoint();
    if (event->button() == Qt::LeftButton) {
        m_resizeDir = NoResize;
        unsetCursor();
        event->accept();
    } else {
        QMainWindow::mouseReleaseEvent(event);
    }
    unsetCursor();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab && event->modifiers() & Qt::ControlModifier) {
        showOptionMenu(rect().center());  // 在窗口中心弹出菜单
        event->accept(); // 阻止事件继续传递
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

MainWindow::ResizeDirection MainWindow::calculateResizeDirection(const QPoint &pos) noexcept {
    constexpr const int edgeSize = 4;
    QRect rect = this->rect();

    bool left   = abs(pos.x() - rect.left()) <= edgeSize;
    bool right  = abs(pos.x() - rect.right()) <= edgeSize;
    bool top    = abs(pos.y() - rect.top()) <= edgeSize;
    bool bottom = abs(pos.y() - rect.bottom()) <= edgeSize;

    if (left && top) return ResizeLeftTop;
    if (right && top) return ResizeRightTop;
    if (left && bottom) return ResizeLeftBottom;
    if (right && bottom) return ResizeRightBottom;
    if (left) return ResizeLeft;
    if (right) return ResizeRight;
    if (top) return ResizeTop;
    if (bottom) return ResizeBottom;
    return NoResize;
}

TitleBar* MainWindow::createTitleBar() noexcept {
    auto* title = new TitleBar(this);
    title->Initialize();
    title->setFixedHeight(30);

    connect(title, &TitleBar::requestMinimize, this, &MainWindow::showMinimized);
    connect(title, &TitleBar::requestClose, this, &MainWindow::close);

    return title;
}

QSplitter* MainWindow::createMainSplitter() noexcept {
    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    // 侧边栏
    QWidget* sidebarContainer = new QWidget();
    QHBoxLayout* sidebarLayout = new QHBoxLayout(sidebarContainer);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

   // m_explorer->SetRootPath("/home/keruis/extra/ASMDSL/");
    m_explorer->Initialize(sidebarLayout);

    sidebarContainer->setMinimumWidth(48);
    sidebarContainer->setMaximumWidth(400);
    sidebarContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    m_renderPreview->setMinimumWidth(20);

    splitter->addWidget(sidebarContainer);
    splitter->addWidget(m_blueprint.get());
    splitter->addWidget(m_renderPreview);

    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 1);
    splitter->setCollapsible(0, false);

    return splitter;
}