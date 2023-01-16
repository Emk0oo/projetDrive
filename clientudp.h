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

    public slots:
        void processPendingDatagrams();

    private :
        QUdpSocket *socket;
};

#endif // CLIENTUDP_H
