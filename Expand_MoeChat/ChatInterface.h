#ifndef BLUEPRINT_CHATINTERFACE_H
#define BLUEPRINT_CHATINTERFACE_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineEdit>
#include "ChatMessageItem.h"

class ChatInterface : public QWidget {
    Q_OBJECT

public:
    ChatInterface(QWidget* parent = nullptr);

public slots:
    void addMessage(const QString& text, bool fromSelf);
    void sendMessage();

private:
    QVBoxLayout* m_messagesLayout;
    QScrollArea* m_scrollArea;
    QLineEdit* m_input;
};


#endif //BLUEPRINT_CHATINTERFACE_H
