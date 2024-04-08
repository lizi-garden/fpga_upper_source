#include "udplisten.h"

UdpListen::UdpListen(QObject *parent)
    : QObject{parent}
{
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(QHostAddress::Any, 10004);
    connect(udpsocket, &QUdpSocket::readyRead, this, &UdpListen::readyReadSlot);
}

void UdpListen::readyReadSlot()
{
    while(udpsocket->hasPendingDatagrams()){
        QHostAddress senderip;
        quint16 senderport;
        qDebug()<< "audio is being received..." << Qt::endl;
        audio vp;
        memset(&vp, 0, sizeof(vp));
        udpsocket->readDatagram((char*)&vp, sizeof(vp), &senderip, &senderport);
        qDebug() << vp.data << "|" << vp.lens << Qt::endl;
        emit readyRead(vp);         // 把收取到的数据发送给录制
    }
}
