#include "FloatingSidebar.h"
#include "TipButton.h"

FloatingSidebar::FloatingSidebar(QWidget* parent)
        : QWidget(parent)
{
    setFixedWidth(160);
    setupLayout();
    setupTitle();
    setupButtons();
}

void FloatingSidebar::setupLayout() {
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(10, 10, 10, 10);
    m_layout->setSpacing(12);
}

void FloatingSidebar::setupTitle() {
    auto* title = new QLabel("MoeChat");
    title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    title->setStyleSheet(R"(
        background-color: transparent;
        color: #ffffff;
        font-weight: bold;
        font-size: 14px;
    )");
    m_layout->addWidget(title);
    m_layout->addSpacing(10);
}

void FloatingSidebar::setupButtons() {
    m_layout->addWidget(createFlatButton("聊天"));
    m_layout->addWidget(createFlatButton("模型"));
    m_layout->addWidget(createFlatButton("设置"));
    m_layout->addWidget(createFlatButton("关于"));
    m_layout->addStretch();
}

QPushButton* FloatingSidebar::createFlatButton(const QString& text) {
    static const QMap<QString, QString> tipMap = {
            { "聊天",   "打开聊天窗口" },
            { "模型",   "当前模型信息" },
            { "设置",   "打开设置面板" },
            { "关于",   "显示关于信息" }
    };

    auto tip = tipMap.value(text, "");

    auto* btn = new TipButton(text, tip, this);
    btn->setFlat(true);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-color: transparent;
            color: #dddddd;
            text-align: left;
            padding: 6px 4px;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 0.08);
        }
    )");
    return btn;
}