# projetDrive
Dev drive afficheur alpha &amp; balance
(Qt Creator 4.11.0, Basé sur Qt 5.12.8 (GCC 9.3.0, 64 bit))


Du 10 janvier 2023

Code fonctionnel pour envoyer une trame sur afficheur alpha 215R (& 215C)



A ajouté en en-tête dans le .pro : 

QT       += core gui
QT += network
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
