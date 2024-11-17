#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QImage>
#include <QTabWidget>
#include "chrono"
#include "unistd.h"
#include "systemlogger.h"

//#define WINDOWS
#ifdef WINDOWS
#include "crtdbg.h"
#include "windows.h"
#endif

#include "signal.h"

#define _DEBUG
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#endif

// _SPI_Packet SPI_Packet;
// uint32_t *u32 = (uint32_t*) &SPI_Packet; //??

unsigned short countTargetsPPS = 0;
unsigned short countTargetsZPS = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    systemLogger::init();
    globalTimer = new QTimer(this);
    globalTimer->setInterval(100); // Задаем интервал таймера
    connect(globalTimer, &QTimer::timeout, this, &MainWindow::GlobalTimeExpired);
    globalTimer->start();

//SocketHandler->getFormulars().getSAPStatus_Formular().W5.Visota; //удалить , а вообще перенести куда надо
/*****************************************************
* блокировка кнопок прм\прд и кнопки вск
* по хорошему придумать более изящьное решение
******************************************************/
    ui->PBprm_prd->setEnabled(0);
    ui->PBsap->setEnabled(0);
/*****************************************************
* определение новых вкладок в шаблон
* нужно для более модульной и
* гибкой работы с отдельными вклаками
******************************************************/
    ric = new Tric();
    sap = new Tsap();
    vsk = new tvsk();
    ui->tabWidget->insertTab(ui->tabWidget->count() + 1,sap, QString("SAP").arg(ui->tabWidget->count() + 1));
    ui->tabWidget->insertTab(ui->tabWidget->count() + 1,ric, QString("RIC").arg(ui->tabWidget->count() + 1));
    ui->tabWidget->insertTab(ui->tabWidget->count() + 1,vsk, QString("VSK").arg(ui->tabWidget->count() + 1));
/*****************************************************
* создаём объек класса обработчика TCP-шных пакетов
* закидываем в отдельный дочерний поток MyTcpThread
******************************************************/
    MyTcpSocket = new MyTcpsocket;
    MyTcpSocket->moveToThread(&MyTcpThread);
/*****************************************************
* создали объект структур который потом будем раскидывать во все дыры
******************************************************/
    FormularFrom306Mod = new StructFormularFrom306Mod;
/*****************************************************
* обработка сигнала от потока
* сигнал для старта отдельного потока
******************************************************/
    connect(&MyTcpThread, &QThread::started, MyTcpSocket, &MyTcpsocket::ConnectToMSP);
/*****************************************************
* фоновая обработка сигналов от сокета
* сигнал о том что нет коннекта и label wi-fi нужно сделать красным
* сигнал о том что есть коннект и label wi-fi нужно сделать зелёным
******************************************************/
    connect(MyTcpSocket, &MyTcpsocket::SignalsDisconnectedFromTheMSP, this, &MainWindow::discardSocket);
    connect(MyTcpSocket, &MyTcpsocket::SignalsConnectedToMSP, this, &MainWindow::connectSocket); //Обработка коннекта по сигналу от клиента атомат
/*****************************************************
* запись в сокет и передача по wi-fi
* сигнал на запись чего-то сравнительно не большого unsigned char
******************************************************/
    connect(this, &MainWindow::signal_write_to_msp, MyTcpSocket, &MyTcpsocket::slot_write_to_msp); //Запись в МСП
/*****************************************************
* обработки кнопок разовых комманд
* сигнал после того как мы записали смену режима в signal_write_to_msp()
* сигнал разукрашивание на плоте во вкладке САП
* будующая комманда ВСК
******************************************************/
    //connect(MyTcpSocket, &MyTcpsocket::signals_WriteFinished, this, &MainWindow::slot_choice_WriteFinished); //обработка нажатия на кнопку смена режма
    connect(this, &MainWindow::signals_WriteFinished, this, &MainWindow::slot_choice_WriteFinished); //обработка нажатия на кнопку смена режма
    connect(this, &MainWindow::signals_for_sap_workingmode, sap, &Tsap::Slot_set_workingmode_from_mw); //rabochi function
    connect(MyTcpSocket, &MyTcpsocket::signals_UnPacked, this, &MainWindow::slot_unPacked); //обработка нажатия на кнопку смена режма
