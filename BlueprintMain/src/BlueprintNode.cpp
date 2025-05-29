#include "../include/BlueprintNode.h"

using namespace Blueprint;

import NodeType;
import DataType;


#include <QPushButton>


BlueprintNode::BlueprintNode(int type, int datatype, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_dataTypes(datatype),
      m_nodeType(type),
      m_nodeStyle("NodeStyle.xml")
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 100)); // 半透明黑色
    shadowEffect->setOffset(15, 15); // 阴影偏移

    this->setGraphicsEffect(shadowEffect);
}

BlueprintNode::~BlueprintNode() {
    Shutdown();
}

void BlueprintNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);

    if (!scene()) return;

    QPointF scenePos = this->scenePos();
    QGraphicsItem* newParent = nullptr;

    QList<QGraphicsItem*> itemsAtPos = scene()->items(scenePos, Qt::IntersectsItemShape, Qt::DescendingOrder);
    for (QGraphicsItem* item : itemsAtPos) {
        if (auto region = dynamic_cast<RegionItem*>(item)) {
            newParent = region;
            break;
        }
    }

    if (newParent != parentItem()) {
        QPointF oldScenePos = this->scenePos();
        setParentItem(newParent);
        QPointF newPos = newParent ? newParent->mapFromScene(oldScenePos) : oldScenePos;
        setPos(newPos);
    }
}

void BlueprintNode::SetClassName(QString className) noexcept {
    m_className = std::move(className);
}

void BlueprintNode::SetNodeName(QString name) noexcept {
    m_name = std::move(name);
}

QString BlueprintNode::GetClassName() noexcept {
    return m_className;
}

const Vector<BlueprintPort *> &BlueprintNode::GetInputPorts() const noexcept {
    return m_inputPorts;
}

const Vector<BlueprintPort *> &BlueprintNode::GetOutputPorts() const noexcept {
    return m_outputPorts;
}

void BlueprintNode::Initialize(int type) noexcept {
    auto& nodeManager = Types::NodeTypeManager::instance();

    // 启用拖动（节点可以被鼠标拖动）
    setFlag(QGraphicsItem::ItemIsMovable);
    // 启用选择（节点可以被点击选中）
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setFlag(QGraphicsItem::ItemAcceptsInputMethod, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setZValue(1);

    SetNodeType(type);
    if(m_nodeType == nodeManager.getTypeId("FUNCTION") || m_nodeType == nodeManager.getTypeId("BRANCH") /*|| nodeType == Type::CONDITION*/ || m_nodeType == nodeManager.getTypeId("FORLOOP"))
        customNodePortSort();
    else
        addButtonToTopLeft();
}

void BlueprintNode::Shutdown() noexcept {
    for (BlueprintPort *port : m_inputPorts) {
        port->removeConnections();
    }
    for (BlueprintPort *port : m_outputPorts) {
        port->removeConnections();
    }
}

BlueprintNode *BlueprintNode::clone() const {
    auto& nodeManager = Types::NodeTypeManager::instance();
    BlueprintNode* newNode = new BlueprintNode(this->m_nodeType,this->m_dataType);
    newNode->SetNodeName(this->m_name);
    newNode->SetClassName(this->m_className);
    newNode->SetNodeType(this->m_nodeType);
    newNode->Initialize(m_nodeType);

    qDebug() << "node type :" << m_nodeType;

    if(newNode->GetNodeType() != nodeManager.getTypeId("INPUT")
        && newNode->GetNodeType() != nodeManager.getTypeId("BRANCH")
        && newNode->GetNodeType() != nodeManager.getTypeId("CONDITION")
        && newNode->GetNodeType() != nodeManager.getTypeId("FORLOOP")) {
        newNode->AddInputPort(nodeManager.getTypeId("FUNCTION"));
        newNode->AddOutputPort(nodeManager.getTypeId("FUNCTION"));
    } else if (newNode->GetNodeType() == nodeManager.getTypeId("BRANCH")) {
        newNode->AddInputPort(nodeManager.getTypeId("BRANCH"));
        newNode->AddOutputPort(nodeManager.getTypeId("BRANCH"));
    } else if (newNode->GetNodeType() == nodeManager.getTypeId("CONDITION")) {
        newNode->addButtonToTopLeft(nodeManager.getTypeId("CONDITION"));
    } else if (newNode->GetNodeType() == nodeManager.getTypeId("FORLOOP")) {
        newNode->AddInputPort(nodeManager.getTypeId("FORLOOP"));
        newNode->AddOutputPort(nodeManager.getTypeId("FORLOOP"));
    }
    for (BlueprintPort* port : this->m_inputPorts) {
        BlueprintPort* clonedPort = port->clone();
        clonedPort->setParentItem(newNode);
        newNode->m_inputPorts.push_back(clonedPort);
    }

    // 克隆输出端口
    for (auto port : this->m_outputPorts) {
        BlueprintPort* clonedPort = port->clone(); // 假设 QBlueprintPort 有一个 clone 方法
        clonedPort->setParentItem(newNode); // 设置父项为新的 QBlueprintNode
        newNode->m_outputPorts.push_back(clonedPort);
    }
    // 设置克隆节点的初始位置
    newNode->setPos(this->pos());

    return newNode;
}

void BlueprintNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // 设置节点的背景为圆角矩形
    QRectF rect = boundingRect();
    m_nodeStyle.paintNode(painter, rect, m_nodeType, m_name);

    customNodePortSort();

    update();
}

