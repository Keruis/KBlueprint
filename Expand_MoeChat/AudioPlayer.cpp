#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(QObject* parent) : QObject(parent) {
    m_audioOutput = new QAudioOutput(this);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_audioOutput);

    connect(m_player, &QMediaPlayer::playbackStateChanged, this, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            emit playbackFinished();
        }
    });
}

#include <QTemporaryFile>
#include <QFile>
#include <QDebug>
#include <QDir>

void AudioPlayer::playAudio(const QByteArray& audioData) {
    stop();

    QTemporaryFile* tempFile = new QTemporaryFile(QDir::tempPath() + "/qt_audio_XXXXXX.wav", this);
    if (tempFile->open()) {
        tempFile->write(audioData);
        qDebug() << audioData.toStdString() ;
        tempFile->flush();
        tempFile->close();

        m_player->setSource(QUrl::fromLocalFile(tempFile->fileName()));
        m_player->play();
        qDebug() << "[AudioPlayer] 是否能播放？状态:" << m_player->error() << m_player->errorString();

        qDebug() << "[AudioPlayer] 播放中:" << tempFile->fileName();
    } else {
        qWarning() << "[AudioPlayer] 无法写入临时文件，无法播放音频";
    }
}

void AudioPlayer::stop() {
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->stop();
    }
    m_buffer.close();
}