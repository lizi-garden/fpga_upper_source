#ifndef UDPLISTEN_H
#define UDPLISTEN_H

#include <QObject>

#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QDebug>

class UdpListen : public QObject
{
    Q_OBJECT
public:
    explicit UdpListen(QObject *parent = nullptr);

    struct audio{
        int lens;
        char data[1024];
    };

signals:
    void readyRead(const audio vp);

private:
    QUdpSocket *udpsocket;

private slots:
    void readPendingDatagrams();

};

#endif // UDPLISTEN_H
