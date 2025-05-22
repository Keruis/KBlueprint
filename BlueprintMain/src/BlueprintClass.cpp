#include "../include/BlueprintClass.h"
#include "../ui/ui_BlueprintClass.h"

BlueprintClass::BlueprintClass(QWidget *parent)
    : QGraphicsView(parent),
    m_ui(new Ui::BlueprintClass),
    m_scene(new QGraphicsScene(this))
{
    m_ui->setupUi(this);
    setScene(m_scene);
}

BlueprintClass::~BlueprintClass() = default;

void BlueprintClass::Initialization() noexcept {
    setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    setDragMode(QGraphicsView::ScrollHandDrag);  // 设置拖拽模式

    // 初始视图缩放
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setBackgroundBrush(QColor(30, 30, 30));  // 设置深色背景
}

void BlueprintClass::Shutdown() noexcept {
    delete m_ui;
    m_ui = nullptr;
}

# TEST
void BlueprintClass::contextMenuEvent(QContextMenuEvent* event) {
    // 获取鼠标在场景中的位置
    QPointF scenePos = mapToScene(event->pos());

    // 创建右键菜单
    QMenu contextMenu;

    // 加载 QSS 样式表
    QFile styleFile(":/qss/ContextMenu.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        contextMenu.setStyleSheet(styleSheet);
        styleFile.close();
    }

    QStringList classNames = {"Input", "Output", "Logic", "Math"};
    QMap<QString, QStringList> classNodeMap;

    classNodeMap["Input"] = {"Input A", "Input B", "Input C"};
    classNodeMap["Output"] = {"Output X", "Output Y"};
    classNodeMap["Logic"] = {"AND", "OR", "NOT"};
    classNodeMap["Math"] = {"Add", "Subtract", "Multiply"};

    // 遍历模拟数据，生成菜单
    for (auto it = classNodeMap.begin(); it != classNodeMap.end(); ++it) {
        QString className = it.key();
        QStringList nodes = it.value();

        // 创建子菜单，并设置 objectName
        QMenu* classMenu = contextMenu.addMenu(className);
        if (className == "Input") {
            classMenu->setObjectName("InputMenu");
        } else if (className == "Output") {
            classMenu->setObjectName("OutputMenu");
        } else {
            classMenu->setObjectName("OtherMenu");
        }

        for (const QString& nodeName : nodes) {
            QAction* action = classMenu->addAction(nodeName);
            connect(action, &QAction::triggered, [this, nodeName, scenePos]() {
                qDebug() << "Clicked:" << nodeName << "at position:" << scenePos;
            });
        }
    }

    // 显示菜单
    contextMenu.exec(event->globalPos());
}