#include "tsap.h"
#include "ui_tsap.h"

Tsap::Tsap(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tsap)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    Table = new _TableFormularTargets*[m_rows];
    for (int i = 0; i < m_rows; i++)
        Table[i] = new _TableFormularTargets[m_cols];

    nIndex = 0;
    ui->widget->axisRect()->setBackground(Qt::black);
    ui->widget->setBackground(Qt::black);
//    QCPGraph* graph1 = ui->widget->addGraph();
//    QCPGraph* graph2 = ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->addGraph();
    //ui->widget->graph(0)->setData(vec_x, vec_y);
    // ui->widget->xAxis->setLabel("x");
    // ui->widget->yAxis->setLabel("y");
    ui->widget->yAxis->setBasePen(QPen(QColor(181, 230, 29), 2)); //цвет основкой полосы у 181, 230, 29
    //ui->widget->xAxis->setBasePen(QPen(QColor(181, 230, 29), 2)); //цвет основной полосы х
    ui->widget->xAxis->setBasePen(QPen(QColor(255, 255, 255, 0), 0)); //цвет основной полосы х
    ui->widget->yAxis->setTickPen(QPen(QColor(181, 230, 29), 1)); //цвет заглавных палок шкалы
    //ui->widget->xAxis->setTickPen(QPen(QColor(181, 230, 29), 1)); //цвет заглавных палок шкалы
    ui->widget->xAxis->setTickPen(QPen(QColor(255, 255, 255, 0), 0)); //цвет заглавных палок шкалы
    ui->widget->yAxis->setSubTickPen(QPen(QColor(181, 230, 29), 1)); //цвет придаточных полупалок шкалы
    //ui->widget->xAxis->setSubTickPen(QPen(QColor(181, 230, 29), 1)); //цвет придаточных полупалок шкалы
    ui->widget->xAxis->setSubTickPen(QPen(QColor(255, 255, 255, 0), 0)); //цвет придаточных полупалок шкалы
    ui->widget->yAxis->setTickLabelColor(QColor(181, 230, 29)); //цвет наименований делений
    ui->widget->xAxis->setTickLabelColor(QColor(181, 230, 29)); //цвет наименований делений
    ui->widget->yAxis->grid()->setPen(QPen(QColor(181, 230, 29), 1, Qt::DotLine)); //цвет придаточных полупалок шкалы
    ui->widget->xAxis->grid()->setPen(QPen(QColor(181, 230, 29), 1, Qt::DotLine)); //цвет придаточных полупалок шкалы
    ui->widget->xAxis->grid()->setZeroLinePen(Qt::NoPen); //отрисовка начальных линий на всю ивановскую нули
    ui->widget->yAxis->grid()->setZeroLinePen(QPen(QColor(181, 230, 29), 2, Qt::SolidLine)); //отрисовка начальных линий на всю ивановскую нули
    ui->widget->xAxis->setRange(0,3); // начальная область видимости
    ui->widget->yAxis->setRange(-80,80); // начальная область видимости
    //ui->widget->yAxis->setRangeReversed(true);

    //ui->widget->yAxis->grid()->setSubGridVisible(true); //если нужно добавить на график мелкие деления и сетку их
    //ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(181, 230, 29), 1, Qt::DotLine)); //цвет придаточных полупалок шкалы;

    QSharedPointer<QCPAxisTickerFixed> fixedTickeryAxis(new QCPAxisTickerFixed);
    ui->widget->yAxis->setTicker(fixedTickeryAxis);
    fixedTickeryAxis->setTickStep(10.0); // tick step shall be 1.0
    fixedTickeryAxis->setScaleStrategy(QCPAxisTickerFixed::ssNone); // and no scaling of the tickstep (like multiples or powers) is allowed
    ui->widget->yAxis->scaleRange(1, 0); //цена деления шкалы по Y

    QSharedPointer<QCPAxisTickerFixed> fixedTickerxAxis(new QCPAxisTickerFixed);
    ui->widget->xAxis->setTicker(fixedTickerxAxis);
    fixedTickerxAxis->setTickStep(1); // tick step shall be 1.0
    fixedTickerxAxis->setScaleStrategy(QCPAxisTickerFixed::ssNone); // and no scaling of the tickstep (like multiples or powers) is allowed
    ui->widget->xAxis->scaleRange(1, 0); //цена деления шкалы по Х

    QSharedPointer<QCPAxisTickerText> TickerTextyAxis(new QCPAxisTickerText);
    TickerTextyAxis->addTick(100,"10");
    TickerTextyAxis->addTick(90, "20");
    TickerTextyAxis->addTick(80, "30");
    TickerTextyAxis->addTick(70, "40");
    TickerTextyAxis->addTick(60, "50");
    TickerTextyAxis->addTick(50, "60");
    TickerTextyAxis->addTick(40, "70");
    TickerTextyAxis->addTick(30, "80");
    TickerTextyAxis->addTick(20, "90");
    TickerTextyAxis->addTick(10, "100");
    TickerTextyAxis->addTick( 0, ""  );
    TickerTextyAxis->addTick(-10,"100");
    TickerTextyAxis->addTick(-20, "90");
    TickerTextyAxis->addTick(-30, "80");
    TickerTextyAxis->addTick(-40, "70");
    TickerTextyAxis->addTick(-50, "60");
    TickerTextyAxis->addTick(-60, "50");
    TickerTextyAxis->addTick(-70, "40");
    TickerTextyAxis->addTick(-80, "30");
    TickerTextyAxis->addTick(-90, "20");
    TickerTextyAxis->addTick(-100,"10");
    ui->widget->yAxis->setTicker(TickerTextyAxis);
    ui->widget->yAxis->setTickLabelFont(QFont(QFont().family(), 12));


    //    customScatterPath = QPixmap(":/TrianglePRM.svg");
    //    customScatterPath.scaled(QSize(0,0));
    customScatterPath.convertFromImage(QImage(":/TrianglePRM.svg").scaled(500, 500));
    customScatterPath3.convertFromImage(QImage(":/TrianglePRM.svg").scaled(500, 500));
    //ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(customScatterPath));
    customScatterPath2.convertFromImage(QImage(":/blue_triangle.png").scaled(35, 35)); //вставляем картинку и потом её изменяем
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    //ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QColor(30,180,0), 10));
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(customScatterPath2));
    customScatterPath4.convertFromImage(QImage(":/green_triangle.png").scaled(35, 35));
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(customScatterPath4));

    customScatterPath5.convertFromImage(QImage(":/blue_triangle.png").scaled(35, 35));
    ui->widget->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(customScatterPath5));
    // QPen pen;
    // pen.setColor(QColor(255,255,255,0));
    // pen.setStyle(Qt::DashLine);
    // pen.setWidth(2);
    // ui->widget->graph(0)->setPen(pen);
    // ui->widget->graph(0)->setName("Linear Function");
    // ui->widget->legend->setVisible(true);
    //QImage(":/blue_triangle.png").scaled(10, 10);

    //TODO: Нужно всё это переносить кудато, и по хорошему переделать
    itemPixmap = new QCPItemPixmap(ui->widget);
    itemPixmap->setPixmap(customScatterPath);
    itemPixmap->setVisible(true);
    itemPixmap->setScaled(true);
    pixX1 = 1.3; //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    pixX2 = 1.8; //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    itemPixmap->topLeft->setCoords(pixX1, 11); //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет//нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    itemPixmap->bottomRight->setCoords(pixX2, 0.1); //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    m_ItemPixmap = itemPixmap; //с этим тоже нужно что-то делать
    itemPixmapArray.push_back(itemPixmap); //ровно точно так же как и сэтим


    itemPixmap2 = new QCPItemPixmap(ui->widget);
    itemPixmap2->setPixmap(customScatterPath3);
    itemPixmap2->setVisible(true);
    itemPixmap2->setScaled(true);
    pixX1 = 1.3; //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    pixX2 = 1.8; //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    itemPixmap2->topLeft->setCoords(pixX1, -11); //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    itemPixmap2->bottomRight->setCoords(pixX2, -0.1); //нужно масштабировать иначе, относительно самого плота, иначе при масштабировании плота, всё уедет
    // m_ItemPixmap2 = itemPixmap2;
    itemPixmapArray.push_back(itemPixmap2);//с этим тоже нужно что-то делать
    //itemPixmap->position()->setPixelPosition()

    QCPItemText* itemText = new QCPItemText(ui->widget);//это все что тносится к маленькой текстовой табличке
    itemText->setLayer("overlay");
    itemText->setPositionAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    itemText->position->setType(QCPItemPosition::ptAxisRectRatio);
    itemText->position->setCoords(0.5, 0.1); //0.5 0.1
    itemText->setText("Point Information\n");
    itemText->setPadding(QMargins(5,5,5,5));
    itemText->setPen(QPen(Qt::black));
    itemText->setBrush(QColor(255, 0, 255));
    m_ItemText = itemText;

    ui->widget->layer("overlay")->setVisible(false);
    ui->widget->setInteractions(/*QCP::iRangeDrag*/ /*|QCP::iRangeZoom |*/ QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend);

    connect(ui->widget, SIGNAL(plottableClick(QCPAbstractPlottable*, int, QMouseEvent*)), this, SLOT(Slot_clickGraph(QCPAbstractPlottable*, int, QMouseEvent*)));

    //connect(ui->pbStop, SIGNAL(clicked()), this, SLOT(Slot_finAddData()));

    // srand(QTime::currentTime().msec()); //заводим таймер для обновления данных в миллисекундах
    // connect(&timer, SIGNAL(timeout()), this, SLOT(Slot_addData())); // обновляем данные на графике по сигналу таймаута от таймера ниже
    // timer.start(100);//каждые 100 миллесекунда мы переписываем данные и обновляем данные
    ui->widget->replot(); //обновляем этой функцией
}

