#include "LeftToolBar.h"

LeftToolBar::LeftToolBar(QWidget* parent)
    : QWidget(parent),
      m_buttonGroup(new QButtonGroup(this))
{

}

LeftToolBar::~LeftToolBar() {

}

void LeftToolBar::Initialize() noexcept {
    this->setFixedWidth(50);
//    this->setStyleSheet("background-color: green;");

    QVBoxLayout* toolLayout = new QVBoxLayout(this);
    toolLayout->setContentsMargins(0, 0, 0, 0);
    toolLayout->setSpacing(10);

    QWidget* topSpacer = new QWidget(this);
    topSpacer->setFixedHeight(2);
    toolLayout->addWidget(topSpacer);

    QStringList icons = {
            ":/icons/LeftTool/folder.svg",
            ":/icons/LeftTool/audio.svg",
            ":/icons/LeftTool/blueprint.svg"
    };

    QStringList texts = {
            "folder",
            "audio",
            "BP"
    };

    m_buttonGroup->setExclusive(true);

    for (int i = 0; i < icons.size(); i++) {
        QToolButton* btn = createSvgButton(icons[i], texts[i]);
        toolLayout->addWidget(btn);

        btn->setCheckable(true);
        if (i == 0) btn->setChecked(true);

        m_buttonGroup->addButton(btn, i);

        connect(btn, &QToolButton::clicked, this, [this, i](){
            emit buttonClicked(i);
        });

        btn->setStyleSheet(R"(
            QToolButton {
                border: none;
                background: transparent;
                border-radius: 6px;
            }
            QToolButton:hover {
                background-color: rgba(255, 255, 255, 0.1);
            }
            QToolButton:checked {
                background-color: rgba(255, 255, 255, 0.2);
            }
        )");
    }

    toolLayout->addStretch();

    QToolButton* btnTerminal = createSvgButton(":/icons/LeftTool/terminal.svg");
    toolLayout->addWidget(btnTerminal);

    btnTerminal->setStyleSheet(R"(
            QToolButton {
                border: none;
                background: transparent;
                border-radius: 5px;
            }
            QToolButton:hover {
                background-color: rgba(255, 255, 255, 0.1);
            }
        )");
    connect(btnTerminal, &QToolButton::clicked, this, [this](){
        emit buttonClicked(-1);
    });
}

QToolButton *LeftToolBar::createSvgButton(const QString &svgPath) noexcept {
    QToolButton* button = new QToolButton(this);
    QIcon icon(svgPath);
    button->setIcon(icon);
    button->setIconSize(QSize(24, 24));
    button->setFixedSize(48, 48);
    return button;
}

QToolButton* LeftToolBar::createSvgButton(const QString& svgPath, const QString& text) noexcept {
    QToolButton* button = new QToolButton(this);
    QIcon icon(svgPath);
    button->setIcon(icon);
    button->setText(text);
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->setIconSize(QSize(20, 20));
    button->setFixedSize(48, 48);
    button->setStyleSheet("QToolButton { "
                          "     border: none; "
                          "     font-size: 5px;"
                          "}");
    return button;
}