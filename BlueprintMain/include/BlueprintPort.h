#ifndef BLUEPRINT_BLUEPRINTPORT_H
#define BLUEPRINT_BLUEPRINTPORT_H



#include <QGraphicsItem>
#include <QFont>
#include <QObject>

#include "BlueprintFont.h"

class BlueprintPort : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    void Initialization() noexcept ;
    void Shutdown() noexcept ;

private:
    BlueprintFont* m_font;
};


#endif //BLUEPRINT_BLUEPRINTPORT_H
