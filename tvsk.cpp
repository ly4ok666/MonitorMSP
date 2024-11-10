#include "tvsk.h"
#include "ui_tvsk.h"
#include "QBrush"

tvsk::tvsk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tvsk)
{
    ui->setupUi(this);
    ui->Tvsk->setColumnCount(2);
}

tvsk::~tvsk()
{
    delete ui;
}

void tvsk::addRootVSKRes_formular(QString name,QString description, _VSKRes_formular VSKRes_formular, bool addToParent)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->Tvsk);
    itm->setText(0, name);
    itm->setText(1, description);
    if(description == "OK")
    {
        QBrush b (QColor(181, 230, 29)); //можно было бы делигат добавить и как в кайф менять цвет но, позже
        itm->setForeground(0,b);
        itm->setForeground(1,b);
    }
    else
    {
        QBrush b (Qt::red); //можно было бы делигат добавить и как в кайф менять цвет но, позже
        itm->setForeground(0,b);
        itm->setForeground(1,b);
    }
    //ui->Ttargets_sap->addTopLevelItem(parent);
    if(!addToParent) return;
    else
    {
        if(name == "Master[1.3]")
        {
            addChildVSKRes_formular(itm, "m301N2", QString::number(VSKRes_formular.W3.m301N2), false);
            addChildVSKRes_formular(itm, "m301N1", QString::number(VSKRes_formular.W3.m301N1), false);
            addChildVSKRes_formular(itm, "m302N2", QString::number(VSKRes_formular.W3.m302N2), false);
            addChildVSKRes_formular(itm, "m302N1", QString::number(VSKRes_formular.W3.m302N1), false);
            addChildVSKRes_formular(itm, "m303N2", QString::number(VSKRes_formular.W3.m303N2), false);
            addChildVSKRes_formular(itm, "m303N1", QString::number(VSKRes_formular.W3.m303N1), false);
            addChildVSKRes_formular(itm, "m305", QString::number(VSKRes_formular.W3.m305), false);
            addChildVSKRes_formular(itm, "m306", QString::number(VSKRes_formular.W3.m306), false);
            addChildVSKRes_formular(itm, "m307", QString::number(VSKRes_formular.W3.m307), false);
        }
        else if(name == "Slave[1.3]")
        {
            addChildVSKRes_formular(itm, "m301N4", QString::number(VSKRes_formular.W5.m301N4), false);
            addChildVSKRes_formular(itm, "m301N3", QString::number(VSKRes_formular.W5.m301N3), false);
            addChildVSKRes_formular(itm, "m302N4", QString::number(VSKRes_formular.W5.m302N4), false);
            addChildVSKRes_formular(itm, "m302N3", QString::number(VSKRes_formular.W5.m302N3), false);
            addChildVSKRes_formular(itm, "m303N4", QString::number(VSKRes_formular.W5.m303N4), false);
            addChildVSKRes_formular(itm, "m303N3", QString::number(VSKRes_formular.W5.m303N3), false);
            addChildVSKRes_formular(itm, "m305_1", QString::number(VSKRes_formular.W5.m305_1), false);
            addChildVSKRes_formular(itm, "m306_1", QString::number(VSKRes_formular.W5.m306_1), false);
            addChildVSKRes_formular(itm, "m307_1", QString::number(VSKRes_formular.W5.m307_1), false);
        }
        else  if(name == "Unit[1.4]")
        {
            addChildVSKRes_formular(itm, "m402", QString::number(VSKRes_formular.W4.m402), false);
            addChildVSKRes_formular(itm, "m403N2", QString::number(VSKRes_formular.W4.m403N2), false);
            addChildVSKRes_formular(itm, "m403N1", QString::number(VSKRes_formular.W4.m403N1), false);
            addChildVSKRes_formular(itm, "m405", QString::number(VSKRes_formular.W4.m405), false);
            addChildVSKRes_formular(itm, "m406", QString::number(VSKRes_formular.W4.m406), false);
            addChildVSKRes_formular(itm, "m407", QString::number(VSKRes_formular.W4.m407), false);
            addChildVSKRes_formular(itm, "m408", QString::number(VSKRes_formular.W4.m408), false);
        }
        else  if(name == "Unit[1.1]")
        {
            addChildVSKRes_formular(itm, "m101N1", QString::number(VSKRes_formular.W2.m101N1), false);
            addChildVSKRes_formular(itm, "m101N2", QString::number(VSKRes_formular.W2.m101N2), false);
            addChildVSKRes_formular(itm, "m102N1", QString::number(VSKRes_formular.W2.m102N1), false);
            addChildVSKRes_formular(itm, "m102N2", QString::number(VSKRes_formular.W2.m102N2), false);
            addChildVSKRes_formular(itm, "m104", QString::number(VSKRes_formular.W2.m104), false);
        }
    }


}

