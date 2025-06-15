#include "ChatWidget.h"
#include "FloatingSidebar.h"

ChatWindow::ChatWindow(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: #1e1e1e; color: white;");
    setupUi();
    setupOverlay();
    setupSidebar();
    setupToggleButton();
    setupAnimations();
    setupConnections();
}

bool ChatWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == m_overlay && event->type() == QEvent::MouseButtonPress) {
        m_toggleBtn->click();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void ChatWindow::setupUi() {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_contentContainer = new ContentContainer(this);
    m_contentContainer->setStyleSheet("background-color: #1e1e1e;");
    m_contentContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_contentContainer);

    auto* contentLayout = new QVBoxLayout(m_contentContainer);
    contentLayout->addWidget(new ChatInterface(this));
}

void ChatWindow::setupOverlay() {
    m_overlay = new QWidget(m_contentContainer);
    m_overlay->setGeometry(m_contentContainer->rect());
    m_overlay->hide();
    m_overlay->setStyleSheet("background-color: black;");
    m_overlay->lower();

    m_overlayEffect = new QGraphicsOpacityEffect(m_overlay);
    m_overlay->setGraphicsEffect(m_overlayEffect);

    m_overlayFade = new QPropertyAnimation(m_overlayEffect, "opacity", this);
    m_overlayFade->setDuration(350);
    m_overlayFade->setEasingCurve(QEasingCurve::InOutQuad);

    m_overlay->installEventFilter(this);
}

void ChatWindow::setupSidebar() {
    m_sidebar = new FloatingSidebar(m_contentContainer);
    m_sidebar->setFixedWidth(200);

    m_sidebar->move(-200, 0);
    m_sidebar->resize(200, m_contentContainer->height());
    m_sidebar->hide();
}

void ChatWindow::setupToggleButton() {
    m_toggleBtn = new QPushButton("☰", m_contentContainer);
    m_toggleBtn->setFixedSize(28, 28);
    m_toggleBtn->move(8, 8);
    m_toggleBtn->raise();
    m_toggleBtn->setStyleSheet(R"(
            QPushButton {
                background-color: #444;
                border-radius: 4px;
                color: white;
            }
            QPushButton:hover {
                background-color: #666;
            }
        )");
}

void ChatWindow::setupAnimations() {
    m_animation = new QPropertyAnimation(m_sidebar, "pos", this);
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
}

void ChatWindow::setupConnections() {
    connect(m_toggleBtn, &QPushButton::clicked, this, &ChatWindow::toggleSidebar);

    m_contentContainer->onResize = [this](QResizeEvent*) {
        m_sidebar->resize(200, m_contentContainer->height());
        m_overlay->setGeometry(m_contentContainer->rect());
    };
}

void ChatWindow::toggleSidebar() {
    m_animation->stop();
    m_overlayFade->stop();

    disconnect(m_animation, &QPropertyAnimation::finished, nullptr, nullptr);
    disconnect(m_overlayFade, &QPropertyAnimation::finished, nullptr, nullptr);

    if (!m_sidebar->isVisible()) {
        m_sidebar->show();
        m_overlay->show();
        m_overlay->raise();
        m_sidebar->raise();
        m_toggleBtn->raise();

        m_overlayEffect->setOpacity(0.0);
        m_overlayFade->setStartValue(0.0);
        m_overlayFade->setEndValue(0.5);
        m_overlayFade->start();

        m_animation->setStartValue(QPoint(-m_sidebar->width(), 0));
        m_animation->setEndValue(QPoint(0, 0));
        m_animation->start();
    } else {
        m_animation->setStartValue(QPoint(0, 0));
        m_animation->setEndValue(QPoint(-m_sidebar->width(), 0));

        connect(m_animation, &QPropertyAnimation::finished, this, [=]() {
            m_sidebar->hide();

            m_overlayFade->setStartValue(0.5);
            m_overlayFade->setEndValue(0.0);

            disconnect(m_overlayFade, &QPropertyAnimation::finished, nullptr, nullptr);
            connect(m_overlayFade, &QPropertyAnimation::finished, m_overlay, &QWidget::hide);

            m_overlayFade->start();
        });

        m_animation->start();
    }
}