#include "tsap.h"
#include "ui_tsap.h"

Tsap::Tsap(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tsap)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->tableWidget->setColumnCount(192);
    ui->tableWidget->setRowCount(18);

    for(int wCol = 0; wCol < 192; wCol += 2)
    {
        ui->tableWidget->setColumnHidden(wCol,true);
        ui->tableWidget->setColumnHidden(wCol-1,true);
        ui->tableWidget->setColumnHidden(191,true);
        for(int wRow = 0; wRow < 18; wRow += 3)
        {
            ui->tableWidget->setSpan(wRow,wCol,3,1);
        }
    }

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
    HidenColandRow(getLastSign(), false);
    // item->setTextAlignment(Qt::AlignJustify); // 1
    // item->setTextAlignment(Qt::AlignHCenter); // 2
    QVector<_formularTargetsForTable> TempTargets;
    double dX = potItem->interface1D()->dataMainKey(num);
    double dY = potItem->interface1D()->dataMainValue(num);

    int dx = dX;
    int y = std::abs(dY);
    int dy;
    switch(y)
    {
    case 5: //100++
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(32);
                setLastSign(23);
            }
            if(dx == 1)
            {
                ShowColandRow(96);
                setLastSign(96);
            }
            if(dx == 2)
            {
                ShowColandRow(160);
                setLastSign(160);
            }
//            dy = 7;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(32,false);
//            ui->tableWidget->setColumnHidden(33,false);
//            ui->tableWidget->setColumnHidden(34,false);
//            ui->tableWidget->setColumnHidden(35,false);
// 1
//            ui->tableWidget->setColumnHidden(96,false);
//            ui->tableWidget->setColumnHidden(97,false);
//            ui->tableWidget->setColumnHidden(98,false);
//            ui->tableWidget->setColumnHidden(99,false);
// 2
//            ui->tableWidget->setColumnHidden(160,false);
//            ui->tableWidget->setColumnHidden(161,false);
//            ui->tableWidget->setColumnHidden(162,false);
//            ui->tableWidget->setColumnHidden(163,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(0);
                setLastSign(0);
            }
            if(dx == 1)
            {
                ShowColandRow(64);
                setLastSign(64);
            }
            if(dx == 2)
            {
                ShowColandRow(128);
                setLastSign(128);
            }
//            dy = 15;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(0,false);
//            ui->tableWidget->setColumnHidden(1,false);
//            ui->tableWidget->setColumnHidden(2,false);
//            ui->tableWidget->setColumnHidden(3,false);
            // 1
            //            ui->tableWidget->setColumnHidden(64,false);
            //            ui->tableWidget->setColumnHidden(65,false);
            //            ui->tableWidget->setColumnHidden(66,false);
            //            ui->tableWidget->setColumnHidden(67,false);
            // 2
            //            ui->tableWidget->setColumnHidden(128,false);
            //            ui->tableWidget->setColumnHidden(129,false);
            //            ui->tableWidget->setColumnHidden(130,false);
            //            ui->tableWidget->setColumnHidden(131,false);
        }
        break;
    case 15: //90-100
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(36);
                setLastSign(36);
            }
            if(dx == 1)
            {
                ShowColandRow(100);
                setLastSign(100);
            }
            if(dx == 2)
            {
                ShowColandRow(164);
                setLastSign(164);
            }
//            dy = 6;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(36,false);
//            ui->tableWidget->setColumnHidden(37,false);
//            ui->tableWidget->setColumnHidden(38,false);
//            ui->tableWidget->setColumnHidden(39,false);
// 1
//            ui->tableWidget->setColumnHidden(100,false);
//            ui->tableWidget->setColumnHidden(101,false);
//            ui->tableWidget->setColumnHidden(102,false);
//            ui->tableWidget->setColumnHidden(103,false);
// 2
//            ui->tableWidget->setColumnHidden(164,false);
//            ui->tableWidget->setColumnHidden(165,false);
//            ui->tableWidget->setColumnHidden(166,false);
//            ui->tableWidget->setColumnHidden(167,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(4);
                setLastSign(4);
            }
            if(dx == 1)
            {
                ShowColandRow(68);
                setLastSign(68);
            }
            if(dx == 2)
            {
                ShowColandRow(132);
                setLastSign(132);
            }

