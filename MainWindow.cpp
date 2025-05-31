#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDockWidget>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(std::make_unique<Ui::MainWindow>()),                    //NOLINT
      m_blueprint(std::make_unique<Blueprint::BlueprintClass>())
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::Initialization() noexcept {
    m_blueprint->Initialization();

    this->setContentsMargins(8, 0, 8, 8);
    setMouseTracking(true);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);

    // 自定义标题栏
    m_title = new TitleBar(this);
    m_title->Initialize();

    // 蓝图容器
    auto central = new QWidget;
    auto layout = new QVBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_title);
    layout->addWidget(m_blueprint.get());
    setCentralWidget(central);

    connect(m_title, &TitleBar::requestMinimize, this, &MainWindow::showMinimized);
    connect(m_title, &TitleBar::requestClose, this, &MainWindow::close);

    update();
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
            m_dragPosition = event->globalPos() - frameGeometry().topLeft();
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
            move(event->globalPos() - m_dragPosition);
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