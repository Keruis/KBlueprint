#ifndef BLUEPRINT_BLUEPRINTCONNECTION_H
#define BLUEPRINT_BLUEPRINTCONNECTION_H

#include <QObject>
#include <QGraphicsItem>
#include "BlueprintPort.h"

namespace Blueprint {
    class BlueprintConnection : public QObject, public QGraphicsItem {
    Q_OBJECT;
    Q_INTERFACES(QGraphicsItem)
    public:
        BlueprintConnection(BlueprintPort* startPort, BlueprintPort* endPort, QGraphicsItem* parent = nullptr);
        ~BlueprintConnection();

        void UpdatePosition(const QPointF& startPos, const QPointF& endPos) noexcept ;

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        void SetEndPort(BlueprintPort *endPort);

        BlueprintPort* GetEndPort() const;
        BlueprintPort* GetStartPort() const;

    protected:
        QPainterPath shape() const override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
        BlueprintPort* m_startPort;
        BlueprintPort* m_endPort;
        bool m_isSelected = false;
    };
}


#endif //BLUEPRINT_BLUEPRINTCONNECTION_H