//            dy = 14;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(4,false);
//            ui->tableWidget->setColumnHidden(5,false);
//            ui->tableWidget->setColumnHidden(6,false);
//            ui->tableWidget->setColumnHidden(7,false);
// 1
//            ui->tableWidget->setColumnHidden(68,false);
//            ui->tableWidget->setColumnHidden(69,false);
//            ui->tableWidget->setColumnHidden(70,false);
//            ui->tableWidget->setColumnHidden(71,false);
// 2
//            ui->tableWidget->setColumnHidden(132,false);
//            ui->tableWidget->setColumnHidden(133,false);
//            ui->tableWidget->setColumnHidden(134,false);
//            ui->tableWidget->setColumnHidden(135,false);
        }
        break;
    case 25: //80-90
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(40);
                setLastSign(40);
            }
            if(dx == 1)
            {
                ShowColandRow(104);
                setLastSign(104);
            }
            if(dx == 2)
            {
                ShowColandRow(168);
                setLastSign(168);
            }
//            dy = 5;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(40,false);
//            ui->tableWidget->setColumnHidden(41,false);
//            ui->tableWidget->setColumnHidden(42,false);
//            ui->tableWidget->setColumnHidden(43,false);
// 1
//            ui->tableWidget->setColumnHidden(104,false);
//            ui->tableWidget->setColumnHidden(105,false);
//            ui->tableWidget->setColumnHidden(106,false);
//            ui->tableWidget->setColumnHidden(107,false);
// 2
//            ui->tableWidget->setColumnHidden(168,false);
//            ui->tableWidget->setColumnHidden(169,false);
//            ui->tableWidget->setColumnHidden(170,false);
//            ui->tableWidget->setColumnHidden(171,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(8);
                setLastSign(8);
            }
            if(dx == 1)
            {
                ShowColandRow(72);
                setLastSign(72);
            }
            if(dx == 2)
            {
                ShowColandRow(136);
                setLastSign(136);
            }
//            dy = 13;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(8,false);
//            ui->tableWidget->setColumnHidden(9,false);
//            ui->tableWidget->setColumnHidden(10,false);
//            ui->tableWidget->setColumnHidden(11,false);
// 1
//            ui->tableWidget->setColumnHidden(72,false);
//            ui->tableWidget->setColumnHidden(73,false);
//            ui->tableWidget->setColumnHidden(74,false);
//            ui->tableWidget->setColumnHidden(75,false);
// 2
//            ui->tableWidget->setColumnHidden(136,false);
//            ui->tableWidget->setColumnHidden(137,false);
//            ui->tableWidget->setColumnHidden(138,false);
//            ui->tableWidget->setColumnHidden(139,false);
        }
        break;
    case 35: //70-80
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(44);
                setLastSign(44);
            }
            if(dx == 1)
            {
                ShowColandRow(108);
                setLastSign(108);
            }
            if(dx == 2)
            {
                ShowColandRow(172);
                setLastSign(172);
            }
//            dy = 4;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(44,false);
//            ui->tableWidget->setColumnHidden(45,false);
//            ui->tableWidget->setColumnHidden(46,false);
//            ui->tableWidget->setColumnHidden(47,false);
// 1
//            ui->tableWidget->setColumnHidden(108,false);
//            ui->tableWidget->setColumnHidden(109,false);
//            ui->tableWidget->setColumnHidden(110,false);
//            ui->tableWidget->setColumnHidden(111,false);
// 2
//            ui->tableWidget->setColumnHidden(172,false);
//            ui->tableWidget->setColumnHidden(173,false);
//            ui->tableWidget->setColumnHidden(174,false);
//            ui->tableWidget->setColumnHidden(175,false);

        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(12);
                setLastSign(12);
            }
            if(dx == 1)
            {
                ShowColandRow(76);
                setLastSign(76);
            }
            if(dx == 2)
            {
                ShowColandRow(140);
                setLastSign(140);
            }
