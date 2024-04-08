#include "player.h"

#include <QDebug>
#include <QMediaDevices>

Player::Player(QObject *parent)
    : QObject{parent}
{
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::UInt8);

    QAudioDevice info = QMediaDevices::defaultAudioOutput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    output = new QAudioSink(format, this);
    connect(output, &QAudioSink::stateChanged, this, &Player::handleStateChanged);
}

void Player::play()
{
    qDebug() << "player start" << Qt::endl;
    file.setFileName("test.mp3");
    file.open(QIODevice::ReadOnly);

    outputDevice = output->start();
}

void Player::stop()
{
    qDebug() << "player stop" << Qt::endl;
    output->stop();
    file.close();
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
