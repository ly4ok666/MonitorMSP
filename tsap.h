#ifndef TSAP_H
#define TSAP_H

#include <QWidget>
#include <qcustomplot.h>
#include "Targets.h"
#include <QMap>

namespace Ui {
class Tsap;
}

typedef struct {
    unsigned Carrier;
    unsigned Dlit;
    unsigned Per;
} _formularTargetsForTable;
typedef struct
{
    QVector<_formularTargetsForTable> TargetsTable;
} _TableFormularTargets;

class Tsap : public QWidget
{
    Q_OBJECT

public:
    explicit Tsap(QWidget *parent = nullptr);
    ~Tsap();
    void setTable(int col, int row, _SignalParam_formular Targets);
    QVector<_formularTargetsForTable> getTable(int col, int row);
private:
    Ui::Tsap *ui;

    //тут нужно доразобраться что и зачем ме нужно будет
    QVector<double> vec_x, vec_y;
    QVector<QCPItemPixmap*> itemPixmapArray;
    double pixX1, pixX2;
    QCPItemText* m_ItemText;
    QCPItemPixmap* m_ItemPixmap;
    QCPItemPixmap* m_ItemPixmap2;
    QCPItemPixmap* itemPixmap;
    QCPItemPixmap* itemPixmap2;
    QPixmap customScatterPath, customScatterPath2, customScatterPath3, customScatterPath4, customScatterPath5;
    int nIndex;
    QTimer timer;
    int m_rows = 3;
    int m_cols = 2;
    _TableFormularTargets** Table;;




public slots:
    //данный слот создан для получения данных по сигналу: void signals_for_sap_workingmode(); в майн виндоус!!
    void Slot_set_workingmode_from_mw(unsigned char, unsigned short, unsigned short);

    void Slot_clickGraph(QCPAbstractPlottable*, int, QMouseEvent*);
    void Slot_addData();
    void slot_addingSignalsToPlot(QVector<_SignalParam_formular>);
};


#endif // TSAP_H