//            dy = 12;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(12,false);
//            ui->tableWidget->setColumnHidden(13,false);
//            ui->tableWidget->setColumnHidden(14,false);
//            ui->tableWidget->setColumnHidden(15,false);
// 1
//            ui->tableWidget->setColumnHidden(76,false);
//            ui->tableWidget->setColumnHidden(77,false);
//            ui->tableWidget->setColumnHidden(78,false);
//            ui->tableWidget->setColumnHidden(79,false);
// 2
//            ui->tableWidget->setColumnHidden(140,false);
//            ui->tableWidget->setColumnHidden(141,false);
//            ui->tableWidget->setColumnHidden(142,false);
//            ui->tableWidget->setColumnHidden(143,false);
        };
        break;
    case 45: //60-70
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(48);
                setLastSign(48);
            }
            if(dx == 1)
            {
                ShowColandRow(112);
                setLastSign(112);
            }
            if(dx == 2)
            {
                ShowColandRow(176);
                setLastSign(176);
            }
//            dy = 3;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(48,false);
//            ui->tableWidget->setColumnHidden(49,false);
//            ui->tableWidget->setColumnHidden(50,false);
//            ui->tableWidget->setColumnHidden(51,false);
// 1
//            ui->tableWidget->setColumnHidden(112,false);
//            ui->tableWidget->setColumnHidden(113,false);
//            ui->tableWidget->setColumnHidden(114,false);
//            ui->tableWidget->setColumnHidden(115,false);
// 2
//            ui->tableWidget->setColumnHidden(176,false);
//            ui->tableWidget->setColumnHidden(177,false);
//            ui->tableWidget->setColumnHidden(178,false);
//            ui->tableWidget->setColumnHidden(179,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(16);
                setLastSign(16);
            }
            if(dx == 1)
            {
                ShowColandRow(80);
                setLastSign(80);
            }
            if(dx == 2)
            {
                ShowColandRow(144);
                setLastSign(144);
            }
//            dy = 11;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(16,false);
//            ui->tableWidget->setColumnHidden(17,false);
//            ui->tableWidget->setColumnHidden(18,false);
//            ui->tableWidget->setColumnHidden(19,false);
// 1
//            ui->tableWidget->setColumnHidden(80,false);
//            ui->tableWidget->setColumnHidden(81,false);
//            ui->tableWidget->setColumnHidden(82,false);
//            ui->tableWidget->setColumnHidden(83,false);
// 2
//            ui->tableWidget->setColumnHidden(144,false);
//            ui->tableWidget->setColumnHidden(145,false);
//            ui->tableWidget->setColumnHidden(146,false);
//            ui->tableWidget->setColumnHidden(147,false);
        }
        break;
    case 55: //50-60
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(52);
                setLastSign(52);
            }
            if(dx == 1)
            {
                ShowColandRow(116);
                setLastSign(116);
            }
            if(dx == 2)
            {
                ShowColandRow(180);
                setLastSign(180);
            }
//            dy = 2;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(52,false);
//            ui->tableWidget->setColumnHidden(53,false);
//            ui->tableWidget->setColumnHidden(54,false);
//            ui->tableWidget->setColumnHidden(55,false);
// 1
//            ui->tableWidget->setColumnHidden(116,false);
//            ui->tableWidget->setColumnHidden(117,false);
//            ui->tableWidget->setColumnHidden(118,false);
//            ui->tableWidget->setColumnHidden(119,false);
// 2
//            ui->tableWidget->setColumnHidden(180,false);
//            ui->tableWidget->setColumnHidden(181,false);
//            ui->tableWidget->setColumnHidden(182,false);
//            ui->tableWidget->setColumnHidden(183,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(20);
                setLastSign(20);
            }
            if(dx == 1)
            {
                ShowColandRow(84);
                setLastSign(84);
            }
            if(dx == 2)
            {
                ShowColandRow(148);
                setLastSign(148);
            }