void Tsap::Slot_clickGraph(QCPAbstractPlottable* potItem, int num, QMouseEvent* event)
{
    ui->stackedWidget->setCurrentIndex(1);

    double dX = potItem->interface1D()->dataMainKey(num);
    double dY = potItem->interface1D()->dataMainValue(num);

    ui->widget->layer("overlay")->setVisible(true);

    m_ItemText->setText(QString("Point Information\nX = %1\nY = %2").arg(QString::number(dX)).arg(QString::number(dY)));

    ui->widget->replot();
    getTable(0,0);


}

void Tsap::Slot_addData()
{

    int nRand = rand() % 1;
    //ui->widget->graph(0)->addData(nIndex++, nRand);
    //ui->widget->graph(0)->addData(vec_x[0], vec_y[0]);
    ui->widget->graph(1)->addData(0.5, 5);
    ui->widget->graph(0)->addData(1.5, 15);
    ui->widget->graph(1)->addData(2.5, 25);
    ui->widget->graph(0)->addData(1.5, 35);
    ui->widget->graph(1)->addData(0.5, 45);
    ui->widget->graph(0)->addData(1.5, 55);
    ui->widget->graph(1)->addData(2.5, 65);
    ui->widget->graph(1)->addData(0.5, -5);
    ui->widget->graph(0)->addData(1.5, -15);
    ui->widget->graph(1)->addData(2.5, -25);
    ui->widget->graph(0)->addData(1.5, -35);
    ui->widget->graph(1)->addData(0.5, -45);
    ui->widget->graph(0)->addData(1.5, -55);
    ui->widget->graph(1)->addData(2.5, -65);

    //    if (nIndex >+ 3)
    //    {
    //        ui->widget->xAxis->moveRange(1);
    //        pixX1++;pixX2++;
    //        itemPixmapArray[0]->topLeft->setCoords(pixX1, 11); //0.5 0.1
    //        itemPixmapArray[0]->bottomRight->setCoords(pixX2, 0.1); //0.5 0.1
    //        itemPixmapArray[1]->topLeft->setCoords(pixX1, -11);
    //        itemPixmapArray[1]->bottomRight->setCoords(pixX2, -0.1);
    //    }

    ui->widget->replot();
}

