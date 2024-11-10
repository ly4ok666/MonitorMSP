#include "tcpsockethandler.h"


//TestTar::TestTar()
//{
//    //тут нужно будет создать ряд объектов
//    Targets = new _SignalParam_formular[TARGET_NUM];
//    VSKRes = new _VSKRes_formular;
//    SAPStatus = new _Periodical_formular;
//    qDebug() << "создался объект Targets, VSKRes, SAPStatus";

//};

//TestTar::~TestTar()
//{
//    delete [] Targets;
//    delete VSKRes;
//    delete SAPStatus;
//    qDebug() << "удалился объект Targets, VSKRes, SAPStatus";
//};

TcpSocketHandler::TcpSocketHandler()
{
    socket = new QTcpSocket; //создадим экземпляр работы с сокетом
//    Formulars = new TestTar;
    qDebug() << "создался объект ТестТаргетс";


}
TcpSocketHandler::~TcpSocketHandler()
{
//    delete Formulars;

    qDebug() << "удалился объект ТестТаргетс";
}

//TestTar TcpSocketHandler::getFormulars()
//{
//    return *Formulars;
//}

unsigned char TcpSocketHandler::connectToHost() //тут мы коннектимся к хосту, а значит и сокет нам создавать туть
{
    unsigned char host_stat = 0;

#ifdef LOCALHOST
    socket->connectToHost(QHostAddress::LocalHost,8080);
#else
    socket->connectToHost(QHostAddress("192.168.0.5"), 80); //тут подключаемся к порту, делаем это только в одном месте
#endif
    while (!socket->waitForConnected(3000)) {
        static uint32_t attempt = 1;

        if (attempt >= 10)
        {
            notConnectToHost();
            emit signals_disconnect_gui_to_msp();
            qDebug() << "Не смогли";
            attempt = 0;
            return host_stat;
        }
#ifdef LOCALHOST
        socket->connectToHost(QHostAddress::LocalHost,8080);
#else
        socket->connectToHost(QHostAddress("192.168.0.5"), 80); //тут подключаемся к порту, делаем это только в одном месте
#endif
        attempt++;
    }
    emit signals_connect_gui_to_msp();
    qDebug() << "Приконектились";
    return host_stat = 1;
}

void TcpSocketHandler::notConnectToHost()
{
    if(socket->isOpen()) // если мы схлопываем программу, чтоб память не утекла, надо всё удалить
        socket->close();
}

void TcpSocketHandler::set_statusCom(unsigned char status)
{
    statusCom = status;
}

unsigned char TcpSocketHandler::get_statusCom()
{
    return statusCom;
}

QTcpSocket* TcpSocketHandler::getSoced()
{
    return socket;
}

void TcpSocketHandler::NullPtrSoced()
{
    socket = nullptr;
}

void TcpSocketHandler::run()
{
    emit finishedWorkOrDisconnect();
}

void TcpSocketHandler::slot_write_to_msp(unsigned char commands)
{
    //в начале нужна проверка что соединение не разорвано
    qDebug() << "Commands: " << commands;
    _SPI_Packet *SPI_Packet =  new _SPI_Packet;

    //_SPI_Packet SPI_Packet;
    SPI_Packet->rw = W;
    SPI_Packet->address = 0x00; //0x00
    SPI_Packet->data.data16 = 0x03;//0x01

    socket->waitForReadyRead(250); // FIXME Если убрать - ничего не приходит на STM
    QByteArray out((char*)SPI_Packet, sizeof(_SPI_Packet));
        qDebug() << "Выходим тут или не доходим и весим где-то? " << out;
    socket->write(out);
    socket->waitForReadyRead(1); // FIXME Если убрать - ничего не приходит на STM

    delete SPI_Packet;

    emit signals_WriteFinished(commands);

    //а тут нужно выкинуть сигнал со статусом что запись прошла успешно и можно менять положения кнопок

}

void TcpSocketHandler::slot_read_to_msp()
{

}