/*****************************************************
* сигналы которые не используются по каким-то причинам
* сигнал о смене статуса, идейно хотелось по нему что-то обновлять, но потоки...
* сигнал во вкладку риц о вск, хз зачем уже пора удалять
******************************************************/
    //connect(this, &MainWindow::SendVSKCommand, ric, &Tric::Setprd_prm); //skoree vsego peredelat
    connect(this, &MainWindow::signal_writeTempData, ric, &Tric::slot_writeTempData); //skoree vsego peredelat
    connect(this, &MainWindow::signal_writeTempData_VSK, vsk, &tvsk::slot_writeTempData_VSK); //skoree vsego peredelat


    connect(this, &MainWindow::signal_addingSignalsToPlot, sap, &Tsap::slot_addingSignalsToPlot);

}

StructFormularFrom306Mod::StructFormularFrom306Mod()
{

}
StructFormularFrom306Mod::~StructFormularFrom306Mod()
{

}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::slot_statusCom(uint8_t status)
{
    qDebug() << "status: " << status;
    set_statusCommands(status);
}

MainWindow::~MainWindow()
{

    MyTcpThread.quit();
    MyTcpThread.wait();
    delete MyTcpSocket;
    delete ui;
    delete globalTimer;
}

void MainWindow::set_statusCommands(unsigned char status)
{
    statusCommands = status;
}

unsigned char MainWindow::get_statusCommands()
{
    return statusCommands;
}



void MainWindow::on_PBsap_clicked()
{
    emit signal_write_to_msp(VSK);
    ui->PBsap->setText("BIT");
    ui->PBsap->setStyleSheet("QPushButton#PBsap { color: red;	background: transparent; }");
        //сделать по лучше блокирование кнопок
    ui->PBsap->setEnabled(0);
    ui->PBprm_prd->setEnabled(0);
    return;
}

void MainWindow::on_PBprm_prd_clicked()
{
        //сделать по лучше блокирование кнопок
    ui->PBprm_prd->setEnabled(0);
    ui->PBsap->setEnabled(0);

    if(WorkingState)
    {
        emit signal_write_to_msp(PRM);
        ui->PBprm_prd->setText("ПРД");
        ui->PBprm_prd->setStyleSheet("QPushButton#PBprm_prd { color: orange;	background: transparent; }");
    }
    else
    {
        emit signal_write_to_msp(PRD);
        ui->PBprm_prd->setText("ПРМ");
        ui->PBprm_prd->setStyleSheet("QPushButton#PBprm_prd { color: orange;	background: transparent; }");
    }
}

void MainWindow::setWorkingModeMSP(unsigned char value)
{
    ui->PBprm_prd->setEnabled(1);
        ui->PBsap->setEnabled(1);
    if(value == PRM)
    {
        ui->PBprm_prd->setText("ПРМ");
        ui->PBprm_prd->setStyleSheet("QPushButton#PBprm_prd { Color: rgb(181, 230, 29);	background: transparent; }");
        WorkingState = false;
        qDebug() << "ПРМ";
    }
    else if (value == PRD)
    {
        ui->PBprm_prd->setText("ПРД");
        ui->PBprm_prd->setStyleSheet("QPushButton#PBprm_prd { Color: rgb(181, 230, 29);	background: transparent; }");
        WorkingState = true;
        qDebug() << "ПРД";
    }
    emit signals_for_sap_workingmode(value, countTargetsPPS, countTargetsZPS);
}