void Tsap::slot_addingSignalsToPlot(QVector<_SignalParam_formular> Targets)
{
    for(int i = 0; i < 3; ++i)
    {
        ui->widget->graph(i)->data().data()->clear();
    }
       // ui->widget->replot();

    int k = -1;
    float kni = 0.5, is = 1.5, other = 2.5;
    for(int i = 0; i < Targets.size(); ++i)
    {
        if(Targets[i].W6.Amplitude < 100)
            k = Targets[i].W6.Amplitude * 0.1 - 3;
        else
            k = 6;
        switch (k) {  //переделать на чуть по лучше вариантик
        case 0:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 75);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -75);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 75);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -75);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 75);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -75);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 1:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 65);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -65);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 65);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -65);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 65);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -65);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 2:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 55);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -55);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 55);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -55);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 55);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -55);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 3:
            if(Targets[i].W9.TipPomehi >= 12 || Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 45);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -45);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 45);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -45);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 45);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -45);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 4:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 35);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -35);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 35);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -35);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 35);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -35);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 5:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 25);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -25);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 25);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -25);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 25);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -25);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 6:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 15);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -15);
                    setTable(1,0,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 15);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -15);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 15);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -15);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        case 7:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 5);
                    setTable(0,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -5);
                    setTable(1,0,Targets[i]);
                }

            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 5);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -5);
                    setTable(1,1,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 5);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -5);
                    setTable(1,2,Targets[i]);
                }
            }
            break;
        default:
            break;
        }
    }
    ui->widget->replot();
}


