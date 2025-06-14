#include "ChatMessageItem.h"

ChatMessageItem::ChatMessageItem(const QString& nickname,
                const QString& message,
                const QString& time,
                const QString& avatarPath,
                bool fromSelf,
                QWidget* parent)
        : QWidget(parent),
          m_nickname(nickname),
          m_message(message),
          m_time(time),
          m_avatarPath(avatarPath),
          m_fromSelf(fromSelf)
{
    setupLayout();
}

QLabel* ChatMessageItem::createNameLabel() {
    auto* nameLabel = new QLabel(m_nickname);
    nameLabel->setStyleSheet("color: gray; font-size: 11px;");
    nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    nameLabel->setAlignment(m_fromSelf ? Qt::AlignRight : Qt::AlignLeft);
    return nameLabel;
}

QLabel* ChatMessageItem::createTimeLabel() {
    auto* timeLabel = new QLabel(m_time);
    timeLabel->setStyleSheet("color: gray; font-size: 10px;");
    timeLabel->setAlignment(m_fromSelf ? Qt::AlignRight : Qt::AlignLeft);
    return timeLabel;
}

QWidget* ChatMessageItem::createAvatarWidget() {
    return new AvatarWidget(m_avatarPath, 42);
}

QVBoxLayout* ChatMessageItem::createNameAndBubbleLayout() {
    auto* layout = new QVBoxLayout;
    layout->setSpacing(2);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(createNameLabel());
    layout->addWidget(new ChatBubble(m_message, m_fromSelf));
    layout->addWidget(createTimeLabel());
    return layout;
}

void ChatMessageItem::setupLayout() {
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(8, 4, 8, 4);
    mainLayout->setSpacing(8);

    auto* avatar = createAvatarWidget();
    auto* nameAndBubbleLayout = createNameAndBubbleLayout();

    if (m_fromSelf) {
        mainLayout->addStretch();
        mainLayout->addLayout(nameAndBubbleLayout);
        mainLayout->addWidget(avatar, 0, Qt::AlignTop);
    } else {
        mainLayout->addWidget(avatar, 0, Qt::AlignTop);
        mainLayout->addLayout(nameAndBubbleLayout);
        mainLayout->addStretch();
    }

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}