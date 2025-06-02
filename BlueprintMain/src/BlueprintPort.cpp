#include <utility>

#include "../include/BlueprintPort.h"
#include "../include/BlueprintConnection.h"

using namespace Blueprint;

BlueprintPort::BlueprintPort(QGraphicsItem *parent, PortType type, QString name, int dataType, QString brief)
    : QGraphicsItem(parent),
      m_type(type),
      m_name(std::move(name)),
      m_dataType(dataType),
      m_portBrief(std::move(brief))
{

}

BlueprintPort::~BlueprintPort() = default;

void BlueprintPort::Initialization() noexcept {
    m_font.SetFont(QFont("Arial", 10));
    initializeGraphicsItem();
}

void BlueprintPort::Shutdown() noexcept {

}

BlueprintPort *BlueprintPort::clone() const {
    BlueprintPort* new_port = new BlueprintPort(nullptr, this->m_type, this->m_name, this->m_dataType, this->m_portBrief);
    new_port->SetNodeType(this->m_parentNodeType);
    return new_port;
}

QRectF BlueprintPort::boundingRect() const {
    return QRectF(0, 0, 10, 10);
}

void BlueprintPort::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setFont(m_font.GetFont());

    QFontMetrics fontMetrics(m_font.GetFont());
    int textWidth = fontMetrics.horizontalAdvance(m_name);
    int textHeight = fontMetrics.height();

    // 绘制端口
    if (m_type == EVENT_INPUT || m_type == EVENT_OUTPUT || m_type == EVENT_TRUE_RETURN || m_type == EVENT_FALSE_RETURN) {
        QPolygonF pentagon;
        qreal size = 5; // 控制整体大小
        QPointF center = boundingRect().center(); // 中心点

        // 计算五角形的五个顶点（以中心点为圆心，顺时针方向）
        for (int i = 0; i < 5; ++i) {
            qreal angle_deg = 72 * i - 90;  // 起始角为 -90° 使其朝右
            qreal angle_rad = qDegreesToRadians(angle_deg);
            QPointF point(center.x() + size * std::cos(angle_rad),
                          center.y() + size * std::sin(angle_rad));
            pentagon << point;
        }

        painter->setBrush(Qt::white);
        painter->setPen(Qt::NoPen);
        painter->drawPolygon(pentagon);
    } else {
        // 绘制圆形端口
        painter->setBrush((m_type == Input) ? Qt::blue : Qt::green);  // 输入端口为蓝色，输出端口为绿色
        painter->drawEllipse(boundingRect());  // 绘制圆形端口
    }

    // 绘制端口名称，放在端口旁边
    painter->setPen(Qt::white);
    if (m_type == Input || m_type == EVENT_INPUT) {
        // 输入端口：名称在端口的右边，左对齐
        QRectF textRect = boundingRect().translated(boundingRect().width() + 10, 0);  // 向右移动文本区域，留出10像素的间距
        textRect.setWidth(textWidth);  // 设置文本区域的宽度，确保名称的最后字符靠近端口
        textRect.setHeight(textHeight);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, m_name);  // 名称放在右侧，左对齐
    } else {
        // 输出端口：名称在端口的左边，右对齐
        QRectF textRect = boundingRect().translated(-textWidth - 10, 0);  // 根据文本长度动态调整区域，留出10像素的间距
        textRect.setWidth(textWidth);  // 设置文本区域的宽度，确保名称的最后字符靠近端口
        textRect.setHeight(textHeight);
        painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, m_name);  // 名称放在左侧，右对齐
    }
}

void BlueprintPort::SetNodeType(int type) noexcept {
    m_parentNodeType = type;
}

int BlueprintPort::GetNodeType() noexcept {
    return m_parentNodeType;
}

void BlueprintPort::SetPortFont(const Blueprint::BlueprintFont &font) noexcept {
    m_font = font;
}

void BlueprintPort::initializeGraphicsItem() noexcept {
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true); // 允许发送几何变化
    setAcceptHoverEvents(true);
    setZValue(2);
}

QPointF BlueprintPort::centerPos() const {
    return mapToScene(boundingRect().center());  // 返回端口的中心点
}

void BlueprintPort::SetDataType(int dataType) noexcept {
    m_dataType = dataType;
}

void BlueprintPort::SetName(QString &name) noexcept {
    m_name = name;
}

void BlueprintPort::SetPortType(PortType type) noexcept {
    m_type = type;
}

int BlueprintPort::GetDataType() noexcept {
    return m_dataType;
}

QString BlueprintPort::GetName() noexcept {
    return m_name;
}

PortType BlueprintPort::GetPortType() noexcept {
    return m_type;
}
#include "../include/BlueprintClass.h"

void BlueprintPort::sendDataToConnectedPorts() noexcept {
    // 获取当前场景
    QGraphicsScene *currentScene = this->scene();
    if (!currentScene) return;

    // 获取 QBlueprint 视图
    BlueprintClass *blueprintView = dynamic_cast<BlueprintClass*>(currentScene->views().first());

    if (blueprintView) {

    }
}

void BlueprintPort::updateConnections() noexcept {
    // 检查当前场景是否存在
    QGraphicsScene *currentScene = this->scene();
    if (!currentScene) return;  // 如果场景不存在，直接返回

    BlueprintClass *blueprintView = dynamic_cast<BlueprintClass*>(currentScene->views().first());

    if (blueprintView) {
        // 更新该端口相关的所有连接
        blueprintView->updateConnectionsForPort(this);
    }
}

void BlueprintPort::removeConnections() noexcept {
    QGraphicsScene *currentScene = this->scene();
    if (!currentScene || currentScene->views().isEmpty()) return;
    qDebug() << "w1";
    auto *blueprintView = dynamic_cast<BlueprintClass*>(currentScene->views().first());
    if (!blueprintView) return;
    qDebug() << "w2";
    std::vector<BlueprintConnection*> toRemove;

    for (BlueprintConnection *connection : blueprintView->GetConnections()) {
        if (!connection) continue;

        qDebug() << "w3";
        BlueprintPort *startPort = connection->GetStartPort();
        qDebug() << "ww";
        BlueprintPort *endPort = connection->GetEndPort();
        qDebug() << "w4";
        if (!startPort || !endPort)
            continue;
        qDebug() << "w5";
        if (startPort == this || endPort == this) {
            qDebug() << "w6";
            toRemove.push_back(connection);
        }
    }

    for (BlueprintConnection *connection : toRemove) {
        blueprintView->removeConnection(connection);
    }
}

QString BlueprintPort::GetVarTypeName() const noexcept {
    return QString::fromStdString(m_var.getDataTypeName());
}

QFont BlueprintPort::GetFont() noexcept {
    return m_font.GetFont();
}