Tsap::~Tsap()
{
    for (int i = 0; i < m_rows; i++)
        delete[] Table[i];

    delete[] Table;
    delete ui;
}

void Tsap::setTable(int col, int row, _SignalParam_formular Targets)
{
    _formularTargetsForTable TempTargets;
    TempTargets.Carrier = Targets.W3.Carrier;
    TempTargets.Dlit = Targets.W4.DlitImp;
    TempTargets.Per = Targets.W5.PulsePeriod_ml;
    Table[row][col].TargetsTable.push_back(TempTargets);
}

QVector<_formularTargetsForTable> Tsap::getTable(int col, int row)
{
    QVector<_formularTargetsForTable> TempTargets;
    for(int i = 0; i < 2; ++i)
    {
        qDebug() << "колонка: " << i;
        for(int j = 0; j < 2; ++j)
        {
            qDebug() << "строка: " << j;
            if(Table[j][i].TargetsTable.size())
                qDebug() << "размер: " << Table[j][i].TargetsTable[j].Carrier;
            // qDebug() << "Частота: " << Table[j][i].TargetsTable[j].Carrier;
            // qDebug() << "Длит: " << Table[j][i].TargetsTable[j].Dlit;
            // qDebug() << "Период: " << Table[j][i].TargetsTable[j].Per;
        }
    }
    return Table[row][col].TargetsTable;
}

void Tsap::Slot_set_workingmode_from_mw(unsigned char value, unsigned short countTargetsPPS, unsigned short countTargetsZPS)
{
    qDebug() << "value: " << value;
    if(value == 2)
    {
        if(countTargetsPPS)
        {
            customScatterPath.convertFromImage(QImage(":/TrianglePRD.svg").scaled(500, 500));
            itemPixmapArray[0]->setPixmap(customScatterPath);
        }
        else if (!countTargetsPPS)
        {
            customScatterPath.convertFromImage(QImage(":/TrianglePRM.svg").scaled(500, 500));
            itemPixmapArray[0]->setPixmap(customScatterPath);
        }
        if(countTargetsZPS)
        {
            customScatterPath3.convertFromImage(QImage(":/TrianglePRD.svg").scaled(500, 500));
            itemPixmapArray[1]->setPixmap(customScatterPath3);
        }
        else if(!countTargetsZPS)
        {
            customScatterPath3.convertFromImage(QImage(":/TrianglePRM.svg").scaled(500, 500));
            itemPixmapArray[1]->setPixmap(customScatterPath3);
        }

    }
    else if (value == 1)
    {
        customScatterPath.convertFromImage(QImage(":/TrianglePRM.svg").scaled(500, 500));
        itemPixmapArray[0]->setPixmap(customScatterPath);
        customScatterPath3.convertFromImage(QImage(":/TrianglePRM.svg").scaled(500, 500));
        itemPixmapArray[1]->setPixmap(customScatterPath3);
    }
}
