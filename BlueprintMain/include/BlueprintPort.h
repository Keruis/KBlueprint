#ifndef BLUEPRINT_BLUEPRINTPORT_H
#define BLUEPRINT_BLUEPRINTPORT_H

#include <QGraphicsItem>
#include <QFont>
#include <QObject>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QPolygonF>
#include "BlueprintFont.h"
#include "../Types/PortType.h"

namespace Blueprint {
    class BlueprintPort : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    public:
        BlueprintPort(QGraphicsItem* parent,
                      PortType type,
                      const QString& name,
                      int dataType,
                      QString brief
                      );
        ~BlueprintPort();

        void Initialization() noexcept;
        void Shutdown() noexcept;

    public:
        virtual BlueprintPort* clone() const noexcept ;
        QRectF boundingRect() const noexcept;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) noexcept ;

        void SetPortFont(const BlueprintFont& font) noexcept ;
        void SetNodeType(int type) noexcept ;
        int GetNodeType() noexcept ;
        void SetPortType(PortType type) noexcept ;
        PortType GetPortType() noexcept ;
        void SetName(QString& name) noexcept;
        QString GetName() noexcept ;
        void SetDataType(int dataType) noexcept ;
        int GetDataType() noexcept ;

        QPointF centerPos() const ;
    private:
        void initializeGraphicsItem() noexcept ;

    private:
        int m_parentNodeType;     //// 所属父节点的类型枚举，用于区分端口所在节点的功能类别（如函数节点、数据节点等）。
        BlueprintFont m_font;           //// 字体
        PortType m_type;                //// 表示端口方向的类型（输入/输出），用于连线逻辑与界面渲染区分。
        QString m_name;                 //// 端口的唯一名称标识，用于界面显示、连接匹配及序列化存储。
        QString m_portBrief;    //// 端口的简要描述字符串，用于调试信息、提示文本或文档生成。
        int m_dataType;         //// 当前端口对应的数据类型，定义此端口所接受或输出的数据种类（如 INT、FLOAT、STRING 等）。
    };
}

#endif //BLUEPRINT_BLUEPRINTPORT_H
