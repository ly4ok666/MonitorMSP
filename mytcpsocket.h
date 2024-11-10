#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>
#include "SPI.h"


//#define LOCALHOST1

class MyTcpsocket: public QObject
{
    Q_OBJECT
public:
    explicit MyTcpsocket(QObject *parent = 0); //Конструктор
    ~MyTcpsocket();
signals:
    void SignalsDisconnectedFromTheMSP();
    void SignalsConnectedToMSP();
    //данный сигнал нужен для того, что бы сигнализировать что мы записали что-то в порт и отправлять какую комманду записали
    //для него создан в mainwindow слот: void slot_choiсe_WriteFinished(unsigned char);
    //void signals_WriteFinished(unsigned char);
    //этим сигналом я передаю все структурки чтоб раскатать их по классу в мейне
    void signals_UnPacked(QByteArray);

public slots:
    void ConnectToMSP();
    void discardSocket(); // обработка дисконекта
    void connectSocket(); //обработка коннекта
    void slot_write_to_msp(unsigned char);
    void slot_read_to_msp();
private:
    QTcpSocket *socket;
};

#endif // MYTCPSOCKET_H
