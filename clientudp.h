#ifndef CLIENTUDP_H
#define CLIENTUDP_H
#include <QUdpSocket>
#include <QObject>
#include <iostream>

class ClientUdp : public QObject
{
    Q_OBJECT
public:

    explicit ClientUdp(QObject *parent = 0);
    virtual ~ClientUdp();
    QUdpSocket *socket;
    QByteArray message;
    QByteArray datagram;

    public slots:
        void processPendingDatagrams();
        QByteArray getDatagram();

    private :

signals:
     void ordreRecu(QByteArray datagram);

};

#endif // CLIENTUDP_H
