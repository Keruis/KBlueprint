#include "../include/BlueprintClass.h"
#include "../ui/ui_BlueprintClass.h"

import EventHelpers;

using namespace Blueprint;

BlueprintClass::BlueprintClass(QWidget *parent)
    : QGraphicsView(parent),
    m_ui(std::make_unique<Ui::BlueprintClass>()),
    m_scene(std::make_unique<QGraphicsScene>(this)),
    m_animationTimer(new QTimer(this)),
    m_blurEffect(new QGraphicsBlurEffect(this))
{
    m_ui->setupUi(this);
    m_scene->setSceneRect(-1000, -1000, 2000, 2000);
    setScene(m_scene.get());
}

BlueprintClass::~BlueprintClass() = default;

void BlueprintClass::setupRendering() noexcept {
    setRenderHint(QPainter::Antialiasing);  // 抗锯齿
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

void BlueprintClass::setupInteraction() noexcept {
    setDragMode(QGraphicsView::ScrollHandDrag);  // 设置拖拽模式
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void BlueprintClass::setupAppearance() noexcept {
    setFrameShape(QFrame::NoFrame);
    setBackgroundBrush(QColor(30, 30, 30));  // 设置深色背景

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void BlueprintClass::Initialization() noexcept {
    connect(m_animationTimer, &QTimer::timeout, this, &BlueprintClass::smoothZoom);
    m_animationTimer->start(16); // ~60 FPS
    setGraphicsEffect(m_blurEffect);
    setupRendering();
    setupInteraction();
    setupAppearance();
}

void BlueprintClass::Shutdown() noexcept {}

bool tt = true;

//  TEST
void BlueprintClass::contextMenuEvent(QContextMenuEvent* event) {
    QMenu contextMenu;
    QPointF scenePos = mapToScene(event->pos());

    if (tt) {
        BlueprintNode* tmp = new BlueprintNode(3, 1, nullptr);
        tmp->SetNodeName("A");
        tmp->SetClassName("Other");
        tmp->Initialize(1);

        BlueprintNode* tmp2 = new BlueprintNode(1, 1, nullptr);
        tmp2->SetNodeName("B");
        tmp2->SetClassName("Other");
        tmp2->Initialize(1);
        m_saveNodes.push_back(tmp);
        m_saveNodes.push_back(tmp2);
    }
    tt = false;
    // 加载 QSS 文件
    QFile styleFile(":/qss/ContextMenu.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qDebug() << styleSheet;
        contextMenu.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qWarning() << "Failed to load QSS file!";
    }

    // 使用 map 存储类名和节点列表
    QMap<QString, QList<BlueprintNode*>> classNodeMap;
    for (BlueprintNode* node : m_saveNodes) {
        if (!node) continue;
        classNodeMap[node->GetClassName()].append(node);
    }

    // 遍历每个类，创建菜单
    for (auto it = classNodeMap.begin(); it != classNodeMap.end(); ++it) {
        QString className = it.key();
        QList<BlueprintNode*> nodes = it.value();

        // 创建菜单并设置对象名称（与 QSS 选择器匹配）
        QMenu* classMenu = contextMenu.addMenu(className);
        classMenu->setObjectName(className + "Menu");

        // 添加菜单项
        for (BlueprintNode* node : nodes) {
            QAction* action = classMenu->addAction(node->GetNodeName());
            connect(action, &QAction::triggered, [this, node, scenePos]() {
                PlaceNodeInScene(node, scenePos);
            });
        }
    }

    contextMenu.exec(event->globalPos());
}

void BlueprintClass::PlaceNodeInScene(BlueprintNode *originalNode, const QPointF &mousePos) noexcept {
    BlueprintNode* newNode = originalNode->clone();
    newNode->setPos(mousePos);
    m_scene->addItem(newNode);
    m_sceneNodes.push_back(newNode);
}

Vector<BlueprintConnection *> BlueprintClass::GetConnections() noexcept {
    return m_connections;
}

void BlueprintClass::updateConnectionsForPort(BlueprintPort *port) {
    // 遍历所有连接并更新与指定端口相关的连接
    for (BlueprintConnection *connection : m_connections)
    {
        if (connection->GetStartPort() == port)
        {
            connection->UpdatePosition(port->centerPos(), connection->GetEndPort()->centerPos());
        }
        else if (connection->GetEndPort() == port)
        {
            connection->UpdatePosition(connection->GetStartPort()->centerPos(), port->centerPos());
        }
    }
}

void BlueprintClass::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsView::drawBackground(painter, rect);

    // 绘制网格背景
    const int gridSize = 20;  // 网格大小
    QPen lightPen(QColor(60, 60, 60), 1);  // 浅色网格线
    QPen darkPen(QColor(25, 25, 25), 2);   // 深色网格线

    // 获取当前视图的矩形区域
    QRectF viewRect = rect;

    // 绘制小网格线
    painter->setPen(lightPen);
    for (qreal x = std::floor(viewRect.left() / gridSize) * gridSize; x < viewRect.right(); x += gridSize) {
        painter->drawLine(QLineF(x, viewRect.top(), x, viewRect.bottom()));
    }
    for (qreal y = std::floor(viewRect.top() / gridSize) * gridSize; y < viewRect.bottom(); y += gridSize) {
        painter->drawLine(QLineF(viewRect.left(), y, viewRect.right(), y));
    }

    // 绘制大网格线（每隔5个小网格）
    painter->setPen(darkPen);
    for (qreal x = std::floor(viewRect.left() / (gridSize * 5)) * (gridSize * 5); x < viewRect.right(); x += gridSize * 5) {
        painter->drawLine(QLineF(x, viewRect.top(), x, viewRect.bottom()));
    }
    for (qreal y = std::floor(viewRect.top() / (gridSize * 5)) * (gridSize * 5); y < viewRect.bottom(); y += gridSize * 5) {
        painter->drawLine(QLineF(viewRect.left(), y, viewRect.right(), y));
    }
}

// 鼠标滚轮事件处理函数，用于触发平滑缩放和模糊过渡效果
void BlueprintClass::wheelEvent(QWheelEvent *event) {
    constexpr const double zoomStep = 0.25; // 每次滚动缩放步长
    constexpr const double blurStep = 8.0;  // 每次滚动模糊步长

    EventHelpers::wheelEvent(
            zoomStep,
            blurStep,
            event->angleDelta().y(),
            m_targetZoomLevel,
            m_targetBlurLevel,
            m_zoomLevel,
            m_blurLevel,
            m_velocity
    );

    m_isDashing = true;   // 启用平滑缩放动画
    event->accept();     // 标记事件已处理
}

// 执行平滑缩放与模糊的动画过渡函数（需在定时器或帧更新中持续调用）
void BlueprintClass::smoothZoom() noexcept {
    EventHelpers::smoothZoom(
            m_isDashing,
            m_velocity,
            m_targetZoomLevel,
            m_targetBlurLevel,
            m_zoomLevel,
            m_blurLevel
            );

    // 应用缩放变换到视图
    QTransform t;
    t.scale(m_zoomLevel, m_zoomLevel);
    setTransform(t); // 设置视图变换

    // 应用模糊效果
    if (m_blurEffect) {
        m_blurEffect->setBlurRadius(m_blurLevel);   // 设置模糊半径
    }

    updateAllConnections();   // 更新所有连接
}

void BlueprintClass::mousePressEvent(QMouseEvent *event) {
    // 将视图坐标转换为场景坐标
    QPointF scenePos = mapToScene(event->pos());
    QGraphicsItem *item = m_scene->itemAt(scenePos, QTransform());

    // 查找鼠标点击的图元
    qDebug()<< "clicked item:" << item;

    if (!item && event->button() == Qt::LeftButton) {
        qDebug() << "background";
        m_panning = true;
        QGraphicsView::mousePressEvent(event);
    }

    // 首先检查是否点击在端口上
    BlueprintPort *port = dynamic_cast<BlueprintPort*>(item);
    if (port) {
        qDebug() << "Clicked on port:" << port->GetName();
        m_draggingPort = port;
        startConnectionDrag(scenePos);
        return;
    }

    // 然后检查是否点击在节点上
    BlueprintNode *node = dynamic_cast<BlueprintNode*>(item);
    if (node) {
        qDebug() << "Clicked Node";
        // 使用访问器方法获取端口列表
        const auto& inputPorts = node->GetInputPorts();
        const auto& outputPorts = node->GetOutputPorts();

        // 遍历找到点击的端口
        for (auto *pPort : inputPorts) {
            if (pPort->contains(pPort->mapFromScene(scenePos))) {
                qDebug() << "Clicked on input pPort:" << pPort->GetName();
                m_draggingPort = pPort;
                startConnectionDrag(scenePos);
                return;
            }
        }

        for (auto *pPort : outputPorts) {
            if (pPort->contains(pPort->mapFromScene(scenePos))) {
                qDebug() << "Clicked on output pPort:" << pPort->GetName();
                m_draggingPort = pPort;
                startConnectionDrag(scenePos);
                return;
            }
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void BlueprintClass::mouseMoveEvent(QMouseEvent *event) {
    QPointF scenePos = mapToScene(event->pos());

    if (m_draggingPort && m_currentConnection) {
        // 更新连接线位置
        m_currentConnection->UpdatePosition(m_draggingPort->centerPos(), scenePos);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void BlueprintClass::mouseReleaseEvent(QMouseEvent *event) {
    if (m_draggingPort && m_currentConnection) {
        // 将视图坐标转换为场景坐标
        QPointF scenePos = mapToScene(event->pos());
        qDebug() << "(m_draggingPort && m_currentConnection)" ;
        // 遍历场景中的所有项目，寻找匹配的端口
        BlueprintPort *targetPort = nullptr;
        for (QGraphicsItem *item : m_scene->items(scenePos)) {
            targetPort = dynamic_cast<BlueprintPort*>(item);
            if (targetPort && targetPort != m_draggingPort && targetPort->GetPortType() != m_draggingPort->GetPortType() && targetPort->parentItem() != m_draggingPort->parentItem()) {
                break;  // 找到目标端口，退出循环
            }
        }
        if(targetPort) {
            if((targetPort->GetPortType() == PortType::EVENT_INPUT && m_currentConnection->GetStartPort()->GetPortType() == PortType::EVENT_OUTPUT)
               ||(targetPort->GetPortType() == PortType::EVENT_OUTPUT && m_currentConnection->GetStartPort()->GetPortType() == PortType::EVENT_INPUT)
               ||(targetPort->GetPortType() == PortType::EVENT_INPUT && m_currentConnection->GetStartPort()->GetPortType() == PortType::EVENT_FALSE_RETURN)
               ||(targetPort->GetPortType() == PortType::EVENT_INPUT && m_currentConnection->GetStartPort()->GetPortType() == PortType::EVENT_TRUE_RETURN))
            {
                qDebug() << "事件端口连接";
                m_currentConnection->SetEndPort(targetPort);
                m_draggingPort->sendDataToConnectedPorts();
                propagateDataFromInitialNode(m_currentConnection->GetStartPort());
            }
            else if (areTypesCompatible(m_currentConnection->GetStartPort()->GetVarTypeName(),targetPort->GetVarTypeName())
                     && targetPort->GetPortType()!=PortType::EVENT_INPUT && targetPort->GetPortType()!=PortType::EVENT_OUTPUT)
            {
                qDebug() << "Found target port:" << targetPort->GetName();
                // 连接两个端口
                m_currentConnection->SetEndPort(targetPort);
                m_draggingPort->sendDataToConnectedPorts();
            } else {
                qDebug() << m_currentConnection->GetStartPort()->GetVarTypeName() << " vs " << targetPort->GetVarTypeName();
                removeConnection(m_currentConnection); // 删除连接
            }
        }
        else
            removeConnection(m_currentConnection);

        m_currentConnection = nullptr;
        m_draggingPort = nullptr;
    }
    qDebug() << "mouseReleaseEvent(event);";
    QGraphicsView::mouseReleaseEvent(event);
}

void BlueprintClass::updateAllConnections() noexcept {
    for (BlueprintConnection* connection : m_connections) {
        if (connection->GetStartPort() && connection->GetEndPort()) {
            connection->UpdatePosition(connection->GetStartPort()->centerPos(), connection->GetEndPort()->centerPos());
        }
    }
}

void BlueprintClass::addConnection(BlueprintConnection *connection) noexcept {
    m_connections.push_back(connection);
    m_scene->addItem(connection);
}

void BlueprintClass::removeConnection(BlueprintConnection *connection) noexcept {
    m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), connection), m_connections.end());
    m_scene->removeItem(connection); // 从场景中移除连接
    delete connection;
}

void BlueprintClass::startConnectionDrag(const QPointF &startPos) noexcept {
    // 创建临时连线
    m_currentConnection = new BlueprintConnection(m_draggingPort, nullptr);
    addConnection(m_currentConnection); // 将连接添加到管理列表中

    // 设置初始位置
    m_currentConnection->UpdatePosition(m_draggingPort->centerPos(), startPos);

    // 强制刷新场景
    m_scene->update();
}

void BlueprintClass::propagateDataFromInitialNode(BlueprintPort *init) noexcept {
    if (!init) return;

    // 获取初始端口的父节点
    BlueprintNode* initialNode = dynamic_cast<BlueprintNode*>(init->parentItem());
    if (!initialNode) return;

    // 找到该节点的所有输出端口，并发送数据
    for (BlueprintPort* outputPort : initialNode->GetOutputPorts()) {
        outputPort->sendDataToConnectedPorts();
    }
}

bool BlueprintClass::areTypesCompatible(const QString &type1, const QString &type2) noexcept {
    if (type1 == type2) return true;

    return false;
}