QRectF BlueprintNode::boundingRect() const {
    QFont font;
    QFontMetrics fontMetrics(font);
    auto& nodeManager = Types::NodeTypeManager::instance();

    // 计算输入端口名称的最大宽度
    int maxInputWidth = 0;
    for (const auto& port : m_inputPorts) {
        int textWidth = fontMetrics.horizontalAdvance(port->GetName());
        if (textWidth > maxInputWidth) {
            maxInputWidth = textWidth;
        }
    }
    // 计算输出端口名称的最大宽度
    int maxOutputWidth = 0;
    for (const auto& port : m_outputPorts) {
        int textWidth = fontMetrics.horizontalAdvance(port->GetName());
        if (textWidth > maxOutputWidth) {
            maxOutputWidth = textWidth;
        }
    }

    int padding = 80;
    if(m_nodeType == nodeManager.getTypeId("CONDITION"));
        maxInputWidth = 57;
    int nodeWidth = maxInputWidth + maxOutputWidth + padding;
    int count = 0;
    int nodeHeight = std::max(m_inputPorts.size(), m_outputPorts.size()) * 31 + 31;

    if (m_nodeType == nodeManager.getTypeId("INPUT")) {
        int maxLineEditWidth = 0;
        for(const auto& lineEdit : m_lineEdits)
        {
            if(maxLineEditWidth < lineEdit->width())
                maxLineEditWidth = lineEdit->width();
        }
        nodeWidth += maxLineEditWidth;
    } else if (m_nodeType == nodeManager.getTypeId("OUTPUT")) {
        int maxLabelWidth = 0;
        for(const auto& label : m_outputLabel)
        {
            if(maxLabelWidth < label->width())
                maxLabelWidth = label->width();
        }
        nodeWidth += maxLabelWidth;
    } else if (m_nodeType == nodeManager.getTypeId("CONDITION")) {
        nodeWidth += 50;
        for (size_t i = 0; i < m_inputPorts.size(); ++i) {
            if(m_inputPorts[i]->GetName() == "E1" || m_inputPorts[i]->GetName() == "E2")
                count ++;
            else if(m_inputPorts[i]->GetName() == "Condition")
                count +=2;
        }
        if(count > 2)
            nodeHeight = std::max(m_inputPorts.size(), m_outputPorts.size()) * 31 + 31 + (count/2 - 1) * 20;
    }
    return QRectF(0, 0, nodeWidth, nodeHeight);
}

QString BlueprintNode::GetNodeName() noexcept {
    return m_name;
}

void BlueprintNode::SetNodeType(int nodetype) noexcept {
    m_nodeType = nodetype;
}

QFont BlueprintNode::GetFont() noexcept {
    return m_font.GetFont();
}

int BlueprintNode::GetNodeType() noexcept {
    return m_nodeType;
}