//            dy = 10;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//    ui->tableWidget->setColumnHidden(20,false);
//    ui->tableWidget->setColumnHidden(21,false);
//    ui->tableWidget->setColumnHidden(22,false);
//    ui->tableWidget->setColumnHidden(23,false);
// 1
//            ui->tableWidget->setColumnHidden(84,false);
//            ui->tableWidget->setColumnHidden(85,false);
//            ui->tableWidget->setColumnHidden(86,false);
//            ui->tableWidget->setColumnHidden(87,false);
// 2
//            ui->tableWidget->setColumnHidden(148,false);
//            ui->tableWidget->setColumnHidden(149,false);
//            ui->tableWidget->setColumnHidden(150,false);
//            ui->tableWidget->setColumnHidden(151,false);
        }
        break;
    case 65: //40-50
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(56);
                setLastSign(56);
            }
            if(dx == 1)
            {
                ShowColandRow(120);
                setLastSign(120);
            }
            if(dx == 2)
            {
                ShowColandRow(184);
                setLastSign(184);
            }
//            dy = 1;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(56,false);
//            ui->tableWidget->setColumnHidden(57,false);
//            ui->tableWidget->setColumnHidden(58,false);
//            ui->tableWidget->setColumnHidden(59,false);
// 1
//            ui->tableWidget->setColumnHidden(120,false);
//            ui->tableWidget->setColumnHidden(121,false);
//            ui->tableWidget->setColumnHidden(122,false);
//            ui->tableWidget->setColumnHidden(123,false);
// 2
//            ui->tableWidget->setColumnHidden(184,false);
//            ui->tableWidget->setColumnHidden(185,false);
//            ui->tableWidget->setColumnHidden(186,false);
//            ui->tableWidget->setColumnHidden(187,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(24);
                setLastSign(24);
            }
            if(dx == 1)
            {
                ShowColandRow(88);
                setLastSign(88);
            }
            if(dx == 2)
            {
                ShowColandRow(152);
                setLastSign(152);
            }
//            dy = 9;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(24,false);
//            ui->tableWidget->setColumnHidden(25,false);
//            ui->tableWidget->setColumnHidden(26,false);
//            ui->tableWidget->setColumnHidden(27,false);
// 1
//            ui->tableWidget->setColumnHidden(88,false);
//            ui->tableWidget->setColumnHidden(89,false);
//            ui->tableWidget->setColumnHidden(90,false);
//            ui->tableWidget->setColumnHidden(91,false);
// 2
//            ui->tableWidget->setColumnHidden(152,false);
//            ui->tableWidget->setColumnHidden(153,false);
//            ui->tableWidget->setColumnHidden(154,false);
//            ui->tableWidget->setColumnHidden(155,false);
        }
        break;
    case 75: //30-40
        if(dY > 0)
        {
            if(dx == 0)
            {
                ShowColandRow(60);
                setLastSign(60);
            }
            if(dx == 1)
            {
                ShowColandRow(124);
                setLastSign(124);
            }
            if(dx == 2)
            {
                ShowColandRow(188);
                setLastSign(188);
            }
//            dy = 0;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            ui->tableWidget->setColumnHidden(60,false);
//            ui->tableWidget->setColumnHidden(61,false);
//            ui->tableWidget->setColumnHidden(62,false);
//            ui->tableWidget->setColumnHidden(63,false);
// 1
//            ui->tableWidget->setColumnHidden(124,false);
//            ui->tableWidget->setColumnHidden(125,false);
//            ui->tableWidget->setColumnHidden(126,false);
//            ui->tableWidget->setColumnHidden(127,false);
// 2
//            ui->tableWidget->setColumnHidden(188,false);
//            ui->tableWidget->setColumnHidden(189,false);
//            ui->tableWidget->setColumnHidden(190,false);
//            ui->tableWidget->setColumnHidden(191,false);
        }
        else
        {
            if(dx == 0)
            {
                ShowColandRow(28);
                setLastSign(28);
            }
            if(dx == 1)
            {
                ShowColandRow(92);
                setLastSign(92);
            }
            if(dx == 2)
            {
                ShowColandRow(156);
                setLastSign(156);
            }
//            dy = 8;
//            qDebug() << "сколько есть сигналов: " << getTable(dx,dy).size();
//            0
//            ui->tableWidget->setColumnHidden(28,false);
//            ui->tableWidget->setColumnHidden(29,false);
//            ui->tableWidget->setColumnHidden(30,false);
//            ui->tableWidget->setColumnHidden(31,false);
//             1
//            ui->tableWidget->setColumnHidden(92,false);
//            ui->tableWidget->setColumnHidden(93,false);
//            ui->tableWidget->setColumnHidden(94,false);
//            ui->tableWidget->setColumnHidden(95,false);
//              2
//            ui->tableWidget->setColumnHidden(156,false);
//            ui->tableWidget->setColumnHidden(157,false);
//            ui->tableWidget->setColumnHidden(158,false);
//            ui->tableWidget->setColumnHidden(159,false);
        }
        break;
    default:
        break;
    }

    //ui->widget->layer("overlay")->setVisible(true);

    //m_ItemText->setText(QString("Point Information\nX = %1\nY = %2").arg(QString::number(dX)).arg(QString::number(dY)));

    ui->widget->replot();


}

