#ifndef BLUEPRINT_BLUEPRINTNODE_H
#define BLUEPRINT_BLUEPRINTNODE_H

#include <QObject>
#include <QGraphicsItem>
#include "BlueprintFont.h"
#include "BlueprintPort.h"
#include "../../Container/Vec/Vector.h"

class BlueprintNode : public QObject, public QGraphicsItem {
    Q_OBJECT

    Q_INTERFACES(QGraphicsItem)

public:
    BlueprintNode();
    ~BlueprintNode();

private:
    BlueprintFont m_font;
    QString m_className;
    QString m_name;

    Vector<int> m_inputPorts;
};


#endif //BLUEPRINT_BLUEPRINTNODE_H