void MainWindow::setVSK(unsigned char value)
{
    if(!value)
    {
        ui->PBsap->setText("VSK");
        ui->PBsap->setStyleSheet("QPushButton#PBsap { color: red;	background: transparent; }");
        ui->PBsap->setEnabled(1);
        ui->PBprm_prd->setEnabled(1);
    }
    else
    {
        ui->PBsap->setText("VSK");
        ui->PBsap->setStyleSheet("QPushButton#PBsap { Color: rgb(181, 230, 29);	background: transparent; }");
        ui->PBsap->setEnabled(1);
        ui->PBprm_prd->setEnabled(1);
    }
}

void MainWindow::GlobalTimeExpired()
{
    unsigned DiscretteTime = 10000;
    if(TimeisExpired(localTimers.GiveMeTheDataNow, DiscretteTime))
    {
        emit signal_write_to_msp(CONNECT);
    }

}

void MainWindow::slot_choice_WriteFinished(unsigned char commands, unsigned char value)
{
    switch (commands) {
    case PRM:
        MainWindow::setWorkingModeMSP(PRM);
        break;
    case PRD:
        MainWindow::setWorkingModeMSP(PRD);
        break;
    case VSK:
        MainWindow::setVSK(value);
        break;
    case CONNECT:

        break;
    default:
        break;
    }
}
inline void StructFormularFrom306Mod::setVSK_Formular(QByteArray input, unsigned long long start)
{
    memcpy(&VSKRes, input.data() + start, sizeof(_VSKRes_formular));
}
_VSKRes_formular StructFormularFrom306Mod::getVSK_Formular()
{
    return VSKRes;
}
inline void StructFormularFrom306Mod::setTargets(QByteArray input, unsigned long long start)
{
    Targets.clear();
    Targets.resize(0);
    countTargetsPPS = 0;
    countTargetsZPS = 0;

    _SignalParam_formular *SignalParam = new _SignalParam_formular[TARGET_NUM]; //выделим динамически много на время
    for (uint8_t i = 0; i < TARGET_NUM; ++i) //скорее всего на время копировавания всего барахла, нужно будет сделать лок, это уже в процессе нужно посмотреть
    {
        memcpy(&SignalParam[i], input.data() + start + sizeof(_SignalParam_formular) * i, sizeof(_SignalParam_formular));
        if(SignalParam[i].W3.Carrier)
        {
            Targets.push_back(SignalParam[i]);
            if(!SignalParam[i].W2.semisphere)
                countTargetsPPS++;
            else
                countTargetsZPS++;
        }
    }
    delete [] SignalParam; //после того как заполнили вектор ТОЛЬКО НЕ НУЛЕВЫМИ сигналами, освобождаем память

}

inline QVector<_SignalParam_formular> StructFormularFrom306Mod::getTargets() const
{
    return Targets;
}

inline void StructFormularFrom306Mod::setSizeVector(size_t newSizeVector)
{
    sizeVector = newSizeVector;
}

inline size_t StructFormularFrom306Mod::getSizeVector() const
{
    return sizeVector;
}
inline void StructFormularFrom306Mod::setSAPStatus_Formular(QByteArray in, unsigned long long start)
{
    memcpy(&SAPStatus, in.data() + start, sizeof(_Periodical_formular));
}