void Tsap::Slot_addData()
{
    ui->widget->replot();
}

void Tsap::slot_addingSignalsToPlot(QVector<_SignalParam_formular> Targets)
{
    for(int i = 0; i < 3; ++i)
    {
        ui->widget->graph(i)->data().data()->clear();
    }
       // ui->widget->replot();
    eraseTargetTable();
    //ui->tableWidget->clear();

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
                    setTable(0,8,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 75);
                    setTable(1,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -75);
                    setTable(1,8,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 75);
                    setTable(2,0,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -75);
                    setTable(2,8,Targets[i]);
                }
            }
            break;
        case 1:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 65);
                    setTable(0,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -65);
                    setTable(0,9,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 65);
                    setTable(1,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -65);
                    setTable(1,9,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 65);
                    setTable(2,1,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -65);
                    setTable(2,9,Targets[i]);
                }
            }
            break;
        case 2:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 55);
                    setTable(0,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -55);
                    setTable(0,10,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 55);
                    setTable(1,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -55);
                    setTable(1,10,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 55);
                    setTable(2,2,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -55);
                    setTable(2,10,Targets[i]);
                }
            }
            break;
        case 3:
            if(Targets[i].W9.TipPomehi >= 12 || Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 45);
                    setTable(0,3,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -45);
                    setTable(0,11,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 45);
                    setTable(1,3,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -45);
                    setTable(1,11,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 45);
                    setTable(2,3,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -45);
                    setTable(2,11,Targets[i]);
                }
            }
            break;
        case 4:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 35);
                    setTable(0,4,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -35);
                    setTable(0,12,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 35);
                    setTable(1,4,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -35);
                    setTable(1,12,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 35);
                    setTable(2,4,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -35);
                    setTable(2,12,Targets[i]);
                }
            }
            break;
        case 5:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 25);
                    setTable(0,5,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -25);
                    setTable(0,13,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 25);
                    setTable(1,5,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -25);
                    setTable(1,13,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 25);
                    setTable(2,5,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -25);
                    setTable(2,13,Targets[i]);
                }
            }
            break;
        case 6:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 15);
                    setTable(0,6,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -15);
                    setTable(0,14,Targets[i]);
                }
            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 15);
                    setTable(1,6,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -15);
                    setTable(1,14,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 15);
                    setTable(2,6,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -15);
                    setTable(2,14,Targets[i]);
                }
            }
            break;
        case 7:
            if(Targets[i].W9.TipPomehi >= 12 && Targets[i].W9.TipPomehi <= 14)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(0)->addData(kni, 5);
                    setTable(0,7,Targets[i]);
                }
                else
                {
                    ui->widget->graph(0)->addData(kni, -5);
                    setTable(0,15,Targets[i]);
                }

            }
            else if(Targets[i].W9.TipPomehi == 7)
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(1)->addData(is, 5);
                    setTable(1,7,Targets[i]);
                }
                else
                {
                    ui->widget->graph(1)->addData(is, -5);
                    setTable(1,15,Targets[i]);
                }
            }
            else
            {
                if(!Targets[i].W2.semisphere)
                {
                    ui->widget->graph(2)->addData(other, 5);
                    setTable(2,7,Targets[i]);
                }
                else
                {
                    ui->widget->graph(2)->addData(other, -5);
                    setTable(2,15,Targets[i]);
                }
            }
            break;
        default:
            break;
        }
    }
    ui->widget->replot();
    setCellTable();
    ui->tableWidget->update();
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
    return Table[row][col].TargetsTable;
}

