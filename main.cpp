#include "mainwindow.h"

#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();




}


