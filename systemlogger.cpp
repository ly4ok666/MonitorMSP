#include "systemlogger.h"
#include <iostream>

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QObject>

QFile* systemLogger::systemLogFile = Q_NULLPTR;
bool systemLogger::isInit = false;
QHash<QtMsgType, QString> systemLogger::contextNames =
{
    {QtMsgType::QtDebugMsg,      "Debug   "},
    {QtMsgType::QtInfoMsg,       "Info    "},
    {QtMsgType::QtWarningMsg,    "Warning "},
    {QtMsgType::QtCriticalMsg,   "Critical"},
    {QtMsgType::QtFatalMsg,      "Fatal   "}
};

void systemLogger::init()
{
    if(isInit) return;
    //если не был инициализирован, тогда создаём файл

    systemLogFile = new QFile;
    systemLogFile->setFileName("./MyLog.log"); //Указываем где будет храниться файл и его название с расширением, в целом это можно будет сделать погибче
    systemLogFile->open(QIODevice::Append | QIODevice::Text); //Указвыаем в каком формате будем его открывать (добавление в конец строки и в текстовом формате

    //Перенаправляем логи на вывод сообщения
    qInstallMessageHandler(systemLogger::messageOutput);

    //избыточная очистка файла, когда буду делать гибче, не понадобится
    systemLogFile->resize(0);

    systemLogger::isInit = true; //теперь логер инициализирован
}

void systemLogger::clean()
{
    if(systemLogFile != Q_NULLPTR) //если файл не пустой тогда мы его почистим, зачем-то, лог от души называется
    {
        systemLogFile->close();
        delete systemLogFile;
    }
}

void systemLogger::messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString log = QObject::tr("%1| %2 | %3 | %4| %5 | %6\n").
                  arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).    //..время на момент записи лога
                  arg(systemLogger::contextNames.value(type)).  //..........................тип самого лога
                  arg(context.line).    //..................................................строка на которой стоит лог
                  arg(QString(context.file).    //..........................................имя файла без пути к файлу
                    section('\\', -1)).
                  arg(QString(context.function).    //......................................функция из которой вызван лог
                    section('(', -2, -2).
                    section(' ', -1).
                    section(':', -1)).
                  arg(msg);     //..........................................................текст
    if(type == 0)
        std::cout << msg.toStdString() << std::endl;
    systemLogFile->write(log.toLocal8Bit());
    systemLogFile->flush();
}
