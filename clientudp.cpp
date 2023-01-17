#include "clientudp.h"
#include <QObject>
ClientUdp::ClientUdp(QObject* parent) : QObject(parent)
{
    //Constructeur

    // Creer un socket udp
      socket= new QUdpSocket(this);

      // Configuration de l'adresse et le port
      socket->bind(QHostAddress("10.78.5.147"), 4000);

      // Connecté le signal à un slot
      connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
      qDebug() << "Serveur UDP en écoute:";


}

ClientUdp::~ClientUdp()
{
    delete socket;
}

void ClientUdp::processPendingDatagrams()
{
    qDebug() << "reception";
    while (socket->hasPendingDatagrams()) {
        // Read the next datagram

        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        qDebug() << "Received datagram:" << datagram;

        qDebug() << datagram[0];

        emit ordreRecu(datagram);
    }

}


QByteArray ClientUdp::getDatagram()
{
    return datagram;
}