BlueprintPort *BlueprintNode::AddInputPort() noexcept {
    auto& dataManager = Types::DataTypeManager::instance();
    BlueprintPort *port = new BlueprintPort(this, PortType::Input, "NULL", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
    port->SetNodeType(m_nodeType);
    SetVariantType(port);
    m_inputPorts.push_back(port);
    return port;
}

BlueprintPort *BlueprintNode::AddOutputPort() noexcept {
    auto& dataManager = Types::DataTypeManager::instance();
    BlueprintPort *port = new BlueprintPort(this, PortType::Output, "NULL", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
    port->SetNodeType(m_nodeType);
    SetVariantType(port);
    m_inputPorts.push_back(port);
    return port;
}

BlueprintPort *BlueprintNode::AddInputPort(const QString &name) noexcept {
    auto& dataManager = Types::DataTypeManager::instance();
    BlueprintPort *port = new BlueprintPort(this, PortType::Input, name, m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
    port->SetNodeType(m_nodeType);
    SetVariantType(port);
    m_inputPorts.push_back(port);
    return port;
}

BlueprintPort *BlueprintNode::AddOutputPort(const QString &name) noexcept {
    auto& dataManager = Types::DataTypeManager::instance();
    BlueprintPort *port = new BlueprintPort(this, PortType::Output, name, m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
    port->SetNodeType(m_nodeType);
    SetVariantType(port);
    m_outputPorts.push_back(port);
    return port;
}

void BlueprintNode::AddInputPort(int type) noexcept {
    auto& nodeManager = Types::NodeTypeManager::instance();
    auto& dataManager = Types::DataTypeManager::instance();
    if(type == nodeManager.getTypeId("FUNCTION")) {
        BlueprintPort *port = new BlueprintPort(this, PortType::EVENT_INPUT, "", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port->SetNodeType(m_nodeType);
        SetVariantType(port);
        m_inputPorts.push_back(port);
    } else if (type == nodeManager.getTypeId("BRANCH")) {
        BlueprintPort *port = new BlueprintPort(this, PortType::EVENT_INPUT, "", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        BlueprintPort *port_Condition = new BlueprintPort(this, PortType::Input, "Condition", dataManager.getTypeId("BOOL"), QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port->SetNodeType(m_nodeType);
        SetVariantType(port);
        port_Condition->SetNodeType(m_nodeType);
        SetVariantType(port_Condition);
        m_inputPorts.push_back(port);
        m_inputPorts.push_back(port_Condition);
        customNodePortSort();
        addOutputLabel(port, port);

    } else if (type == nodeManager.getTypeId("CONDITION")) {
        BlueprintPort *port = new BlueprintPort(this, PortType::Input, "E1", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port->SetNodeType(m_nodeType);
        SetVariantType(port);
        m_inputPorts.push_back(port);
        customNodePortSort();
        addOutputLabel(port, port);
        BlueprintPort *port2 = new BlueprintPort(this, PortType::Input, "E2", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port2->SetNodeType(m_nodeType);
        SetVariantType(port2);
        m_inputPorts.push_back(port2);
        customNodePortSort();
        addOutputLabel(port2, port2);
        addLineEdit(port, port2);
        if(m_inputPorts.size()>2)
            addRadioButtonOptions(port);
        port->SetVarType(int());
        port2->SetVarType(int());

    } else {
        BlueprintPort *port = new BlueprintPort(this, PortType::EVENT_INPUT, "", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port->SetNodeType(m_nodeType);
        SetVariantType(port);
        m_inputPorts.push_back(port);
    }
}

void BlueprintNode::AddOutputPort(int type) noexcept {
    auto& nodeManager = Types::NodeTypeManager::instance();
    auto& dataManager = Types::DataTypeManager::instance();
    if(type == nodeManager.getTypeId("FUNCTION")) {
        BlueprintPort *port = new BlueprintPort(this, PortType::EVENT_INPUT, "", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port->SetNodeType(m_nodeType);
        SetVariantType(port);
        m_outputPorts.push_back(port);
    } else if (type == nodeManager.getTypeId("BRANCH")) {
        BlueprintPort *port_return_true = new BlueprintPort(this, PortType::EVENT_TRUE_RETURN, "True", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        BlueprintPort *port_return_false = new BlueprintPort(this, PortType::EVENT_FALSE_RETURN, "False", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
        port_return_true->SetNodeType(m_nodeType);
        SetVariantType(port_return_true);
        port_return_false->SetNodeType(m_nodeType);
        SetVariantType(port_return_false);
        m_outputPorts.push_back(port_return_true);
        m_outputPorts.push_back(port_return_false);
        customNodePortSort();
    } else if (Type == nodeManager.getTypeId("CONDITION")) {
        if(m_outputPorts.size()==0) {
            BlueprintPort *port = new BlueprintPort(this, PortType::Output, "Condition", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
            port->SetNodeType(m_nodeType);
            SetVariantType(port);
            port->SetVarType(bool());
            m_outputPorts.push_back(port);
        }
    }
}


void BlueprintNode::SetVariantType(BlueprintPort *port) noexcept {
    auto tmp = port->GetDataType();
    switch (tmp) {
        case 0:
            port->SetVarType(int()); // 设置为 int 类型
            break;
        case 1:
            port->SetVarType(float()); // 设置为 float 类型
            break;
        case 2:
            port->SetVarType(double()); // 设置为 double 类型
            break;
        case 3:
            port->SetVarType(char()); // 设置为 char 类型
            break;
    }
}

void BlueprintNode::addOutputLabel(BlueprintPort *outport, BlueprintPort *inport) noexcept {
    QLabel* pLabel = nullptr; // 声明基类指针
    auto& nodeManager = Types::NodeTypeManager::instance();
    // 根据端口数据类型选择合适的 QLabel 类型
    pLabel = new QLabel("");

    pLabel->setStyleSheet("QLineEdit { border: 1px solid black; border-radius: 0px; padding: 2px; }");

    // 创建 QGraphicsProxyWidget 并将 QLineEdit 添加到该代理
    QGraphicsProxyWidget* pMyProxy = new QGraphicsProxyWidget(this); // 代理作为 QGraphicsItem 的子项
    pMyProxy->setWidget(pLabel); // 将 QWidget 基类对象添加到代理中

    // 设置较高的 Z 值，确保控件显示在前景
    pMyProxy->setZValue(10);
    pLabel->setMinimumWidth(50);
    pLabel->setMinimumHeight(10);
    QPointF outputPortPos = inport->pos();
    QFontMetrics fontMetrics(inport->GetFont());
    int outputTextWidth = fontMetrics.horizontalAdvance(inport->GetName());
    pMyProxy->setPos(outputPortPos.x() + outputTextWidth + 30, outputPortPos.y() - 3);
    // 设置克隆的 QLineEdit 大小与原始的一致
    if(inport->GetName() == "Condition")
        pMyProxy->resize(QSize(50, 20));
    if(m_nodeType == nodeManager.getTypeId("BRANCH"))
        pMyProxy->resize(QSize(50, 20));
    else
        pMyProxy->resize(QSize(60, 20));

    // 添加克隆的 QLineEdit 到新的节点的 lineEdits 列表
    m_outputLabel.push_back(pLabel);
}

void BlueprintNode::customNodePortSort() noexcept {
    auto& nodeManager = Types::NodeTypeManager::instance();
    if(m_nodeType == nodeManager.getTypeId("CONDITION"))
    {
        // 排列输入端口
        int count = 0;
        for (size_t i = 0; i < m_inputPorts.size(); ++i) {
            QFontMetrics fontMetrics(m_inputPorts[i]->GetFont());
            int inputTextWidth = fontMetrics.horizontalAdvance(m_inputPorts[i]->GetName());
            m_inputPorts[i]->setPos(5, i * 30 + 40 + (count/2) * 20); // 左边距15，纵向位置
            if(m_inputPorts[i]->GetName() == "E1" || m_inputPorts[i]->GetName() == "E2")
                count ++;
            else if(m_inputPorts[i]->GetName() == "Condition")
                count +=2;
        }
        // 排列输出端口
        for (size_t i = 0; i < m_outputPorts.size(); ++i) {
            QFontMetrics fontMetrics(m_outputPorts[i]->GetFont());
            int outputTextWidth = fontMetrics.horizontalAdvance(m_outputPorts[i]->GetName());
            m_outputPorts[i]->setPos(boundingRect().width() - 15, i * 60 + 40); // 右边距15
        }
    }
    else {
        // 排列输入端口
        for (size_t i = 0; i < m_inputPorts.size(); ++i) {
            QFontMetrics fontMetrics(m_inputPorts[i]->GetFont());
            int inputTextWidth = fontMetrics.horizontalAdvance(m_inputPorts[i]->GetName());
            m_inputPorts[i]->setPos(5, i * 30 + 40); // 左边距15，纵向位置
        }
        // 排列输出端口
        for (size_t i = 0; i < m_outputPorts.size(); ++i) {
            QFontMetrics fontMetrics(m_outputPorts[i]->GetFont());
            int outputTextWidth = fontMetrics.horizontalAdvance(m_outputPorts[i]->GetName());
            if(m_nodeType == nodeManager.getTypeId("CONDITION")) // 条件节点的输出端口是需要间隔一个output的
                m_outputPorts[i]->setPos(boundingRect().width() - 15, i * 60 + 40); // 右边距15
            else
                m_outputPorts[i]->setPos(boundingRect().width() - 15, i * 30 + 40); // 右边距15
        }
    }
}

void BlueprintNode::addLineEdit(BlueprintPort *port1, BlueprintPort *port2) noexcept {
    // 创建 QLineEdit
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText("条件");  // 设置提示文本
    lineEdit->setStyleSheet("QLineEdit { border: 1px solid black; padding: 2px; }");  // 设置样式
    lineEdit->resize(80, 20);

    // 创建 QGraphicsProxyWidget 并将 lineEdit 添加到代理
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);
    pMyProxy->setWidget(lineEdit);

    // 设置 Z 值，确保控件显示在前景
    pMyProxy->setZValue(10);

    // 设置代理的位置
    QPointF outputPortPos = port2->pos();
    pMyProxy->setPos(outputPortPos.x() - lineEdit->width() + 233, (outputPortPos.y()) - 3);

    // 将 lineEdit 添加到列表中
    m_lineEdits.push_back(lineEdit);
    m_relation.push_back("");  // 初始化为一个空的 QString，占据与该 lineEdit 对应的位置

    // 使用 QRegularExpressionValidator 限制输入条件符号
    QRegularExpression regex(R"(>|<|=|>=|<=|!=)");  // 允许的符号
    QValidator *validator = new QRegularExpressionValidator(regex, this);
    lineEdit->setValidator(validator);
    int currentIndex = m_lineEdits.size() - 1;  // 当前 lineEdit 的索引
    connect(lineEdit, &QLineEdit::textChanged, this, [&](const QString &text) {
        QStringList allowedConditions = {">", "<", "=", ">=", "<=", "!="};
        if (allowedConditions.contains(text.trimmed())) {
            m_relation[currentIndex] = text.trimmed();  // 将输入的条件符号存入 relation 的对应位置
            qDebug() << "输入条件符号：" << m_relation[currentIndex];

        } else {
            qDebug() << "无效输入，当前仅支持条件符号：" << allowedConditions;
        }
    });
}

void BlueprintNode::addRadioButtonOptions(BlueprintPort *port) noexcept {
    // 创建 QWidget 作为 QGraphicsProxyWidget 的容器
    QWidget *containerWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);  // 使用水平布局管理器

    // 设置布局的间距和边距
    layout->setSpacing(5);  // 控件之间的间距
    layout->setContentsMargins(0, 0, 0, 0);  // 去掉边距

    // 创建两个 QRadioButton 用于选择 || 和 &&
    QRadioButton *orOption = new QRadioButton("||");
    QRadioButton *andOption = new QRadioButton("&&");

    // 设置单选按钮的大小
    orOption->setFixedSize(40, 20);
    andOption->setFixedSize(40, 20);

    // 默认选中 || 选项
    orOption->setChecked(true);

    // 初始化 radioButtonOptions 和 radioButtonValues
    m_radioButtonOptions.emplace_back(orOption, andOption);
    m_radioButtonValues.push_back("||");  // 默认选中 "||"

    // 将单选按钮添加到布局
    layout->addWidget(orOption);
    layout->addWidget(andOption);

    // 创建 QGraphicsProxyWidget 并将 containerWidget 添加到代理
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);
    pMyProxy->setWidget(containerWidget);

    // 设置代理的位置
    QPointF portPos = port->pos();
    pMyProxy->setPos(portPos.x(), portPos.y() - 30);  // 调整位置以适应布局

    // 确保布局适合代理的大小
    containerWidget->setLayout(layout);
    containerWidget->setFixedSize(235, 20);  // 缩小容器的大小

    unsigned long currentIndex = m_radioButtonOptions.size() - 1;  // 获取当前的索引
    qDebug() << "radioButtonValues:" <<m_radioButtonValues.size();
    // 连接单选按钮的信号到槽函数，用于处理选择的变化
//    connect(orOption, &QRadioButton::toggled, this, [&](bool checked) {
//        if (checked) {
//            m_radioButtonValues[currentIndex] = "||";
//            qDebug() << "选择了 || 选项";
//
//        }
//    });
//
//    connect(andOption, &QRadioButton::toggled, this, [&](bool checked) {
//        if (checked) {
//            m_radioButtonValues[currentIndex] = "&&";
//            qDebug() << "选择了 && 选项";
//            //processData(nullptr, QVariant());
//
//        }
//    });
}

void BlueprintNode::addButtonToTopLeft() noexcept {
    auto& nodeManager = Types::NodeTypeManager::instance();

    // 创建 QPushButton
    QPushButton* button = new QPushButton("+");
    // 创建 QGraphicsProxyWidget 并将按钮嵌入其中
    QGraphicsProxyWidget* buttonProxy = new QGraphicsProxyWidget(this);
    // 设置按钮的大小，按钮应该是一个正方形以便显示成圆形
    int buttonSize = 10;
    button->setFixedSize(buttonSize, buttonSize);
    // 使用样式表将按钮绘制成一个圆
    button->setStyleSheet(
            "QPushButton {"
            "    background-color: #DFFFD6;"  // 按钮背景颜色（绿色）
            "    color: black;"  // 按钮文字颜色（白色）
            "    border: none;"  // 无边框
            "    border-radius: 5px;"  // 设置圆角半径，半径为按钮尺寸的一半
            "}"
            "QPushButton:pressed {"
            "    background-color: #DFFFD6;"  // 点击时的背景颜色
            "}"
    );
    buttonProxy->setWidget(button);
    buttonProxy->setPos(10, 5);

    // 设置按钮的点击事件
    connect(button, &QPushButton::clicked, [&]() {
        qDebug() << "Button clicked! - addButtonToTopLeft";
        addInputPortCondition(nodeManager.getTypeId("FUNCTION"));
    });
}

void BlueprintNode::addButtonToTopLeft(int type) noexcept {
    // 创建 QPushButton
    QPushButton* button = new QPushButton("+");
    // 创建 QGraphicsProxyWidget 并将按钮嵌入其中
    QGraphicsProxyWidget* buttonProxy = new QGraphicsProxyWidget(this);
    // 设置按钮的大小，按钮应该是一个正方形以便显示成圆形
    int buttonSize = 10;
    button->setFixedSize(buttonSize, buttonSize);
    // 使用样式表将按钮绘制成一个圆
    button->setStyleSheet(
            "QPushButton {"
            "    background-color: #2196F3;"  // 按钮背景颜色（蓝色）
            "    color: white;"  // 按钮文字颜色（白色）
            "    border: none;"  // 无边框
            "    border-radius: 0px;"  // 设置圆角半径，半径为按钮尺寸的一半
            "}"
            "QPushButton:pressed {"
            "    background-color: #45a049;"  // 点击时的背景颜色
            "}"
    );
    buttonProxy->setWidget(button);
    buttonProxy->setPos(25, 10);

    // 设置按钮的点击事件
    connect(button, &QPushButton::clicked, [this](){
        //addInputPortCondition(Type::CONDITION);
        qDebug() << "Clicked";
    });
}

void BlueprintNode::addInputPortCondition(int type) noexcept {
    auto& dataManager = Types::DataTypeManager::instance();
    BlueprintPort *port =new BlueprintPort(this, PortType::Input, "Test", m_dataType, QString::fromStdString(dataManager.getTypeName(m_dataType)));
    port->SetNodeType(m_nodeType);
    SetVariantType(port);
    m_inputPorts.push_back(port);
    AddOutputPort(Type);
    customNodePortSort();
    addOutputLabel(port, port);
    if(m_inputPorts.size()>1) {
        addRadioButtonOptions(port);
    }
    port->SetVarType(bool());
}

