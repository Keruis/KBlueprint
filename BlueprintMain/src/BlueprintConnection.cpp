#include "../include/BlueprintConnection.h"
#include "../Types/PortType.h"
#include "../include/BlueprintClass.h"

import NodeType;

Blueprint::BlueprintConnection::BlueprintConnection(Blueprint::BlueprintPort *startPort, Blueprint::BlueprintPort *endPort, QGraphicsItem *parent)
        : QGraphicsItem(parent),
          m_startPort(startPort),
          m_endPort(endPort)
{
    auto& manager = Types::NodeTypeManager::instance();
    m_startPoint = startPort->centerPos();

    m_startColor = getColorFromType(manager.getTypeName(startPort->GetNodeType()));

    qDebug() << startPort->GetNodeType();

    if (endPort) {
        m_endPoint = endPort->centerPos();
        m_endColor = getColorFromType(manager.getTypeName(endPort->GetNodeType()));
    } else {
        m_endPoint = m_startPoint;
        m_endColor = QColor(Qt::yellow);
    }

    Initialize();
}

Blueprint::BlueprintConnection::~BlueprintConnection() {

}

void Blueprint::BlueprintConnection::Initialize() noexcept {
    setZValue(2);
    setFlag(QGraphicsItem::ItemIsSelectable, false);

    UpdatePosition(m_startPoint, m_endPoint);

    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, [this]() {
        m_animationProgress += 0.01;
        if (m_animationProgress > 1.0)
            m_animationProgress = 0.0;
        update();  // 触发重绘
    });
}

void Blueprint::BlueprintConnection::Shutdown() noexcept {

}

void Blueprint::BlueprintConnection::UpdatePosition(const QPointF &startPos, const QPointF &endPos) noexcept {
    prepareGeometryChange();
    m_startPoint = startPos;
    m_endPoint = endPos;
    update();
}

QRectF Blueprint::BlueprintConnection::boundingRect() const {
    QPointF controlPoint1, controlPoint2;

    qreal dx = m_endPoint.x() - m_startPoint.x();
    qreal dy = m_endPoint.y() - m_startPoint.y();
    qreal offset = qAbs(dx) * 0.6;

    if (m_startPort->GetPortType() == PortType::Output || m_startPort->GetPortType() == PortType::EVENT_OUTPUT
        || m_startPort->GetPortType() == PortType::EVENT_TRUE_RETURN || m_startPort->GetPortType() == PortType::EVENT_FALSE_RETURN) {
        if (dx > 0) {
            controlPoint1 = m_startPoint + QPointF(offset, 0);
            controlPoint2 = m_endPoint - QPointF(offset, 0);
        } else {
            controlPoint1 = m_startPoint + QPointF(offset, dy * 0.5);
            controlPoint2 = m_endPoint - QPointF(offset, -dy * 0.5);
        }
    } else {
        if (dx > 0) {
            controlPoint1 = m_startPoint - QPointF(offset, 0);
            controlPoint2 = m_endPoint + QPointF(offset, 0);
        } else {
            controlPoint1 = m_startPoint - QPointF(offset, -dy * 0.5);
            controlPoint2 = m_endPoint + QPointF(offset, dy * 0.5);
        }
    }

    QRectF bounding = QRectF(m_startPoint, m_endPoint)
            .united(QRectF(controlPoint1, controlPoint2))
            .normalized()
            .adjusted(-10, -10, 10, 10);

    return bounding;
}

