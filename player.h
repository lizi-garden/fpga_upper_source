#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QFile>
#include <QAudioSink>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void play(QString fileName);
    void pause();
    void stop();

private:
    void handleStateChanged(QAudio::State newState);

    QFile file;
    QAudioSink *output;
    QIODevice *outputDevice;

signals:

};

#endif // PLAYER_H
