#ifndef INITBASICSTYLE_H
#define INITBASICSTYLE_H

#include <QString>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
//#include <mainwindow.h>
#include <QWidget>



class VerticalQLable: public QLabel
{
    Q_OBJECT
public:
    explicit VerticalQLable(QWidget *parent = 0);
    explicit VerticalQLable(const QString &text, QWidget *parent = 0);
    //static QString

protected:
    void paintEvent(QPaintEvent*);
    QSize sizeHint () const;
    QSize minimumSizeHint() const;

};



#endif // INITBASICSTYLE_H
