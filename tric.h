#ifndef TRIC_H
#define TRIC_H

#include <QWidget>
//#include "mainwindow.h"
#include "Targets.h"
#include <QVector>
#include <QTreeWidget>

namespace Ui {
class Tric;
}

class Tric : public QWidget
{
    Q_OBJECT

public:
    explicit Tric(QWidget *parent = nullptr);
    ~Tric();
    // может сделать гибче конечно, может уже в конце так и сделаю
    void addRootPeriodical_formular( QString name, _Periodical_formular Periodical_formular);
    void addRootTargets_formular( QString name, _SignalParam_formular Targets);
    void addChildPeriodical_formular(QTreeWidgetItem *parent ,QString name, QString description);
    void addChildTargets_formular(QTreeWidgetItem *parent ,QString name, QString description);

private:
    Ui::Tric *ui;

private slots:

public slots:

    void slot_writeTempData(_Periodical_formular, QVector<_SignalParam_formular>);
signals:

};

#endif // TRIC_H
