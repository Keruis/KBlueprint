#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDockWidget>
#include <QPushButton>
#include <QStringList>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_explorer(new Explorer(parent)),
      m_terminal(new Terminal(parent)),
      m_renderPreview(new RenderPreviewWidget(parent)),
      m_ui(new Ui::MainWindow()),                    //NOLINT
      m_blueprint(std::make_unique<Blueprint::BlueprintClass>())
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::Initialization() noexcept {
    m_blueprint->Initialization();

    this->setContentsMargins(4, 0, 4, 4);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);

    QWidget* central = new QWidget;
    QVBoxLayout* VLayout = new QVBoxLayout(central);
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->setSpacing(0);

    m_title = createTitleBar();
    VLayout->addWidget(m_title);

    QSplitter* verticalSplitter = new QSplitter(Qt::Vertical);

    QSplitter* mainAreaSplitter = createMainSplitter();

    m_terminal->Initialize();

    verticalSplitter->addWidget(mainAreaSplitter);
    verticalSplitter->addWidget(m_terminal);

    verticalSplitter->setStretchFactor(0, 1);
    verticalSplitter->setStretchFactor(1, 0);
    verticalSplitter->setCollapsible(1, true);

    VLayout->addWidget(verticalSplitter);
    setCentralWidget(central);
}

void MainWindow::Shutdown() noexcept { }

std::unique_ptr<Blueprint::BlueprintClass> &MainWindow::GetBlueprint() noexcept {
    return m_blueprint;
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