#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QTemporaryFile>
#include <QFile>
#include <QAudioSource>

class Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent = nullptr);

    void start(QFile *tempFile);
    void pause();
    void end();

    struct audio {
        char data[1024];
        qint64 lens;
    };

private:
    void handleStateChanged(QAudio::State newState);

    QFile *file;
    QFile saveFile;
    QAudioSource *input;
    QIODevice *inputDevice;

signals:

};

#endif // RECORDER_H
