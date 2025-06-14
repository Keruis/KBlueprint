#include "ChatInterface.h"

ChatInterface::ChatInterface(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(4);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget* scrollContent = new QWidget;
    m_messagesLayout = new QVBoxLayout(scrollContent);
    m_messagesLayout->setAlignment(Qt::AlignTop);
    m_scrollArea->setWidget(scrollContent);

    layout->addWidget(m_scrollArea, 1);

    auto* inputLayout = new QHBoxLayout;
    m_input = new QLineEdit(this);
    m_input->setPlaceholderText("输入消息...");
    auto* sendBtn = new QPushButton("发送", this);

    inputLayout->addWidget(m_input);
    inputLayout->addWidget(sendBtn);

    layout->addLayout(inputLayout);

    connect(sendBtn, &QPushButton::clicked, this, &ChatInterface::sendMessage);
    connect(m_input, &QLineEdit::returnPressed, this, &ChatInterface::sendMessage);
}

void ChatInterface::addMessage(const QString& text, bool fromSelf) {
    QString nickname = fromSelf ? "我" : "对方";
    QString time = QTime::currentTime().toString("HH:mm:ss");
    QString avatarPath = fromSelf ? ":/resource/self.jpg" : ":/resource/other.jpg";

    auto* item = new ChatMessageItem(nickname, text, time, avatarPath, fromSelf);
    m_messagesLayout->addWidget(item);

    QTimer::singleShot(0, m_scrollArea->verticalScrollBar(), [scrollBar = m_scrollArea->verticalScrollBar()] {
        scrollBar->setValue(scrollBar->maximum());
    });
}

void ChatInterface::sendMessage() {
    QString text = m_input->text().trimmed();
    if (!text.isEmpty()) {
        addMessage(text, true);
        m_input->clear();

        QTimer::singleShot(500, this, [=]() {
            addMessage("这是对方的回复", false);
        });
    }
}