void tvsk::addChildVSKRes_formular(QTreeWidgetItem *parent, QString name, QString description, bool addToParent)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);

    if(description == "1")
    {
        itm->setText(1, "OK");
        QBrush b (QColor(181, 230, 29)); //можно было бы делигат добавить и как в кайф менять цвет но, позже
        itm->setForeground(0,b);
        itm->setForeground(1,b);
    }
    else
    {
        itm->setText(1, "Error");
        QBrush b (Qt::red); //можно было бы делигат добавить и как в кайф менять цвет но, позже
        itm->setForeground(0,b);
        itm->setForeground(1,b);
    }
        parent->addChild(itm);
        if(!addToParent) return;

    // addChildVSKRes_formular(itm, "testTT", description, false); //на случай если нужно плодить уровни

}

void tvsk::slot_writeTempData_VSK(_VSKRes_formular VSKRes_formular) //нужно как минимум переделать на значение 1 - ок, иначе еррор
{
    ui->Tvsk->clear();
    if(VSKRes_formular.W2.SAP)
        addRootVSKRes_formular("VSK STATUS","OK", VSKRes_formular, false); //тут бы по хорошему переделать тоже
    else
        addRootVSKRes_formular("VSK STATUS","Error", VSKRes_formular, false);
    if(VSKRes_formular.W3.L_281_1_3)
        addRootVSKRes_formular("Master[1.3]","OK", VSKRes_formular, true);
    else
        addRootVSKRes_formular("Master[1.3]","Error", VSKRes_formular, true);
    if(VSKRes_formular.W5.L_281_1_3)
        addRootVSKRes_formular("Slave[1.3]","OK", VSKRes_formular, true);
    else
        addRootVSKRes_formular("Slave[1.3]","Error", VSKRes_formular, true);
    if(VSKRes_formular.W4.L281_1_4)
        addRootVSKRes_formular("Unit[1.4]","OK", VSKRes_formular, true);
    else
        addRootVSKRes_formular("Unit[1.4]","Error", VSKRes_formular, true);
    if(VSKRes_formular.W2.L281_1_1)
        addRootVSKRes_formular("Unit[1.1]","OK", VSKRes_formular, true);
    else
        addRootVSKRes_formular("Unit[1.1]","Error", VSKRes_formular, true);
    if(VSKRes_formular.W2.MSP_02_01)
        addRootVSKRes_formular("Unit[02_01]","OK", VSKRes_formular, false); //тут бы по хорошему переделать тоже
    else
        addRootVSKRes_formular("Unit[02_01]","Error", VSKRes_formular, false);
    if(VSKRes_formular.W2.MSP_02_02)
        addRootVSKRes_formular("Unit[02_02]","OK", VSKRes_formular, false); //тут бы по хорошему переделать тоже
    else
        addRootVSKRes_formular("Unit[02_02]","Error", VSKRes_formular, false);
    if(VSKRes_formular.W3.L_281_1_6PPS)
        addRootVSKRes_formular("Unit PPS[1.6]","OK", VSKRes_formular, false); //тут бы по хорошему переделать тоже
    else
        addRootVSKRes_formular("Unit PPS[1.6]","Error", VSKRes_formular, false);
    if(VSKRes_formular.W3.L_281_1_6ZPS)
        addRootVSKRes_formular("Unit ZPS[1.6]","OK", VSKRes_formular, false); //тут бы по хорошему переделать тоже
    else
        addRootVSKRes_formular("Unit ZPS[1.6]","Error", VSKRes_formular, false);
    if(VSKRes_formular.W2.L281_1_7)
        addRootVSKRes_formular("Unit[1.7]","OK", VSKRes_formular, false); //тут бы по хорошему переделать тоже
    else
        addRootVSKRes_formular("Unit[1.7]","Error", VSKRes_formular, false);

    // qDebug() << "1: " <<VSKRes_formular.W2.L281_1_1;
    // qDebug() << "1: " <<VSKRes_formular.W2.m101N1;
    // qDebug() << "1: " <<VSKRes_formular.W2.m101N2;
    // qDebug() << "1: " <<VSKRes_formular.W2.m102N1;
    // qDebug() << "1: " <<VSKRes_formular.W2.m102N2;
    // qDebug() << "1: " <<VSKRes_formular.W2.m104;
    // qDebug() << "1: " <<VSKRes_formular.W2.MSP_02_02;
    // qDebug() << "1: " <<VSKRes_formular.W2.MSP_02_01;
    // qDebug() << "1: " <<VSKRes_formular.W2.L281_1_7;
    // qDebug() << "1: " <<VSKRes_formular.W2.PK1_2_2;
    // qDebug() << "1: " <<VSKRes_formular.W2.PK1_2_1;
    // qDebug() << "1: " <<VSKRes_formular.W2.SAP;

    // qDebug() << "1: " <<VSKRes_formular.W3.L_281_1_3;
    // qDebug() << "1: " <<VSKRes_formular.W3.m301N2;
    // qDebug() << "1: " <<VSKRes_formular.W3.m301N1;
    // qDebug() << "1: " <<VSKRes_formular.W3.m302N2;
    // qDebug() << "1: " <<VSKRes_formular.W3.m302N1;
    // qDebug() << "1: " <<VSKRes_formular.W3.m303N2;
    // qDebug() << "1: " <<VSKRes_formular.W3.m303N1;
    // qDebug() << "1: " <<VSKRes_formular.W3.m305;
    // qDebug() << "1: " <<VSKRes_formular.W3.m306;
    // qDebug() << "1: " <<VSKRes_formular.W3.m307;
    // qDebug() << "1: " <<VSKRes_formular.W3.L_281_1_6ZPS;
    // qDebug() << "1: " <<VSKRes_formular.W3.L_281_1_6PPS;

    // qDebug() << "1: " <<VSKRes_formular.W4.L281_1_4;
    // qDebug() << "1: " <<VSKRes_formular.W4.m402;
    // qDebug() << "1: " <<VSKRes_formular.W4.m403N2;
    // qDebug() << "1: " <<VSKRes_formular.W4.m403N1;
    // qDebug() << "1: " <<VSKRes_formular.W4.m405;
    // qDebug() << "1: " <<VSKRes_formular.W4.m406;
    // qDebug() << "1: " <<VSKRes_formular.W4.m407;
    // qDebug() << "1: " <<VSKRes_formular.W4.m408;

    // qDebug() << "1: " <<VSKRes_formular.W5.L_281_1_3;
    // qDebug() << "1: " <<VSKRes_formular.W5.m301N4;
    // qDebug() << "1: " <<VSKRes_formular.W5.m301N3;
    // qDebug() << "1: " <<VSKRes_formular.W5.m302N4;
    // qDebug() << "1: " <<VSKRes_formular.W5.m302N3;
    // qDebug() << "1: " <<VSKRes_formular.W5.m303N4;
    // qDebug() << "1: " <<VSKRes_formular.W5.m303N3;
    // qDebug() << "1: " <<VSKRes_formular.W5.m305_1;
    // qDebug() << "1: " <<VSKRes_formular.W5.m306_1;
    // qDebug() << "1: " <<VSKRes_formular.W5.m307_1;
    // qDebug() << "1: " <<VSKRes_formular.W5.Word_Valid;
}
