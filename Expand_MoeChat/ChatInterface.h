#ifndef BLUEPRINT_CHATINTERFACE_H
#define BLUEPRINT_CHATINTERFACE_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QTime>
#include <QQueue>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QFile>
#include <QScrollBar>
#include <QLineEdit>
#include <thread>
#include <QBuffer>
#include <QNetworkReply>
#include "ChatMessageItem.h"
#include "AudioPlayer.h"

class ChatInterface : public QWidget {
    Q_OBJECT

public:
    ChatInterface(QWidget* parent = nullptr);
    void scrollToBottom();

public slots:
    void addMessage(const QString& text, bool fromSelf);
    void appendMessageToUI(const QString& message);
    QNetworkReply* sendToTTS(const QString& base64Audio);
    void sendMessage();
    void tryPlayNext();
    void processNextPendingChunk();

private:
    QString m_fullReply;
    AudioPlayer* m_audioPlayer;
    QVBoxLayout* m_messagesLayout;
    QScrollArea* m_scrollArea;
    QLineEdit* m_input;
    struct StreamedChunk {
        QString message;
        QByteArray audioData;
        QString base64Audio;
        bool done = false;
    };
    QQueue<QVariantMap> m_pendingChunks;
    QQueue<StreamedChunk> m_audioQueue;
    bool m_isPlaying = false;

    struct ChatMessage {
        QString role;
        QString content;
    };
    QVector<ChatMessage> m_contextMessages;
};


#endif //BLUEPRINT_CHATINTERFACE_H
