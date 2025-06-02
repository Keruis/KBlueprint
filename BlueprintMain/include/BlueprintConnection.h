#ifndef BLUEPRINT_BLUEPRINTCONNECTION_H
#define BLUEPRINT_BLUEPRINTCONNECTION_H

#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "BlueprintPort.h"

namespace Blueprint {
    class BlueprintConnection : public QObject, public QGraphicsItem {
    Q_OBJECT;
    Q_INTERFACES(QGraphicsItem)
    public:
        BlueprintConnection(BlueprintPort* startPort, BlueprintPort* endPort, QGraphicsItem* parent = nullptr);
        ~BlueprintConnection();

        void Initialize() noexcept ;
        void Shutdown() noexcept ;

        void UpdatePosition(const QPointF& startPos, const QPointF& endPos) noexcept ;

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        void SetEndPort(BlueprintPort *endPort);

        BlueprintPort* GetEndPort() const;
        BlueprintPort* GetStartPort() const;

    private:
        void setupAnimation();
        void clearSelection();
        QColor getColorFromType(const std::string& nodeName);

    protected:
        QPainterPath shape() const override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
        BlueprintPort* m_startPort = nullptr;
        BlueprintPort* m_endPort = nullptr;

        QColor m_startColor;
        QColor m_endColor;

        QPointF m_startPoint;
        QPointF m_endPoint;

        QTimer* m_animationTimer;
        qreal m_animationProgress;
    };
}


#endif //BLUEPRINT_BLUEPRINTCONNECTION_H