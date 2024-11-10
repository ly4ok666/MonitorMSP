#include "tric.h"
#include "ui_tric.h"
#include <QDebug>

Tric::Tric(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tric)
{
    ui->setupUi(this);
    ui->Ttargets_sap->setColumnCount(2);

}

Tric::~Tric()
{
    delete ui;
}

void Tric::addRootPeriodical_formular(QString name, _Periodical_formular Periodical_formular)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->Ttargets_sap);
    ui->Ttargets_sap->expandItem( itm);
    itm->setText(0, name);
    //ui->Ttargets_sap->addTopLevelItem(parent);
    addChildPeriodical_formular(itm, "Visota", QString::number(Periodical_formular.W5.Visota));
    addChildPeriodical_formular(itm, "AVT_quit", QString::number(Periodical_formular.W6.AVT_quit));
    addChildPeriodical_formular(itm, "CU_quit", QString::number(Periodical_formular.W6.CU_quit));
    addChildPeriodical_formular(itm, "BCVM_Connection", QString::number(Periodical_formular.W6.BCVM_Connection));
    addChildPeriodical_formular(itm, "FHS_Enable", QString::number(Periodical_formular.W6.FHS_Enable));
    addChildPeriodical_formular(itm, "RHS_Enable", QString::number(Periodical_formular.W6.RHS_Enable));
    addChildPeriodical_formular(itm, "IzluchPPS", QString::number(Periodical_formular.W6.IzluchPPS));
    addChildPeriodical_formular(itm, "IzluchZPS", QString::number(Periodical_formular.W6.IzluchZPS));
    addChildPeriodical_formular(itm, "StationModes", QString::number(Periodical_formular.W6.StationModes));
    addChildPeriodical_formular(itm, "VSKStatus", QString::number(Periodical_formular.W6.VSKStatus));
    addChildPeriodical_formular(itm, "VzaimnZash", QString::number(Periodical_formular.W6.VzaimnZash));
    addChildPeriodical_formular(itm, "m302_0_obsl", QString::number(Periodical_formular.W7.m302_0_obsl));
    addChildPeriodical_formular(itm, "m302_1_obsl", QString::number(Periodical_formular.W7.m302_1_obsl));
    addChildPeriodical_formular(itm, "m302_0_neobsl", QString::number(Periodical_formular.W8.m302_0_neobsl));
    addChildPeriodical_formular(itm, "m302_1_neobsl", QString::number(Periodical_formular.W8.m302_1_neobsl));
}

void Tric::addRootTargets_formular( QString name, _SignalParam_formular Targets)
{

    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->Ttargets_sap);
    ui->Ttargets_sap->expandItem( itm);
    itm->setText(0, name);
    //ui->Ttargets_sap->addTopLevelItem(parent);
    addChildTargets_formular(itm, "semisphere", QString::number(Targets.W2.semisphere));
    addChildTargets_formular(itm, "m302num", QString::number(Targets.W2.m302num));
    addChildTargets_formular(itm, "WorkingFlag", QString::number(Targets.W2.WorkingFlag));
    addChildTargets_formular(itm, "Carrier", QString::number(Targets.W3.Carrier));
    addChildTargets_formular(itm, "DlitImp", QString::number(Targets.W4.DlitImp));
    addChildTargets_formular(itm, "PulsePeriod_ml", QString::number(Targets.W5.PulsePeriod_ml));
    addChildTargets_formular(itm, "PulsePeriod_st", QString::number(Targets.W6.PulsePeriod_st));
    addChildTargets_formular(itm, "Amplitude", QString::number(Targets.W6.Amplitude));
    addChildTargets_formular(itm, "Signal_type", QString::number(Targets.W7.Signal_type));
    addChildTargets_formular(itm, "EtapRaboty", QString::number(Targets.W7.EtapRaboty));
    addChildTargets_formular(itm, "Spectrum", QString::number(Targets.W8.Spectrum));
    addChildTargets_formular(itm, "PeriodPovtPachki", QString::number(Targets.W9.PeriodPovtPachki));
    addChildTargets_formular(itm, "TipPomehi", QString::number(Targets.W9.TipPomehi));
    addChildTargets_formular(itm, "DlitPachki", QString::number(Targets.W10.DlitPachki));

}

