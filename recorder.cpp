#include "recorder.h"

#include <QDebug>
#include <QMediaDevices>

Recorder::Recorder(QObject *parent)
    : QObject{parent}
{
    if (testMode) {

    } else {
        QAudioFormat format;
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleFormat(QAudioFormat::UInt8);

        QAudioDevice info = QMediaDevices::defaultAudioInput();
        if (!info.isFormatSupported(format)) {
            qWarning() << "Default format not supported, trying to use the nearest.";
        }

        input = new QAudioSource(format, this);
        connect(input, &QAudioSource::stateChanged, this, &Recorder::handleStateChanged);
    }
}

void Recorder::start()
{
    qDebug() << "recorder start" << Qt::endl;
    if (testMode) {

    } else {


        char buf[1024];
        input->start(file);
        file->setFileName("test.mp3");
        file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    }
}

void Recorder::pause()
{
    qDebug() << "recorder pause" << Qt::endl;
    if (testMode) {

    } else {
        input->stop();
    }
}

void Recorder::end()
{
    qDebug() << "recorder end" << Qt::endl;
    if (testMode) {

    } else {
        input->stop();
        file->close();
    }
}

void Recorder::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::StoppedState:
            if (input->error() != QAudio::NoError) {
                // Error handling
                qWarning() << "input error" << Qt::endl;
            } else {
                // Finished recording
                qDebug() << "input success" << Qt::endl;
            }
            break;

        case QAudio::ActiveState:
            // Started recording - read from IO device
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}
