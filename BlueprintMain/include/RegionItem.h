#ifndef BLUEPRINT_REGIONITEM_H
#define BLUEPRINT_REGIONITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPainter>
#include <QString>
#include <QList>
#include <QInputDialog>

#include "BlueprintFont.h"

class RegionItem : public QGraphicsRectItem {
public:
    enum ResizeDirection {
        NoResize,
        ResizeLeft,
        ResizeRight,
        ResizeTop,
        ResizeBottom,
        ResizeLeftTop,
        ResizeRightTop,
        ResizeLeftBottom,
        ResizeRightBottom
    };

    RegionItem(QGraphicsItem* parent = nullptr, const QString& name = "TEST") ;

    void Initialize() noexcept ;
    QString GetName() noexcept ;
    void SetName(const QString& name) noexcept ;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override ;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override ;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override ;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override ;

private:
    ResizeDirection calculateResizeDirection(const QPointF& pos) noexcept ;
    void adjustSize(const QPointF& currentPos) noexcept ;

private:
    QRectF m_textRect;
    Blueprint::BlueprintFont m_font;
    QString m_name;
    ResizeDirection m_resizeDirection;
    QPointF m_dragStartPos;
};

#endif //BLUEPRINT_REGIONITEM_H
