#include "player.h"
#include "define.h"

#include <QDebug>
#include <QMediaDevices>

Player::Player(QObject *parent)
    : QObject{parent}
{
    QAudioFormat format;
    format.setSampleRate(SAMPLE_RATE);
    format.setChannelCount(CHANNEL_NUM);
    format.setSampleFormat(SAMPLE_FORMAT);

    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    output = new QAudioSink(format, this);
    connect(output, &QAudioSink::stateChanged, this, &Player::handleStateChanged);
}

void Player::play(QFile *tempFile)
{
    qDebug() << "player start" << Qt::endl;
    if (file == nullptr) {
        qDebug() << "open file failed" << Qt::endl;
        return;
    }

    file = tempFile;
    file->open(QIODevice::ReadOnly);
    output->start(file);
}

void Player::stop()
{
    qDebug() << "player stop" << Qt::endl;
    output->stop();
    file->close();
}

void Player::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            // Finished playing (no more data)
            Player::stop();
            break;

        case QAudio::StoppedState:
            // Stopped for other reasons
            if (output->error() != QAudio::NoError) {
                // Error handling
                qWarning() << "output error" << Qt::endl;
            }
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}
