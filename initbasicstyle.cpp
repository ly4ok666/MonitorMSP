#include "initbasicstyle.h"


VerticalQLable::VerticalQLable(QWidget *parent) : QLabel(parent)
{

}

VerticalQLable::VerticalQLable(const QString &text, QWidget *parent) : QLabel(text, parent)
{

}

void VerticalQLable::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //painter.setPen(Qt::blue);
    painter.setBrush(Qt::Dense1Pattern);

    painter.rotate(90);

    painter.drawText(0,0, text());
}

QSize VerticalQLable::sizeHint () const
{
    QSize s = QLabel::sizeHint();
    return QSize(s.height(), s.width());

}
QSize VerticalQLable::minimumSizeHint() const
{
    QSize s = QLabel::sizeHint();
    return QSize(s.height(), s.width());
}


