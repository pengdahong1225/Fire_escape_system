#include "udpthread.h"
#include<QImage>
#include<QDebug>
#include<QBuffer>

UdpThread::UdpThread(QObject *parent):QThread (parent)
{
//    is_stop = false;
//    is_finished = false;
//    m_udpSocket = new QUdpSocket(this);
//    m_udpSocket->bind(45454,QUdpSocket::ShareAddress);
//    connect(m_udpSocket,&QUdpSocket::readyRead,this,&UdpThread::processPendingDatagram);
}

void UdpThread::closeThread()
{
    is_stop = false;
}

void UdpThread::run()  //run()函数执行结束后会发出 finished信号，代表线程执行结束
{
    qDebug()<<"udp线程begin";
    int i=0;
    int j=1;
    while(true)
    {
        qDebug()<<i++<<QThread::currentThreadId();
        QString path = QString("D:/Codes/Qt/untitled/pic/%1.jpg").arg(j++);

        sleep(1);
    }
}

void UdpThread::processPendingDatagram()
{
    qDebug()<<"有数据";
    QByteArray datagram;
    QBuffer buffer(&datagram);
    buffer.open(QIODevice::ReadWrite);

    int value_size = static_cast<int>(this->m_udpSocket->pendingDatagramSize());
    datagram.resize(value_size);
    qDebug()<<value_size;
    //接收数据报放到datagram中
    m_udpSocket->readDatagram(datagram.data(),datagram.size());
    qDebug()<<datagram.data();
    //去头





    //base64转字符串
//    QByteArray decryptedByte;
//    decryptedByte = QByteArray::fromBase64(datagram.data());
//    QImage to_image;
//    to_image.loadFromData(decryptedByte);
//    if(!to_image.isNull())
//        emit recevie_success(to_image);
}
