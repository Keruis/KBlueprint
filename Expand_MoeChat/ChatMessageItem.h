//
// Created by keruis on 2025/6/15.
//

#ifndef BLUEPRINT_CHATMESSAGEITEM_H
#define BLUEPRINT_CHATMESSAGEITEM_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QTextLayout>
#include <QTextLine>
#include <QVBoxLayout>
#include <QFont>
#include <QTextEdit>
#include <QSizePolicy>
#include "AvatarWidget.h"
#include "ChatMessageBubble.h"

class ChatMessageItem : public QWidget {
public:
    ChatMessageItem(const QString& nickname,
                    const QString& message,
                    const QString& time,
                    const QString& avatarPath,
                    bool fromSelf,
                    QWidget* parent = nullptr);

private:
    QString m_nickname;
    QString m_message;
    QString m_time;
    QString m_avatarPath;
    bool m_fromSelf;

private:
    QLabel* createNameLabel();
    QLabel* createTimeLabel();
    QWidget* createAvatarWidget();
    QVBoxLayout* createNameAndBubbleLayout();
    void setupLayout();
};

#endif //BLUEPRINT_CHATMESSAGEITEM_H
