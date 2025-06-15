#include "ChatInterface.h"

ChatInterface::ChatInterface(QWidget* parent)
    : QWidget(parent)
{
    m_audioPlayer = new AudioPlayer(this);

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
    m_scrollArea->verticalScrollBar()->setStyleSheet(R"(
        QScrollBar:vertical {
            background: rgba(45, 45, 45, 100);
            width: 8px;
            border: none;
        }

        QScrollBar::handle:vertical {
            background: rgba(85, 85, 85, 180);
            min-height: 20px;
            border-radius: 0;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical,
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: transparent;
            border: none;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0px;
            subcontrol-origin: margin;
        }

        QScrollBar:horizontal {
            background: #2d2d2d;
            height: 8px;
            margin: 0px 0px 0px 0px;
            border: none;
        }
        QScrollBar::handle:horizontal {
            background: #555;
            min-width: 20px;
            border-radius: 0px;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 0px;
            subcontrol-origin: margin;
        }
    )");
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

void ChatInterface::scrollToBottom() {
    QScrollBar* vBar = m_scrollArea->verticalScrollBar();
    QTimer::singleShot(50, this, [vBar]() {
        vBar->setValue(vBar->maximum());
    });
}

void ChatInterface::addMessage(const QString& text, bool fromSelf) {
    QString nickname = fromSelf ? "我" : "对方";
    QString time = QTime::currentTime().toString("HH:mm:ss");
    QString avatarPath = fromSelf ? ":/resource/self.jpg" : ":/resource/other.jpg";

    auto* item = new ChatMessageItem(nickname, text, time, avatarPath, fromSelf);
    m_messagesLayout->addWidget(item);
    scrollToBottom();
}

void ChatInterface::appendMessageToUI(const QString& message) {
    addMessage(message, false);
    scrollToBottom();
}

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>

#include <QNetworkAccessManager>

QNetworkReply* ChatInterface::sendToTTS(const QString& base64Audio) {
    QNetworkRequest asrRequest(QUrl("http://localhost:18080/api/tts"));
    asrRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["data"] = base64Audio;
    QByteArray json = QJsonDocument(obj).toJson();

    QNetworkAccessManager* asrManager = new QNetworkAccessManager(this);
    QNetworkReply* asrReply = asrManager->post(asrRequest, json);

    return asrReply;
}

void ChatInterface::sendMessage() {
    QString text = m_input->text().trimmed();
    if (text.isEmpty()) return;

    addMessage(text, true);
    m_input->clear();
    scrollToBottom();

    m_contextMessages.append({ "user", text });

    m_fullReply.clear();
    m_pendingChunks.clear();

    QJsonArray messages;
    for (const auto& m : m_contextMessages) {
        QJsonObject obj;
        obj["role"] = m.role;
        obj["content"] = m.content;
        messages.append(obj);
    }
    QJsonObject payload;
    payload["msg"] = messages;

    QNetworkRequest request(QUrl("http://localhost:18080/chat-stream"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "text/event-stream");

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->post(request, QJsonDocument(payload).toJson());

    QObject::connect(reply, &QIODevice::readyRead, this, [reply, this]() mutable {
        while (reply->canReadLine()) {
            QByteArray line = reply->readLine().trimmed();
            if (line.startsWith("data: ")) {
                QByteArray jsonData = line.mid(6);
                QJsonParseError err;
                QJsonDocument doc = QJsonDocument::fromJson(jsonData, &err);
                if (!doc.isObject()) continue;

                QJsonObject obj = doc.object();
                m_pendingChunks.enqueue(obj.toVariantMap());

                tryPlayNext();
            }
        }
    });
}

void ChatInterface::tryPlayNext() {
    if (m_isPlaying) return;

    while (!m_pendingChunks.isEmpty()) {
        QVariantMap map = m_pendingChunks.dequeue();
        QJsonObject obj = QJsonObject::fromVariantMap(map);
        QString message = obj["message"].toString();
        QString fileBase64 = obj["file"].toString();
        bool done = obj["done"].toBool();

        m_fullReply += message;

        if (!fileBase64.isEmpty()) {
            StreamedChunk chunk;
            chunk.message = message;
            chunk.base64Audio = fileBase64;
            chunk.audioData = QByteArray::fromBase64(fileBase64.toUtf8().trimmed());
            chunk.done = done;

            m_audioQueue.enqueue(chunk);
        } else {
            appendMessageToUI(message);
            if (done && m_audioQueue.isEmpty() && m_pendingChunks.isEmpty()) {
                m_contextMessages.append({ "assistant", m_fullReply });
            }
        }
    }

    if (!m_audioQueue.isEmpty()) {
        m_isPlaying = true;
        StreamedChunk chunk = m_audioQueue.dequeue();
        appendMessageToUI(chunk.message);
        m_audioPlayer->playAudio(chunk.audioData);

        disconnect(m_audioPlayer, nullptr, this, nullptr);
        connect(m_audioPlayer, &AudioPlayer::playbackFinished, this, [this, chunk]() {
            QNetworkReply* asrReply = sendToTTS(chunk.base64Audio);
            connect(asrReply, &QNetworkReply::finished, this, [this, asrReply, chunk]() {
                if (asrReply->error() == QNetworkReply::NoError) {
                    QByteArray response = asrReply->readAll();
                    QString text = QString::fromUtf8(response);
                    qDebug() << "[TTS结果]:" << text;
                } else {
                    qWarning() << "[TTS请求失败]:" << asrReply->errorString();
                }

                asrReply->deleteLater();
                m_isPlaying = false;

                if (chunk.done && m_pendingChunks.isEmpty() && m_audioQueue.isEmpty()) {
                    m_contextMessages.append({ "assistant", m_fullReply });
                }

                tryPlayNext();
            });
        });
    }
}

void ChatInterface::processNextPendingChunk() {
    if (m_pendingChunks.isEmpty()) return;

    QVariantMap map = m_pendingChunks.dequeue();
    QJsonObject obj = QJsonObject::fromVariantMap(map);
    QString message = obj["message"].toString();
    QString fileBase64 = obj["file"].toString();
    bool done = obj["done"].toBool();

    m_fullReply += message;

    if (!fileBase64.isEmpty()) {
        StreamedChunk chunk;
        chunk.message = message;
        chunk.base64Audio = fileBase64;
        chunk.audioData = QByteArray::fromBase64(fileBase64.toUtf8().trimmed());
        chunk.done = done;

        m_audioQueue.enqueue(chunk);
        tryPlayNext();
    } else {
        appendMessageToUI(message);

        QMetaObject::invokeMethod(this, [this, done]() {
            if (done && m_pendingChunks.isEmpty() && m_audioQueue.isEmpty()) {
                m_contextMessages.append({ "assistant", m_fullReply });
            } else {
                processNextPendingChunk();
            }
        }, Qt::QueuedConnection);
    }
}