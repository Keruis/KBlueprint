#ifndef BLUEPRINT_AUDIOPLAYER_H
#define BLUEPRINT_AUDIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QBuffer>

class AudioPlayer : public QObject {
Q_OBJECT

public:
    explicit AudioPlayer(QObject* parent = nullptr);
    void playAudio(const QByteArray& audioData);
    void stop();

private:
    QMediaPlayer* m_player;
    QAudioOutput* m_audioOutput;
    QBuffer m_buffer;

signals:
    void playbackFinished();
};


#endif //BLUEPRINT_AUDIOPLAYER_H