inline _Periodical_formular StructFormularFrom306Mod::getSAPStatus_Formular()
{
    return SAPStatus;
}
void MainWindow::slot_unPacked(const QByteArray in)
{
//    _Periodical_formular Periodical_formular;
//    memcpy(&Periodical_formular, in.data() + 1, sizeof(_Periodical_formular));
//    qDebug() << "1: " << Periodical_formular.W5.Visota;
//    qDebug() << "2: " << Periodical_formular.W6.AVT_quit;
//    qDebug() << "3: " << Periodical_formular.W6.CU_quit;
//    qDebug() << "4: " << Periodical_formular.W6.BCVM_Connection;
//    qDebug() << "5: " << Periodical_formular.W6.StationModes;
//    qDebug() << "6: " << Periodical_formular.W6.FHS_Enable;
//    qDebug() << "7: " << Periodical_formular.W6.RHS_Enable;
//    qDebug() << "8: " << Periodical_formular.W6.IzluchPPS;
//    qDebug() << "9: " << Periodical_formular.W6.IzluchZPS;
//    qDebug() << "10: " << Periodical_formular.W6.VSKStatus;
//    qDebug() << "11: " << Periodical_formular.W6.VzaimnZash;
//    qDebug() << "12: " << Periodical_formular.W7.m302_0_obsl;
//    qDebug() << "13: " << Periodical_formular.W7.m302_1_obsl;
//    qDebug() << "14: " << Periodical_formular.W8.m302_0_neobsl;
//    qDebug() << "15: " << Periodical_formular.W8.m302_1_neobsl;


    FormularFrom306Mod->setSAPStatus_Formular(in, startBit); //1
    FormularFrom306Mod->setTargets(in, startBit + sizeof(_Periodical_formular)); //
    FormularFrom306Mod->setVSK_Formular(in, startBit + sizeof(_Periodical_formular) + sizeof(_SignalParam_formular) * TARGET_NUM);
    if(FormularFrom306Mod->getSAPStatus_Formular().W6.StationModes == 2)
    {
        emit signals_WriteFinished(PRM, 0);
        qDebug() << "5: " << FormularFrom306Mod->getSAPStatus_Formular().W6.StationModes;

    }
    else if (FormularFrom306Mod->getSAPStatus_Formular().W6.StationModes == 3)
    {
        emit signals_WriteFinished(PRD, 0);
        qDebug() << "5: " << FormularFrom306Mod->getSAPStatus_Formular().W6.StationModes;
    }
    if (!FormularFrom306Mod->getVSK_Formular().W2.SAP)
    {
        emit signals_WriteFinished(VSK, 0);
    }
    else if(FormularFrom306Mod->getVSK_Formular().W2.SAP)
    {
        emit signals_WriteFinished(VSK, 1);
    }

    emit signal_addingSignalsToPlot(FormularFrom306Mod->getTargets());
    emit signal_writeTempData(FormularFrom306Mod->getSAPStatus_Formular(), FormularFrom306Mod->getTargets());
    emit signal_writeTempData_VSK(FormularFrom306Mod->getVSK_Formular());
 //тут нам нужен сигналы раскидать в сап и в риц пакетовые, если в сап , то передаём параметры сигнала и состояний станции, то в риц нужно скинуть вообще всё
    QTime saveTime;
    localTimers.GiveMeTheDataNow = saveTime.currentTime(); //сохраняю время последних данных
}

void MainWindow::on_PBwifi_clicked()
{
    MyTcpThread.start(); //тут нужен флаг на всякий случай
    //нужен таймер, если в течении 5 секунд небыло обновления информации, то отправить команду 4
    //команда 4 - звучит как: дай данные которые есть у тебя, чиним недостоющие части сервера
}

void MainWindow::discardSocket()
{
    MyTcpThread.quit();
    MyTcpThread.wait();

    ui->PBprm_prd->setEnabled(0);
    ui->PBsap->setEnabled(0);
    ui->PBwifi->setStyleSheet("QPushButton#PBwifi { color: red;	background: transparent; }");
    qDebug() << "Disconnect!";
}

void MainWindow::connectSocket()
{
    ui->PBprm_prd->setEnabled(1);
    ui->PBsap->setEnabled(1);
    ui->PBwifi->setStyleSheet("QPushButton#PBwifi {Color: rgb(181, 230, 29);	background: transparent; }");
    emit signal_write_to_msp(CONNECT);
    qDebug() << "Connect!";
}

unsigned MainWindow::TimeisExpired(QTime EventTime, unsigned DiscretteTime)
{
    QTime CurrentTime;
    if (CurrentTime.currentTime() < (EventTime.addMSecs(DiscretteTime)))
        return 0;
    return 1;

}