void Blueprint::BlueprintConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPen pen;

    if (isSelected()) {
        // 使用动态渐变效果
        QLinearGradient gradient(m_startPoint, m_endPoint);

        // 动态调整渐变的颜色位置, 使用多个渐变点模拟流动
        int numPoints = 20;  // 渐变点的数量
        for (int i = 0; i <= numPoints; ++i) {
            // 计算每个渐变点的位置和颜色
            qreal position = fmod(m_animationProgress + static_cast<double>(i) / numPoints, 1.0);
            QColor color = (i % 2 == 0) ? Qt::green : Qt::white;  // 交替颜色
            gradient.setColorAt(position, color);
        }

        // 设置连接线的样式，将渐变应用到笔刷
        pen = QPen(QBrush(gradient), 2);  // 使用渐变作为画笔
    } else {
        // 使用静态渐变效果
        QLinearGradient gradient(m_startPoint, m_endPoint);
        gradient.setColorAt(0, m_startColor);  // 设置起始颜色
        gradient.setColorAt(1, m_endColor);    // 设置结束颜色

        // 设置连接线的样式，将渐变应用到笔刷
        pen = QPen(QBrush(gradient), 2);  // 使用渐变作为画笔
    }

    painter->setPen(pen);

    // 创建贝塞尔曲线
    QPainterPath path(m_startPoint);

    // 计算控制点
    QPointF controlPoint1;
    QPointF controlPoint2;

    // 获取起点和终点的位置差
    qreal dx = m_endPoint.x() - m_startPoint.x();
    qreal dy = m_endPoint.y() - m_startPoint.y();
    qreal offset = qAbs(dx) * 0.6;  // 控制点偏移量

    if (m_startPort->GetPortType() == PortType::Output || m_startPort->GetPortType() == PortType::EVENT_OUTPUT
        || m_startPort->GetPortType() == PortType::EVENT_TRUE_RETURN || m_startPort->GetPortType() == PortType::EVENT_FALSE_RETURN) {
        if (dx > 0) {
            controlPoint1 = m_startPoint + QPointF(offset, 0);
            controlPoint2 = m_endPoint - QPointF(offset, 0);
        } else {
            controlPoint1 = m_startPoint + QPointF(offset, dy * 0.5);
            controlPoint2 = m_endPoint - QPointF(offset, -dy * 0.5);
        }
    } else if (m_startPort->GetPortType() == PortType::Input || m_startPort->GetPortType() == PortType::EVENT_INPUT) {
        if (dx > 0) {
            controlPoint1 = m_startPoint - QPointF(offset, 0);
            controlPoint2 = m_endPoint + QPointF(offset, 0);
        } else {
            controlPoint1 = m_startPoint - QPointF(offset, -dy * 0.5);
            controlPoint2 = m_endPoint + QPointF(offset, dy * 0.5);
        }
    }

    // 创建贝塞尔曲线
    path.cubicTo(controlPoint1, controlPoint2, m_endPoint);

    // 绘制曲线
    painter->drawPath(path);
}

void Blueprint::BlueprintConnection::SetEndPort(Blueprint::BlueprintPort *endPort) {
    m_endPort = endPort;
    if (m_endPort) {
        UpdatePosition(m_startPort->centerPos(), m_endPort->centerPos());
        m_startPort->sendDataToConnectedPorts();
    }
}

Blueprint::BlueprintPort *Blueprint::BlueprintConnection::GetEndPort() const {
    return m_endPort;
}

Blueprint::BlueprintPort *Blueprint::BlueprintConnection::GetStartPort() const {
    return m_startPort;
}

QPainterPath Blueprint::BlueprintConnection::shape() const {
    QPainterPath path(m_startPoint);

    // 计算控制点
    QPointF controlPoint1 = m_startPoint + QPointF((m_endPoint.x() - m_startPoint.x()) / 2, 0);
    QPointF controlPoint2 = m_endPoint + QPointF((m_startPoint.x() - m_endPoint.x()) / 2, 0);

    path.cubicTo(controlPoint1, controlPoint2, m_endPoint);

    // 使用路径描边器生成较细的形状
    QPainterPathStroker stroker;
    stroker.setWidth(6); // 线的宽度
    return stroker.createStroke(path);
}

void Blueprint::BlueprintConnection::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    clearSelection();

    // 切换选中状态
    m_animationTimer->start(50);  // 启动动画，每50毫秒更新一次

    // 重绘线条
    update();

    // 保持默认的事件处理
    QGraphicsItem::mousePressEvent(event);
}

void Blueprint::BlueprintConnection::clearSelection() {
    QGraphicsScene *currentScene = this->scene();
    if (!currentScene) return;

    BlueprintClass *blueprintView = dynamic_cast<BlueprintClass*>(currentScene->views().first());
    if (blueprintView) {
        for (BlueprintConnection *connection : blueprintView->GetConnections()) {
            connection->m_animationTimer->stop();  // 停止动画
            connection->update();
        }
    }
    update();
}

#include "../../utils/xml/xml.h"

QColor Blueprint::BlueprintConnection::getColorFromType(const std::string& nodeName) {
    Utils::Xml root;
    QColor color;
    root.load("ConnectionColor.xml");
    std::string StrColor = root["Color"][nodeName].text();
    qDebug() << root["Color"][nodeName].text();
    color.setNamedColor(QString::fromStdString(StrColor));
    if (!color.isValid()) {
        color = Qt::yellow;
    }
    return color;
}
