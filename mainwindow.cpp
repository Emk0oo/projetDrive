#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
using namespace std;
//#define PORT "/dev/ttyUSB0"
#include "clientudp.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonDeconnexion->setDisabled(true);
    //ui->envoyer->setDisabled(true);
    //ui->textEdit->setDisabled(true);

    //connect(serie, SIGNAL(timeout()), this, SLOT(on_envoyer_clicked()));
    ClientUdp recepteur;
    recepteur.processPendingDatagrams();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonConnexion_clicked()
{
    const QString PORT= "/dev/ttyUSB0"; //chemin vers le port série !!!!!
    serie= new QSerialPort(PORT);

    //configuration de la liaison

    serie->setBaudRate(QSerialPort::Baud9600);
    serie->setDataBits(QSerialPort::Data8);
    serie->setParity(QSerialPort::NoParity);
    serie->setStopBits(QSerialPort::OneStop);
    serie->setFlowControl(QSerialPort::NoFlowControl);

    serie->open(QIODevice::ReadWrite);


    //test de l'ouverture de la connexion

    if (serie->isOpen()==true)
    {
        ui->information->setTextColor(Qt::green);
        ui->information->setText("Port ouvert");

        ui->pushButtonConnexion->setDisabled(true);
        ui->pushButtonDeconnexion->setEnabled(true);
        ui->envoyer->setEnabled(true);
        ui->textEdit->setEnabled(true);
    }
    else {
        ui->information->setTextColor(Qt::red);
        ui->information->setText("Port non ouvert");

    }

}

void MainWindow::on_pushButtonDeconnexion_clicked()
{
    serie->close();

    if (serie->isOpen()==true)
    {
        ui->information->setText("La deconnexion a echoue");
    }
    else {
        ui->information->setText("La deconnexion a reussie");
        ui->pushButtonConnexion->setEnabled(true);
        ui->pushButtonDeconnexion->setDisabled(true);
        ui->envoyer->setDisabled(true);
        ui->textEdit->setDisabled(true);
    }

    delete serie;
}

void MainWindow::on_envoyer_clicked()
{

        QByteArray trame;

        int i;
        for (i=0;i<5;i++){
            trame[i]=0x00;
        }

        trame.append(0x01);
        trame.append(0x7A); //'z';
        trame.append(0x30); //'0';
        trame.append(0x30); //'0';
        trame.append(0x02); //2
        trame.append(0x41); //'A';
        trame.append(0x41); //'A';

        trame.append(ui->textEdit->toPlainText()); //on récupère les char du textEdit

        trame.append(0x04);
        QString trameqs = QString::fromStdString(trame.toStdString());
        qDebug() << trameqs;
        serie->write(trame);



        QByteArray trame2;

        int a;
        for (a=0;a<5;a++){
            trame2[a]=0x00;
        }

        trame2.append(0x01);
        trame2.append(0x7A); //'z';
        trame2.append(0x30); //'0';
        trame2.append(0x30); //'0';
        trame2.append(0x02); //2
        trame2.append(0x41); //'A';
        trame2.append(0x42); //'A';

        trame2.append(""); //on récupère les char du textEdit
        trame2.append(0x04);

        serie->write(trame2);

//faire recepteur udp


}

void MainWindow::on_clear_clicked()
{
    ui->textEdit->clear();
    on_envoyer_clicked();
}


