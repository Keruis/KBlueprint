#ifndef BLUEPRINT_BLUEPRINTNODE_H
#define BLUEPRINT_BLUEPRINTNODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "BlueprintFont.h"
#include "BlueprintPort.h"
#include "../../Container/Vec/Vector.h"
#include "../Draw/PaintNode.h"
#include "RegionItem.h"

namespace Blueprint {
    class BlueprintNode : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    public:
        BlueprintNode(int type, int datatype, QGraphicsItem *parent = nullptr);
        ~BlueprintNode();

        void Initialize(int type) noexcept ;
        void Shutdown() noexcept ;

        BlueprintNode *clone() const;

        void SetNodeName(QString name) noexcept ;
        void SetClassName(QString className) noexcept ;
        void SetNodeType(int nodetype) noexcept;
        int GetNodeType() noexcept ;
        QString GetClassName() noexcept ;
        QString GetNodeName() noexcept ;
        QFont GetFont() noexcept ;

        BlueprintPort* AddInputPort() noexcept ;
        BlueprintPort* AddOutputPort() noexcept ;
        BlueprintPort* AddInputPort(const QString& name) noexcept ;
        BlueprintPort* AddOutputPort(const QString& name) noexcept ;
        void AddInputPort(int type) noexcept ;
        void AddOutputPort(int type) noexcept ;

        void SetVariantType(BlueprintPort* port) noexcept ;

        [[nodiscard]] const std::vector<BlueprintPort*>& GetInputPorts() const noexcept ;
        [[nodiscard]] const std::vector<BlueprintPort*>& GetOutputPorts() const  noexcept ;

    private:
        void addOutputLabel(BlueprintPort* outport, BlueprintPort* inport) noexcept;
        void customNodePortSort() noexcept;
        void addLineEdit(BlueprintPort* port1, BlueprintPort* port2) noexcept ;
        void addRadioButtonOptions(BlueprintPort* port) noexcept ;
        void addButtonToTopLeft() noexcept ;
        void addButtonToTopLeft(int type) noexcept ;
        void addInputPortCondition(int type) noexcept ;

    protected:
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override ;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        QRectF boundingRect() const override;

    private:
        Paint::NodeStyle m_nodeStyle;

        QGraphicsBlurEffect* m_blurEffect;

        BlueprintFont m_font;
        QString m_className;
        QString m_name;
        int m_dataType{};
        int m_nodeType;

        std::vector<BlueprintPort *> m_inputPorts; // 输入端口
        std::vector<BlueprintPort *> m_outputPorts; // 输出端口
        Vector<int> m_dataTypes;       // 存储节点支持的数据类型

        Vector<QLineEdit*> m_lineEdits;
        Vector<QLabel*> m_inputLabel;
        Vector<QLabel*> m_outputLabel;

        Vector<QString> m_relation; // 存放关系 ><=等

        std::vector<std::pair<QRadioButton*, QRadioButton*>> m_radioButtonOptions; // 存放关系 || &&
        Vector<QString> m_radioButtonValues;
    };
}

#endif //BLUEPRINT_BLUEPRINTNODE_H