void Tric::addChildPeriodical_formular(QTreeWidgetItem *parent, QString name, QString description)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);
    itm->setText(1, description);



    parent->addChild(itm);
}

void Tric::addChildTargets_formular(QTreeWidgetItem *parent, QString name, QString description)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, name);
    itm->setText(1, description);

    parent->addChild(itm);
}



void Tric::slot_writeTempData(_Periodical_formular Periodical_formular, QVector<_SignalParam_formular> Targets)
{
    ui->Ttargets_sap->clear();
    addRootPeriodical_formular( "SAP_Status", Periodical_formular);


    // qDebug() << "Periodical_formular.W5.Visota = " << Periodical_formular.W5.Visota;;
    // qDebug() << "Periodical_formular.W6.AVT_quit = " << Periodical_formular.W6.AVT_quit;
    // qDebug() << "Periodical_formular.W6.CU_quit = " << Periodical_formular.W6.CU_quit;
    // qDebug() << "Periodical_formular.W6.BCVM_Connection = " << Periodical_formular.W6.BCVM_Connection;
    // qDebug() << "Periodical_formular.W6.FHS_Enable = " << Periodical_formular.W6.FHS_Enable;
    // qDebug() << "Periodical_formular.W6.RHS_Enable = " << Periodical_formular.W6.RHS_Enable;
    // qDebug() << "Periodical_formular.W6.IzluchPPS = " << Periodical_formular.W6.IzluchPPS;
    // qDebug() << "Periodical_formular.W6.IzluchZPS = " << Periodical_formular.W6.IzluchZPS;
    // qDebug() << "Periodical_formular.W6.StationModes = " << Periodical_formular.W6.StationModes;
    // qDebug() << "Periodical_formular.W6.VSKStatus = " << Periodical_formular.W6.VSKStatus;
    // qDebug() << "Periodical_formular.W6.VzaimnZash = " << Periodical_formular.W6.VzaimnZash;
    // qDebug() << "Periodical_formular.W7.m302_0_obsl = " << Periodical_formular.W7.m302_0_obsl;
    // qDebug() << "Periodical_formular.W7.m302_1_obsl = " << Periodical_formular.W7.m302_1_obsl;
    // qDebug() << "Periodical_formular.W8.m302_0_neobsl = " << Periodical_formular.W8.m302_0_neobsl;
    // qDebug() << "Periodical_formular.W8.m302_1_neobsl = " << Periodical_formular.W8.m302_1_neobsl;

    for(int i = 0; i < Targets.size(); ++i)
    {
        addRootTargets_formular( "Targets", Targets[i]);
        // qDebug() << "Targets[" << i << "].W2.semisphere: " << Targets[i].W2.semisphere;
        // qDebug() << "Targets[" << i << "].W2.m302num: " << Targets[i].W2.m302num;
        // qDebug() << "Targets[" << i << "].W2.WorkingFlag: " << Targets[i].W2.WorkingFlag;
        // qDebug() << "Targets[" << i << "].W3.Carrier: " << Targets[i].W3.Carrier;
        // qDebug() << "Targets[" << i << "].W4.DlitImp: " << Targets[i].W4.DlitImp;
        // qDebug() << "Targets[" << i << "].W5.PulsePeriod_ml: " << Targets[i].W5.PulsePeriod_ml;
        // qDebug() << "Targets[" << i << "].W6.PulsePeriod_st: " << Targets[i].W6.PulsePeriod_st;
        // qDebug() << "Targets[" << i << "].W6.Amplitude: " << Targets[i].W6.Amplitude;
        // qDebug() << "Targets[" << i << "].W7.Signal_type: " << Targets[i].W7.Signal_type;
        // qDebug() << "Targets[" << i << "].W7.EtapRaboty: " << Targets[i].W7.EtapRaboty;
        // qDebug() << "Targets[" << i << "].W8.Spectrum: " << Targets[i].W8.Spectrum;
        // qDebug() << "Targets[" << i << "].W9.PeriodPovtPachki: " << Targets[i].W9.PeriodPovtPachki;
        // qDebug() << "Targets[" << i << "].W9.TipPomeh: " << Targets[i].W9.TipPomehi;
        // qDebug() << "Targets[" << i << "].W10.DlitPachki: " << Targets[i].W10.DlitPachki;
    }

}