void TcpSocketHandler::slot_check_connect_gui_to_msp() //слот обработчик для повторного коннекта к серверу
{
    if(TcpSocketHandler::connectToHost())
    {
        //emit signals_connect_gui_to_msp();
    }
    else
    {
        //emit signals_disconnect_gui_to_msp();
    }
}







//эту функцию переделать или вообще удалить нафик
void TcpSocketHandler::WriteRead() //это более гибкий типа способ записи, ручками из под гуя, но наверное лишняя опция, только для будующих целей
{
    _SPI_Packet SPI_Packet; //создаём пакет, он стандартный для всего чтение и запись
    SPI_Packet.rw = W; //R
    SPI_Packet.address = 0x00;
    SPI_Packet.data.data16 = 0x00;

    //не ясная мысль, что с этим делать
    if (SPI_Packet.rw == 0 && SPI_Packet.address == 0) {
        //TcpSocketHandler::ReadAll();
        // ui->DebugLabel->setText("All read data is presented at \"Read All\"");
        return;
    }

    //Стандартное обращение к сокету, возможно есть смысл вынести в отдельный функциионал..
    QTcpSocket socket;
    socket.connectToHost(QHostAddress("192.168.0.5"), 80);

    while (!socket.waitForConnected(1000)) {
        static uint32_t attempt = 1;
        if (attempt >= 10)
        {
            attempt = 0;
            // ui->Status_Label->setText("Can not connect to ESP (TimeOut). Stopped");
            // ui->actionReadAll->setChecked(false);
            return;
        }
        socket.connectToHost(QHostAddress("192.168.0.5"), 80);
    }

    QByteArray out((char*)&SPI_Packet, sizeof(_SPI_Packet));
    socket.write(out);
    socket.waitForReadyRead(1); // FIXME Если убрать - ничего не приходит на STM

    //для чтения пакетов на линии
    if (SPI_Packet.rw == R)
    {
        QByteArray in;
        while(in.length() < 2)
            if (socket.waitForReadyRead(1000)) //если ответ от соединения шёл меньше минуты, тогда читаем всё
                in.append(socket.readAll());
            else {
                //ui->DebugLabel->setText("No answer from ESP (TimeOut)"); //DEBUG
                socket.close();
                socket.deleteLater();
                return;
            }
        //ui->DebugLabel->setText("Data successfully recieved!"); //DEBUG

        //memcpy((uint16_t*) &DescrWordStruct + SPI_Packet.address,  in.constData(), 2);

        //QString answer = QString::number(*((quint16*) in.constData()), 16).toUpper();
        //ui->dataLineEdit->setText(answer);
    }
    else //иначе выведем сообщение что данные успешно отправлены
    {
        // ui->DebugLabel->setText("Data successfully transmitted!"); //DEBUG
        qDebug() << "Data successfully transmitted!" ;
    }

    socket.close(); //заканчиваем сессию
    socket.deleteLater(); // удаляем все что начитали или назаписывали
}



void TcpSocketHandler::SendVSKCommand(uint8_t command)
{

    static quint64 counter = 0;
    counter++;

    _SPI_Packet *SPI_Packet =  new _SPI_Packet;
    SPI_Packet->rw = W;
    SPI_Packet->address = 0x00;
    SPI_Packet->data.data16 = 0x08;
    qDebug() << "Commands: " << command;
    QTcpSocket *socket = new QTcpSocket;
    socket->connectToHost(QHostAddress("192.168.0.5"), 80); // !!! ERROR !!!

    while (!socket->waitForConnected(3000)) {
        static uint32_t attempt = 1;

        if (attempt >= 10)
        {
            attempt = 0;
            return;
        }
        socket->connectToHost(QHostAddress("192.168.0.5"), 80);
        attempt++;
    }

    socket->waitForReadyRead(250); // FIXME Если убрать - ничего не приходит на STM

    QByteArray out((char*)&SPI_Packet, sizeof(_SPI_Packet));
    socket->write(out);
    socket->waitForReadyRead(1); // FIXME Если убрать - ничего не приходит на STM
    socket->close();
    socket->deleteLater();
    delete SPI_Packet;
    delete socket;
    qDebug() << "Выходим тут или не доходим и весим где-то?";
    return;
}
