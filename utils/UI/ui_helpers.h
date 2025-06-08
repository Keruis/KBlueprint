#ifndef BLUEPRINT_UI_HELPERS_H
#define BLUEPRINT_UI_HELPERS_H

#include <QWidget>
#include <QGraphicsOpacityEffect>

inline void setWidgetOpacity(QWidget* widget, qreal opacity) {
    if (!widget) return;

    QGraphicsOpacityEffect* effect = qobject_cast<QGraphicsOpacityEffect*>(widget->graphicsEffect());
    if (!effect) {
        effect = new QGraphicsOpacityEffect(widget);
        widget->setGraphicsEffect(effect);
    }

    effect->setOpacity(opacity);
}

#endif //BLUEPRINT_UI_HELPERS_H
