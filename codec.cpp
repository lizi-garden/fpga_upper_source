#include "codec.h"
#include "define.h"

#include <QFile>
#include <QIODevice>
#include <QDebug>


Codec::Codec(QObject *parent)
    : QObject{parent}
{

}


qint64 Codec::pcm2wav(QString pcmFileName, QString wavFileName)
{
    // 开始设置WAV的文件头
    WAVFILE_HEADER WavFileHeader;
    qstrcpy(WavFileHeader.RiffName, "RIFF");
    qstrcpy(WavFileHeader.WavName, "WAVE");
    qstrcpy(WavFileHeader.FmtName, "fmt ");
    qstrcpy(WavFileHeader.DataName,"data");

    WavFileHeader.nFmtLength = 16;              // 表示FMT块的长度
    WavFileHeader.nAudioFormat = 1;             // 表示按照PCM编码
    WavFileHeader.nChannleNumber = CHANNEL_NUM; // 声道数目
    WavFileHeader.nSampleRate = SAMPLE_RATE;    // 采样频率

    // nBytesPerSample 和 nBytesPerSecond这两个值通过设置的参数计算得到;
    // 数据块对齐单位(每个采样需要的字节数 = 通道数 × 每次采样得到的样本数据位数 / 8 )
    WavFileHeader.nBytesPerSample = CHANNEL_NUM * SAMPLE_BITS / 8;

    // 波形数据传输速率
    // (每秒平均字节数 = 采样频率 × 通道数 × 每次采样得到的样本数据位数 / 8  = 采样频率 × 每个采样需要的字节数 )
    WavFileHeader.nBytesPerSecond = SAMPLE_RATE * CHANNEL_NUM * SAMPLE_BITS / 8;

    // 每次采样得到的样本数据位数;
    WavFileHeader.nBitsPerSample = SAMPLE_BITS;

    QFile cacheFile(pcmFileName);
    QFile wavFile(wavFileName);

    Q_ASSERT_X(cacheFile.open(QIODevice::ReadOnly), "cacheFile", "open cacheFile failed");
    Q_ASSERT_X(wavFile.open(QIODevice::WriteOnly | QIODevice::Truncate), "cacheFile", "open waveFile failed");

    qint32 nSize = sizeof(WavFileHeader);
    qint64 nFileLen = cacheFile.bytesAvailable();

    WavFileHeader.nRiffLength = quint32(nFileLen - 8 + nSize);
    WavFileHeader.nDataLength = quint32(nFileLen);

    // 先将wav文件头信息写入，再将音频数据写入;
    wavFile.write((const char *)&WavFileHeader, nSize);
    wavFile.write(cacheFile.readAll());

    cacheFile.close();
    wavFile.close();

    return nFileLen;
}
