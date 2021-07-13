#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include<QThread>
#include<QUdpSocket>
#include<QByteArray>
#include<QImage>

class UdpThread : public QThread
{
    Q_OBJECT
public:
    UdpThread(QObject *parent = nullptr);
    void closeThread();
    QUdpSocket *m_udpSocket;
protected:
    void run();
signals:
    void recevie_success(QImage img); //值传递
public slots:
    void processPendingDatagram();
private:
    QByteArray m_buf;
    volatile bool is_stop;
    bool is_finished;
};

#endif // UDPTHREAD_H
