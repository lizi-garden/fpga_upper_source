#ifndef CODEC_H
#define CODEC_H

#include <QObject>

class Codec : public QObject
{
    Q_OBJECT
public:
    explicit Codec(QObject *parent = nullptr);
    static qint64 pcm2wav(QString pcmFileName, QString wavFileName);

    // Wav 文件数据头
    typedef struct
    {
        // RIFF 头
        char    RiffName[4];
        quint32 nRiffLength;

        // 数据类型标识符
        char    WavName[4];

        // 格式块中的块头
        char    FmtName[4];
        quint32 nFmtLength;

        // 格式块中的块数据
        quint16 nAudioFormat;
        quint16 nChannleNumber;
        quint32 nSampleRate;
        quint32 nBytesPerSecond;
        quint16 nBytesPerSample;
        quint16 nBitsPerSample;

        // 数据块中的块头
        char    DataName[4];
        quint32 nDataLength;
    } WAVFILE_HEADER;

};

#endif // CODEC_H
