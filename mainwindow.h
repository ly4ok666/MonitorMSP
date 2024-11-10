#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "initbasicstyle.h"
#include <qcustomplot.h>
#include <stdint.h>
#include "tric.h"
#include "tsap.h"
#include "tvsk.h"
#include "Targets.h"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

//#include "Targets.h"
//#include "SPI.h"

#include "chrono"
#include "unistd.h"

#include <tcpsockethandler.h>
#include "mytcpsocket.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum onetimecommands
{
    noCom,
    PRM,
    PRD,
    VSK,
    CONNECT,
    Other
}onetimecommands;


class MainWindow : public QMainWindow
{
    Q_OBJECT
/*    bool VSK_Started; //???*/

/*    void unPack(QByteArray input); //??*/
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_statusCommands(unsigned char);
    unsigned char get_statusCommands();


private:
    Tric *ric;
    Tsap *sap;
    tvsk *vsk;
    bool WorkingState = false;
    StructFormularFrom306Mod *FormularFrom306Mod;
    QTimer timer;
    unsigned char statusCommands;
    MyTcpsocket *MyTcpSocket;
    QThread MyTcpThread;


protected:
        Ui::MainWindow *ui;
private slots:
    void on_PBsap_clicked(); //кнопка для проведения вск
    void on_PBprm_prd_clicked(); //кнопка для смены режима
    void on_PBwifi_clicked(); //кнопка для вайфая
    void discardSocket(); // обработка дисконекта
    void connectSocket(); //обработка коннекта
    void setWorkingModeMSP(unsigned char);
    void setVSK(unsigned char);

public slots:
        void on_actionExit_triggered(); //слот для обработки сигнала от гуя (верхнй бар)

        //данный слот создан для получения данных по сигналу: void signals_statusCom(uint8_t); в майн виндоус!!
        void slot_statusCom(unsigned char);

        void slot_choice_WriteFinished(unsigned char, unsigned char);

        //слот распаковщик, пока на первое время просто распакую во что-то
        void slot_unPacked(const QByteArray);
signals:
        //данный сигнал нужен для смены режима (ПРМ\ПРД) во вкладке САП
        //для него создан в sap слот: void Slot_set_workingmode_from_mw(bool);
        void signals_for_sap_workingmode(unsigned char, unsigned short, unsigned short);
        void signals_WriteFinished(unsigned char, unsigned char);
        //данный сигнал нужен для записи в мсп (в данный момент записывать будем разовые комманды)
        //по этому сайзоф никакой не нужен, упращённая запись
        //для него создан в tcpsoket слот: void slot_write_to_msp(uint16_t, uint16_t);
        void signal_write_to_msp(unsigned char);

        //Данный сигнал нужен для повторного коннекта с сервером
        //для него создан в tcpsoket слот: void slot_check_connect_gui_to_msp();
        void signal_check_connect_gui_to_msp();

        void signal_writeTempData(_Periodical_formular, QVector<_SignalParam_formular>);
        void signal_writeTempData_VSK(_VSKRes_formular);
        void signal_addingSignalsToPlot(QVector<_SignalParam_formular>);


        //void ReadAll();
        void ReadFinished();
        void SendVSKCommand(uint8_t);
        void Setprd_prm(uint8_t);
};
#endif // MAINWINDOW_H
