#ifndef BLUEPRINT_BLUEPRINTNODE_H
#define BLUEPRINT_BLUEPRINTNODE_H

#include <QObject>
#include <QGraphicsItem>
#include "BlueprintFont.h"
#include "BlueprintPort.h"
#include "../../Container/Vec/Vector.h"

namespace Blueprint {
    class BlueprintNode : public QObject, public QGraphicsItem {
    Q_OBJECT

        Q_INTERFACES(QGraphicsItem)

    public:
        BlueprintNode(int type, int datatype, QGraphicsItem *parent = nullptr);
        ~BlueprintNode();

        void Initialize() noexcept ;
        void Shutdown() noexcept ;

        void SetNodeName(QString name) noexcept ;
        void SetClassName(QString className) noexcept ;
        QString GetClassName() noexcept ;

    private:
        BlueprintFont m_font;
        QString m_className;
        QString m_name;
        int m_dataType;

        Vector<BlueprintPort *> m_inputPorts; // 输入端口
        Vector<BlueprintPort *> m_outputPorts; // 输出端口
        std::vector<int> m_dataTypes;       // 存储节点支持的数据类型

    };
}

#endif //BLUEPRINT_BLUEPRINTNODE_H
