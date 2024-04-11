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

    void start();
    void pause();
    void end();

    struct audio {
        char data[1024];
        qint64 lens;
    };

    bool testMode = false;

private:
    void handleStateChanged(QAudio::State newState);

    QTemporaryFile tempFile;
    QFile file;
    QAudioSource *input;
    QIODevice *inputDevice;

signals:

};

#endif // RECORDER_H
