#include "../include/BlueprintConnection.h"

Blueprint::BlueprintConnection::BlueprintConnection(Blueprint::BlueprintPort *startPort,
                                                    Blueprint::BlueprintPort *endPort, QGraphicsItem *parent) {

}

Blueprint::BlueprintConnection::~BlueprintConnection() {

}

void Blueprint::BlueprintConnection::UpdatePosition(const QPointF &startPos, const QPointF &endPos) noexcept {

}

QRectF Blueprint::BlueprintConnection::boundingRect() const {
    return QRectF();
}

void Blueprint::BlueprintConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

void Blueprint::BlueprintConnection::SetEndPort(Blueprint::BlueprintPort *endPort) {

}

Blueprint::BlueprintPort *Blueprint::BlueprintConnection::GetEndPort() const {
    return nullptr;
}

Blueprint::BlueprintPort *Blueprint::BlueprintConnection::GetStartPort() const {
    return nullptr;
}

QPainterPath Blueprint::BlueprintConnection::shape() const {
    return QGraphicsItem::shape();
}

void Blueprint::BlueprintConnection::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
}
