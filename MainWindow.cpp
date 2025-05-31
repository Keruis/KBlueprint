#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDockWidget>
#include <QPushButton>
#include <QStringList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
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

    m_title = new TitleBar(this);
    m_title->Initialize();
    m_title->setFixedHeight(30);
    VLayout->addWidget(m_title);

    connect(m_title, &TitleBar::requestMinimize, this, &MainWindow::showMinimized);
    connect(m_title, &TitleBar::requestClose, this, &MainWindow::close);

    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    QWidget *sidebarContainer = new QWidget();
    QHBoxLayout *sidebarLayout = new QHBoxLayout(sidebarContainer);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    m_leftSidebarList = new QListWidget();
    m_leftSidebarList->addItem("📁");
    m_leftSidebarList->addItem("🔍");
    m_leftSidebarList->addItem("Git");
    m_leftSidebarList->addItem("💡");
    m_leftSidebarList->addItem("⚙️");
    m_leftSidebarList->setFixedWidth(48);

    m_explorer = new QTreeWidget();
    m_explorer->setHeaderLabel("EXPLORER");
    auto src = new QTreeWidgetItem(m_explorer);
    src->setText(0, "📁 src");
    src->addChild(new QTreeWidgetItem(QStringList("📄 main.js")));
    src->addChild(new QTreeWidgetItem(QStringList("📄 utils.js")));

    auto pub = new QTreeWidgetItem(m_explorer);
    pub->setText(0, "📁 public");
    pub->addChild(new QTreeWidgetItem(QStringList("📄 index.html")));
    pub->addChild(new QTreeWidgetItem(QStringList("📄 style.css")));

    m_explorer->addTopLevelItem(src);
    m_explorer->addTopLevelItem(pub);
    m_explorer->addTopLevelItem(new QTreeWidgetItem(QStringList("📄 README.md")));

    m_leftStackedWidget = new QStackedWidget();
    m_leftStackedWidget->addWidget(m_explorer);
    m_leftStackedWidget->addWidget(new QLabel("Search View"));
    m_leftStackedWidget->addWidget(new QLabel("Git View"));
    m_leftStackedWidget->addWidget(new QLabel("Other View"));
    m_leftStackedWidget->addWidget(new QLabel("Settings View"));

    sidebarLayout->addWidget(m_leftSidebarList);
    sidebarLayout->addWidget(m_leftStackedWidget);
    sidebarContainer->setMinimumWidth(200);
    sidebarContainer->setMaximumWidth(400);
    sidebarContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    splitter->addWidget(sidebarContainer);
    splitter->addWidget(m_blueprint.get());
    splitter->setStretchFactor(1, 1);

    m_leftSidebarList->setMinimumWidth(48);
    m_leftStackedWidget->setMinimumWidth(48);
    sidebarContainer->setMinimumWidth(48);
    splitter->setCollapsible(0, false);

    VLayout->addWidget(splitter);
    setCentralWidget(central);

    connect(m_leftSidebarList, &QListWidget::currentRowChanged,
            m_leftStackedWidget, &QStackedWidget::setCurrentIndex);
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