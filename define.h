#ifndef DEFINE_H
#define DEFINE_H

#include <QAudioFormat>

// recorder
#define SAMPLE_RATE     16000
#define CHANNEL_NUM     1
#define SAMPLE_BITS     16
#define SAMPLE_FORMAT   QAudioFormat::Int16

#define RECORD_FILENAME "fpga_record.wav"


// udpListen
#define IP_ADDRESS      "198.168.0.1"

#endif // DEFINE_H
