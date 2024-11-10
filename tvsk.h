#ifndef TVSK_H
#define TVSK_H

#include <QWidget>
#include "Targets.h"
#include <QTreeWidget>

namespace Ui {
class tvsk;
}

class tvsk : public QWidget
{
    Q_OBJECT

public:
    explicit tvsk(QWidget *parent = nullptr);
    ~tvsk();
    void addRootVSKRes_formular( QString name, QString description, _VSKRes_formular VSKRes_formular, bool addToParent);
    void addChildVSKRes_formular(QTreeWidgetItem *parent ,QString name, QString description, bool addToParent);
private:
    Ui::tvsk *ui;

public slots:
    void slot_writeTempData_VSK(_VSKRes_formular);
};

#endif // TVSK_H
