#ifndef TCPSOCKETHANDLER_H
#define TCPSOCKETHANDLER_H
#include "Targets.h" //переезжаем в основной цикл, туда сигналами накидаем, нужно будет для того что бы сохранить последние данные, хотя может это и ненужн будет , посмотрим
#include <QObject>
//#include "TCP.h"
#include "SPI.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>
#include <stdint.h>

#define LOCALHOST

class TcpSocketHandler: public QObject
{
    Q_OBJECT //нужен для использования сигнал/слот

public:
    TcpSocketHandler();
    ~TcpSocketHandler();
    void unPack(QByteArray); //в этой вункции идёт запись данных полученных при чтении тут нужно подумать как без циклов скопировать данные сразу все по структурам
    //TestTar getFormulars(); //это доступ до класса таргетс, с помощью этого доступа сможем сигналами отправлять структурки заполненные
    unsigned char connectToHost();//это функция с помощью которой мы осуществляем коннект к серверу, возможно есть готовый вариант, но не будем
    void notConnectToHost();
    void set_statusCom(unsigned char);
    unsigned char get_statusCom();
    QTcpSocket* getSoced(); //функция для получения экземпляра созданного сокета
    void NullPtrSoced(); //эту функцию  лучше не использовать
public slots:
    //собственно наш стартер
    void run();
    //данный слот создан для получения данных по сигналу: void signal_write_to_msp(uint16_t, uint16_t); в майн виндоус!!
    void slot_write_to_msp(unsigned char);
    void slot_read_to_msp();

    //данный слот создан для получения данных по сигналу: void signal_check_connect_gui_to_msp(); в майн виндоус!!
    void slot_check_connect_gui_to_msp();

//это всё нужно будет переделать нафик
   void WriteRead(); //эта функция тесно связана с ридолл
//    void WriteToZero(); //на счёт этой подумать, на сколько она нужна будет

    void SendVSKCommand(uint8_t); //тут разложить всё же на разные функции вск и переключение режима прм\прд, чтоб не запутаться

signals:
    //испускаемый сигнал, что мы закончили вообще работу и пора выключать бадягу
    void finishedWorkOrDisconnect();

    void ReadFinished();

    //данный сигнал нужен для того, что бы сигнализировать что мы записали что-то в порт и отправлять какую комманду записали
    //для него создан в mainwindow слот: void slot_choiсe_WriteFinished(unsigned char);
    void signals_WriteFinished(unsigned char);

    //данный сигнал нужен для оповещения прошла комманда или нет
    //для него создан в mainwindow слот: void slot_statusCom(uint8_t);
    void signals_statusCom(unsigned char);

    //этот сигнал нужен для смены цвета wi-fi на зелёный при старте
    //для него создан в mainwindow слот: void connectSocket();
    void signals_connect_gui_to_msp();

    //этот сигнал нужен для смены цвета wi-fi на красный при старте
    //для него создан в mainwindow слот: void discardSocket();
    void signals_disconnect_gui_to_msp();

private:
    QTcpSocket *socket;
    //TestTar *Formulars;
    uint8_t statusCom;

};

#endif // TCPSOCKETHANDLER_H
