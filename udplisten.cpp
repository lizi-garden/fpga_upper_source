#include "udplisten.h"
#include "define.h"

#include <QDebug>
#include <QBuffer>

UdpListen::UdpListen(QObject *parent)
    : QObject{parent}
{
    udpsocket = new QUdpSocket(this);
    udpsocket->bind(QHostAddress::AnyIPv4, 8080);
    connect(udpsocket, &QUdpSocket::readyRead, this, &UdpListen::readPendingDatagrams);
}

auto UdpListen::readPendingDatagrams() -> void
{
    while(udpsocket->hasPendingDatagrams()){
        QHostAddress senderip;
        quint16 senderport;
        Q_ASSERT_X(senderip.setAddress(IP_ADDRESS), "senderip", "Set IP address failed");

        qDebug()<< "audio is being received..." << Qt::endl;
        audio vp;
        memset(&vp, 0, sizeof(vp));
        udpsocket->readDatagram((char*)&vp, sizeof(vp), &senderip, &senderport);
        qDebug() << vp.data << "|" << vp.lens << Qt::endl;
        emit readyRead(vp);

        QBuffer buffer;
        buffer.open(QBuffer::WriteOnly);
        buffer.write(vp.data, vp.lens);
    }
}