void Tsap::eraseTargetTable()
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            Table[i][j].TargetsTable.clear();
        }
    }
}

void Tsap::setCellTable()
{
    int setCol = 0, setMaxCol = 0;
    int setRow = 0;
    for(int col = 0; col < 3; ++col)
    {
        if(col == 0)
        {
            setMaxCol = 0; // 64
        }
        if(col == 1)
        {
            setMaxCol = 64; //128
        }
        if(col == 2)
        {
            setMaxCol = 128; //192
        }
        for(int row = 15; row >= 0; --row, setMaxCol += 4) //дальше нужно понять как заполнить от 100+ к 30 или наоборот
        {
            setCol = setMaxCol + 1;
            if(getTable(col,row).size())
            {
                qDebug() << "зашли сюда " ;
                for(int i = 0, setRow = 0; i < getTable(col,row).size(); ++i)
                {
                    QTableWidgetItem *itemCer = new QTableWidgetItem;
                    QTableWidgetItem *itemDlt = new QTableWidgetItem;
                    QTableWidgetItem *itemPer = new QTableWidgetItem;

                    itemCer->setText(QString::number(getTable(col,row)[i].Carrier));
                    ui->tableWidget->setItem(setRow + 0,setCol,itemCer);

                    itemDlt->setText(QString::number(getTable(col,row)[i].Dlit));
                    ui->tableWidget->setItem(setRow + 1,setCol,itemDlt);

                    itemPer->setText(QString::number(getTable(col,row)[i].Per));
                    ui->tableWidget->setItem(setRow + 2,setCol,itemPer);

                    if(setCol - 3 != setMaxCol)
                    {
                        setCol += 2;
                    }
                    else
                    {
                        setCol -= 2;
                        setRow += 3;
                    }
                    if(setRow >= 18) break;
                }
            }
        }
    }

}

void Tsap::HidenColandRow(int col, bool local) //локальное или глобальное закрытие всего
{
    if(local)
    {
        for(int wCol = 0; wCol < 192; wCol += 2)
        {
            if(!ui->tableWidget->isColumnHidden(wCol))
            {
                ui->tableWidget->setColumnHidden(wCol,true);
                ui->tableWidget->setColumnHidden(wCol-1,true);
                ui->tableWidget->setColumnHidden(191,true);

                for(int wRow = 0; wRow < 18; wRow ++)
                {
                    if(!ui->tableWidget->isRowHidden(wRow))
                    {
                        ui->tableWidget->setRowHidden(wRow, true);
                    }
                }
            }
        }
    }
    else
    {
        for(int tempcol = col; tempcol < col + 4; ++tempcol)
        {
            ui->tableWidget->setColumnHidden(tempcol,true);
            for(int wRow = 0; wRow < 18; wRow ++)
            {
                if(!ui->tableWidget->isRowHidden(wRow))
                {
                    ui->tableWidget->setRowHidden(wRow, true);
                }
            }
        }
    }

}

void Tsap::ShowColandRow(int startCol)
{

        for(int tempcol = startCol; tempcol < startCol + 4; ++tempcol)
        {
            ui->tableWidget->setColumnHidden(tempcol,false); //проверяем схлопнута ли ячейка
            for(int wRow = 0; wRow < 18; wRow ++)
            {
                if(ui->tableWidget->isRowHidden(wRow)) //проверяем схлопнута ли ячейка (излишняя проверка честно говоря)
                {
                    if(ui->tableWidget->item(wRow,tempcol)) //проверяем есть ли там данные
                        ui->tableWidget->setRowHidden(wRow, false);
                }
            }
        }
}

void Tsap::setLastSign(int value)
{
    LastSigShow = value;
}

int Tsap::getLastSign()
{
    return LastSigShow;
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
