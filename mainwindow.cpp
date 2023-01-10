#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
using namespace std;
//#define PORT "/dev/ttyUSB1"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->information->setText("allo");
    ui->pushButtonDeconnexion->setDisabled(true);
    //ui->envoyer->setDisabled(true);
    //ui->textEdit->setDisabled(true);

    //connect(serie, SIGNAL(timeout()), this, SLOT(on_envoyer_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonConnexion_clicked()
{
    const QString PORT= "/dev/ttyUSB1"; //chemin vers le port série !!!!! remettre ces 2 lignes dans la connexion
    serie= new QSerialPort(PORT); // !!!!! remettre ces 2 lignes dans la connexion

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
        ui->information->setText("Port ouvert");
        ui->pushButtonConnexion->setDisabled(true);
        ui->pushButtonDeconnexion->setEnabled(true);
        ui->envoyer->setEnabled(true);
        ui->textEdit->setEnabled(true);
    }
    else ui->information->setText("Port non ouvert");


}

void MainWindow::on_pushButtonDeconnexion_clicked()
{
    serie->close();

    if (serie->isOpen()==true)
    {
        ui->information->setText("La deconnexion a echoue");
    }
    else {
        ui->information->setText("la deconnexion a reussie");
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

        //string msg1= msg.toStdString();


        /*const char* c= msg.toStdString().c_str(); //on convertit le qstring en char
        //qDebug()<< c;
        i++;
        strcpy(&test[i], c);

        i=i+strlen(c);

        test[i++]=0x04;

        qDebug()<<test[i];

        QByteArray data=QByteArray(test,i); //conversion de char test en QBytteArray
        qDebug() << data;
        serie->write(data);*/



    /*char test[250];

    //on crée la trame avec les caractères nécessaires

    int i;
    for (i=0;i<5;i++){
        test[i]=0x00;
    }

    test[i++]=0x01;
    test[i++]=0x7A; //'z';
    test[i++]=0x30; //'0';
    test[i++]=0x30; //'0';
    test[i++]=0x02; //2
    test[i++]=0x41; //'A';
    test[i++]=0x41; //'A';

    QString msg=ui->textEdit->toPlainText(); //on récupère les char du textEdit

    //string msg1= msg.toStdString();


    const char* c= msg.toStdString().c_str(); //on convertit le qstring en char
    //qDebug()<< c;
    i++;
    strcpy(&test[i], c);

    i=i+strlen(c);

    test[i++]=0x04;

    qDebug()<<test[i];

    QByteArray data=QByteArray(test,i); //conversion de char test en QBytteArray
    qDebug() << data;
    serie->write(data);*/


}
