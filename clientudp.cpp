#include "clientudp.h"
#include <QObject>
ClientUdp::ClientUdp(QObject* parent) : QObject(parent)
{
    //Constructeur

    // Creer un socket udp
      socket= new QUdpSocket();

      // Configuration de l'adresse et le port
      socket->bind(QHostAddress::LocalHost, 4000);

      // Connecté le signal à un slot
      connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

}

ClientUdp::~ClientUdp()
{
    delete socket;
}

void ClientUdp::processPendingDatagrams()
{
    while (socket->hasPendingDatagrams()) {
        // Read the next datagram
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // Process the datagram
        qDebug() << "Received datagram:" << datagram;

    }
}


