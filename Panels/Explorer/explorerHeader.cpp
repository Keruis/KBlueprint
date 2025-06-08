#include "explorerHeader.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

ExplorerHeader::ExplorerHeader(QWidget* parent) : QWidget(parent) {
    setFixedHeight(30);

    setupUi();
    setupConnections();
    setupAnimations();
}

void ExplorerHeader::setupUi() {
    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(6, 2, 6, 2);
    layout->setSpacing(4);

    auto* label = new QLabel("EXPLORER", this);
    label->setStyleSheet("color: white; font-weight: bold;");

    m_line = new QFrame();
    m_line->setFrameShape(QFrame::VLine);
    auto* effect = new QGraphicsOpacityEffect(m_line);
    effect->setOpacity(0.0);
    m_line->setGraphicsEffect(effect);
    m_line->setVisible(false);

    m_addBtn = createIconButton(":/icons/explorer/add.svg", "Add");
    m_expandBtn = createIconButton(":/icons/explorer/expandSelected.svg", "Expand All");
    m_collapseBtn = createIconButton(":/icons/explorer/collapseAll.svg", "Collapse All");
    m_collapseBtn->setIconSize(QSize(18, 18));

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(m_addBtn);
    layout->addWidget(m_line);
    layout->addWidget(m_expandBtn);
    layout->addWidget(m_collapseBtn);
}

QPushButton* ExplorerHeader::createIconButton(const QString& iconPath, const QString& tooltip) {
    auto* button = new QPushButton(this);
    button->setIcon(QIcon(iconPath));
    button->setToolTip(tooltip);
    button->setFlat(true);
    button->setCursor(Qt::PointingHandCursor);
    button->setFixedSize(25, 25);
    button->setIconSize(QSize(20, 20));
    button->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            padding: 2px;
            border-radius: 4px;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 0.1); /* 浅灰，适合深色背景 */
        }
        QPushButton:pressed {
            background-color: rgba(255, 255, 255, 0.2);
        }
    )");
    // 添加透明效果
    auto* effect = new QGraphicsOpacityEffect(button);
    effect->setOpacity(0.0);
    button->setGraphicsEffect(effect);
    button->setVisible(false);

    return button;
}

void ExplorerHeader::setupConnections() {
    connect(m_addBtn, &QPushButton::clicked, this,&ExplorerHeader::addRequested);
    connect(m_expandBtn, &QPushButton::clicked, this, &ExplorerHeader::expandRequested);
    connect(m_collapseBtn, &QPushButton::clicked, this, &ExplorerHeader::collapseRequested);
}

void ExplorerHeader::setupAnimations() {
    m_addAnim = new QPropertyAnimation(m_addBtn->graphicsEffect(), "opacity", this);
    m_lineAnim = new QPropertyAnimation(m_line->graphicsEffect(), "opacity", this);
    m_expandAnim = new QPropertyAnimation(m_expandBtn->graphicsEffect(), "opacity", this);
    m_collapseAnim = new QPropertyAnimation(m_collapseBtn->graphicsEffect(), "opacity", this);

    for (auto* anim : {m_addAnim, m_lineAnim, m_expandAnim, m_collapseAnim}) {
        anim->setDuration(200);
        anim->setEasingCurve(QEasingCurve::InOutQuad);
    }
}

void ExplorerHeader::setButtonsVisible(bool visible) {
    if (visible) {
        m_addBtn->setVisible(true);
        m_line->setVisible(true);
        m_expandBtn->setVisible(true);
        m_collapseBtn->setVisible(true);
        animateOpacity(m_addAnim, 1.0);
        animateOpacity(m_lineAnim, 1.0);
        animateOpacity(m_expandAnim, 1.0);
        animateOpacity(m_collapseAnim, 1.0);
    } else {
        animateOpacity(m_addAnim, 0.0);
        animateOpacity(m_lineAnim, 0.0);
        animateOpacity(m_expandAnim, 0.0);
        animateOpacity(m_collapseAnim, 0.0);

        connect(m_addAnim, &QPropertyAnimation::finished, this, [this]() {
            if (m_addAnim->endValue().toDouble() == 0.0)
                m_addBtn->setVisible(false);
        });
        connect(m_lineAnim, &QPropertyAnimation::finished, this, [this]() {
            if (m_lineAnim->endValue().toDouble() == 0.0)
                m_line->setVisible(false);
        });
        connect(m_expandAnim, &QPropertyAnimation::finished, this, [this]() {
            if (m_expandAnim->endValue().toDouble() == 0.0)
                m_expandBtn->setVisible(false);
        });
        connect(m_collapseAnim, &QPropertyAnimation::finished, this, [this]() {
            if (m_collapseAnim->endValue().toDouble() == 0.0)
                m_collapseBtn->setVisible(false);
        });
    }
}

void ExplorerHeader::animateOpacity(QPropertyAnimation* animation, qreal endValue) {
    if (!animation)
        return;

    auto* effect = qobject_cast<QGraphicsOpacityEffect*>(animation->targetObject());
    if (!effect)
        return;

    animation->stop();
    animation->setStartValue(effect->opacity());
    animation->setEndValue(endValue);
    animation->start();
}