#include "../include/BlueprintNode.h"

using namespace Blueprint;

BlueprintNode::BlueprintNode(int type, int datatype, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_dataTypes(datatype)
{

}

BlueprintNode::~BlueprintNode() {

}

void BlueprintNode::SetClassName(QString className) noexcept {
    m_className = className;
}

void BlueprintNode::SetNodeName(QString name) noexcept {
    m_name = name;
}

QString BlueprintNode::GetClassName() noexcept {
    return m_className;
}