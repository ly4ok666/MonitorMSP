#include "mytcpsocket.h"
#include "Targets.h"

MyTcpsocket::MyTcpsocket(QObject *parent)
    : QObject(parent)
{
}
MyTcpsocket::~MyTcpsocket()
{
    if(socket->isOpen()) // если мы схлопываем программу, чтоб память не утекла, надо всё удалить
        socket->close();
    qDebug() << "удалился объект ТестТаргетс";
}

void MyTcpsocket::ConnectToMSP()
{
    socket = new QTcpSocket(this); //создадим экземпляр работы с сокетом
    //теперь подключим сигналы от сокета
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpsocket::discardSocket); //Обработка диссконекта по сигналу от клиента автомат
    connect(socket, &QTcpSocket::connected, this, &MyTcpsocket::connectSocket); //Обработка коннекта по сигналу от клиента атомат
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpsocket::slot_read_to_msp); //чтение из МСП

    qDebug() << "Connecting...";
#ifdef LOCALHOST1
    socket->connectToHost(QHostAddress::LocalHost,8080); //коннектимся к серверу
#else
    socket->connectToHost(QHostAddress("192.168.0.5"), 80); //тут подключаемся к порту, делаем это только в одном месте
#endif
    if(!socket->waitForConnected(3000))
    {
        qDebug() << "Not Connect with MSP!!";
        emit SignalsDisconnectedFromTheMSP();
        //как вариант попробовать сделать ещё коннект, но может в этом и нет смысла, но мы в отдельном потоке ЖИ
    }
}

void MyTcpsocket::connectSocket()
{
    qDebug() << "Connect to MSP!!";
    emit SignalsConnectedToMSP();
}
void MyTcpsocket::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;
    qDebug() << "Disconnect from MSP!!";
    emit SignalsDisconnectedFromTheMSP();
}

void MyTcpsocket::slot_write_to_msp(unsigned char commands)
{
    qDebug() << "Commands: " << commands;
    _SPI_Packet SPI_Packet;
    SPI_Packet.rw = W;
    SPI_Packet.address = 0x00; //0x00 (адрес плис + это значение) получим сдвиги
    SPI_Packet.data.data16 = commands;//0x01

    QByteArray out((char*)&SPI_Packet, sizeof(_SPI_Packet));
    qDebug() << "предаваемые данные: " << out;
    socket->write(out);
    socket->waitForBytesWritten();
    //emit signals_WriteFinished(commands); //не восстанавливаю управлпение станцией, пока не дождусь ответ

}

void MyTcpsocket::slot_read_to_msp()
{

    QByteArray in;

    in.resize(maxsizepack);
    in.clear();
    while (in.length() < (int)maxsizepack)
    {
        if (socket->waitForReadyRead(1000))
        {
            //in.append(socket->readAll());
            in.append(socket->read(maxsizepack));
            qDebug() << "Read Data : " << in;
        }
            //in.append(socket->readAll());
        else {
            return;
        }
    }


        emit signals_UnPacked(in); //распаковка данных принятых с мсп

    // if(in[0] == 0x1)
    //     qDebug() << "Read Data : " << in[0];
}
