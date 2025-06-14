#ifndef BLUEPRINT_CHATWIDGET_H
#define BLUEPRINT_CHATWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include "ContentContainer.h"
#include "ChatInterface.h"

class ChatWindow : public QWidget {
Q_OBJECT

public:
    ChatWindow(QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QWidget* m_sidebar = nullptr;
    QPushButton* m_toggleBtn = nullptr;
    QPropertyAnimation* m_animation = nullptr;

    QWidget* m_overlay = nullptr;
    QGraphicsOpacityEffect* m_overlayEffect = nullptr;
    QPropertyAnimation* m_overlayFade = nullptr;

    ContentContainer* m_contentContainer = nullptr;

    void setupUi();
    void setupOverlay();
    void setupSidebar();
    void setupToggleButton();
    void setupAnimations();
    void setupConnections();
    void toggleSidebar();
};

#endif //BLUEPRINT_CHATWIDGET_H
