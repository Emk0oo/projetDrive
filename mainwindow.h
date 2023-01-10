#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonConnexion_clicked();

    void on_pushButtonDeconnexion_clicked();

    void on_envoyer_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serie;


};
#endif // MAINWINDOW_H
