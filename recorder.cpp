#include "recorder.h"
#include "define.h"
#include "codec.h"

#include <QDebug>
#include <QMediaDevices>

Recorder::Recorder(QObject *parent)
    : QObject{parent}
{
    // 录制文件
    saveFile.setFileName(RECORD_FILENAME);
    saveFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

    // 音频流格式设定
    QAudioFormat format;
    format.setSampleRate(SAMPLE_RATE);
    format.setChannelCount(CHANNEL_NUM);
    format.setSampleFormat(SAMPLE_FORMAT);

    // 检查输入设备支持
    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
    }

    // 获取输入设备并跟踪
    input = new QAudioSource(format, this);
    connect(input, &QAudioSource::stateChanged, this, &Recorder::handleStateChanged);
}

// 开始录制
void Recorder::start(QFile *tempFile)
{
    if (tempFile == nullptr){
        qDebug() << "open file is null" << Qt::endl;
        return;
    }

    qDebug() << "recorder start" << Qt::endl;
    file = tempFile;
    input->start(file);
}

// 暂停录制
void Recorder::pause()
{
    qDebug() << "recorder pause" << Qt::endl;
    input->stop();
}

// 结束录制
void Recorder::end()
{
    qDebug() << "recorder end" << Qt::endl;
    input->stop();
    qDebug() << "save file to " << saveFile.fileName() << Qt::endl;
    Codec::pcm2wav(file->fileName(), saveFile.fileName());
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
