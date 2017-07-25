#include "klinegrid.h"
#include "datafile.h"
#include "stockgrid.h"
#include <QPen>
#include <QPainter>
#include <QString>
#include <QVector>
#include <QPoint>
#include <QTextCodec>

#include "mainwindow.h"

KLineGrid::KLineGrid(QWidget* parent) : StockGrid(parent)
{
    pdetail = new KLineDetail(this);
    pdetail->setGeometry(80,60,75,500);
    pdetail->move(-10,20);
    pdetail->show();
}


void KLineGrid::initial()
{
    StockGrid::initial();
    getSelfIndicator();
}

void KLineGrid::drawLine()
{
    //画的k线所需的参数  最高价 最低价
    getSelfIndicator();

    //画y轴坐标轴
    drawYtick();

    //画k线
    drawKLine();
}


void KLineGrid::paintEvent(QPaintEvent* event)
{
    StockGrid::paintEvent(event);
    drawLine();
    drawAverageLine(5);
    drawAverageLine(10);
    drawAverageLine(20);
    drawAverageLine(30);
    drawAverageLine(60);
    drawInformation();
}

void KLineGrid::keyPressEvent(QKeyEvent* event)
{
    StockGrid::keyPressEvent(event);
    update();
}

void KLineGrid::getSelfIndicator()
{
    auto pData = getPData();
    if( nullptr == pData)
        return;

    highestBid = 0;
    lowestBid = 1000;


    for( int i= getStartIndex();i< getEndIndex();++i)
    {

		int j = getStartIndex();
        if(pData->kline[i].highestBid > highestBid)
            highestBid = pData->kline[i].highestBid;

        if(pData->kline[i].lowestBid < lowestBid)
            lowestBid = pData->kline[i].lowestBid;
    }
    pData = nullptr;
}

void KLineGrid::drawYtick()
{

    StockGrid::drawYtick(lowestBid,highestBid);

}

void KLineGrid::drawKLine()
{



    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);


    //y轴缩放
    double yscale = getGridHeight() / (highestBid -lowestBid ) ;
    //x轴步进
    double xstep =  getGridWidth() / getTotalIndex();

    //画线用到的点
    QPoint p1;
    QPoint p2;
    QPoint p3;
    QPoint p4;


    auto pData = getPData();

    for( int i = getStartIndex()+1;i< getEndIndex()+1;++i )
    {
		int a = getStartIndex();
		int b = getEndIndex();

        if( pData->kline[i].openingPrice > pData->kline[i].closeingPrice )
            pen.setColor(QColor(85,252,252));
        else if( pData->kline[i].openingPrice < pData->kline[i].closeingPrice)
            pen.setColor(Qt::red);
        else if( pData->kline[i].openingPrice == pData->kline[i].closeingPrice)
        {
            if( i -1 <0)
                pen.setColor(Qt::red);
            else if( pData->kline[i].openingPrice > pData->kline[i -1 ].closeingPrice)
                pen.setColor(Qt::red);
            else if( pData->kline[i].openingPrice <pData->kline[i -1 ].closeingPrice)
                pen.setColor(QColor(85,252,252));
        }


        lineWidth = getGridWidth() / getTotalIndex();

        //为了各个k线之间不贴在一起，设置一个间隔
        lineWidth = lineWidth - 0.2*lineWidth;

        //最小线宽为3
        if( lineWidth < 3)
            lineWidth = 3;


        //阴线
         if( pData->kline[i].openingPrice > pData->kline[i].closeingPrice )
        {
             //画开盘与收盘之间的粗实线
             pen.setWidth(lineWidth);
             painter.setPen(pen);
             p1.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p1.setY( getWidgetHeight() - (pData->kline[i].openingPrice - lowestBid) *yscale - getMarginBottom());
             p2.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p2.setY( getWidgetHeight() - (pData->kline[i].closeingPrice - lowestBid) *yscale - getMarginBottom() - 0.5*lineWidth);
             painter.drawLine(p1,p2);


             //画最高价与最低价之间的细线
             pen.setWidth(1);
             painter.setPen(pen);
             p1.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p1.setY( getWidgetHeight() - (pData->kline[i].highestBid - lowestBid) *yscale - getMarginBottom());
             p2.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p2.setY( getWidgetHeight() - (pData->kline[i].lowestBid - lowestBid) *yscale - getMarginBottom());
             painter.drawLine(p1,p2);
        }

         //阳线
         else
         {
             pen.setWidth(1);
             painter.setPen(pen);


             p1.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)));
             p1.setY( getWidgetHeight() - (pData->kline[i].openingPrice - lowestBid) *yscale - getMarginBottom());

             p2.setX( getMarginLeft() + xstep *(i - (getStartIndex() + 1)) + lineWidth);
             p2.setY( getWidgetHeight() - (pData->kline[i].openingPrice - lowestBid) *yscale - getMarginBottom());


             p3.setX( getMarginLeft() + xstep *(i - (getStartIndex() + 1)));
             p3.setY( getWidgetHeight() - (pData->kline[i].closeingPrice - lowestBid) *yscale - getMarginBottom());

             p4.setX( getMarginLeft() + xstep *(i - (getStartIndex() + 1)) + lineWidth);
             p4.setY( getWidgetHeight() - (pData->kline[i].closeingPrice - lowestBid) *yscale - getMarginBottom());

             painter.drawLine(p1,p2);
             painter.drawLine(p1,p3);
             painter.drawLine(p2,p4);
             painter.drawLine(p3,p4);


             //画最高价与最低价之间的细线
             pen.setWidth(1);
             painter.setPen(pen);
             p1.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p1.setY( getWidgetHeight() - (pData->kline[i].highestBid - lowestBid) *yscale - getMarginBottom());


             double y1,y2;
             if( pData->kline[i].openingPrice > pData->kline[i].closeingPrice )
             {
                 y1 = pData->kline[i].openingPrice;
                 y2 = pData->kline[i].closeingPrice;
             }
             else
             {
                 y1 = pData->kline[i].closeingPrice;
                 y2 = pData->kline[i].openingPrice;
             }

             p2.setX( getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p2.setY( getWidgetHeight() - (y1 - lowestBid) *yscale - getMarginBottom());
             p3.setX(getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p3.setY( getWidgetHeight() - (y2 - lowestBid) *yscale - getMarginBottom());
             p4.setX(getMarginLeft() + xstep *(i - (getStartIndex()+1)) + 0.5*lineWidth);
             p4.setY(getWidgetHeight() - (pData->kline[i].lowestBid - lowestBid) *yscale - getMarginBottom());

             painter.drawLine(p1,p2);
             painter.drawLine(p3,p4);
         }
    }
    pData = nullptr;


}

void KLineGrid::drawAverageLine(int day)
{
    //y轴缩放
    double yscale = getGridHeight() / (highestBid -lowestBid ) ;

    //画线要连接的点
    QVector<QPoint> point;

    //临时点
    QPoint temp;

    //x轴步进
    double xstep = getGridWidth() / getTotalIndex();



    auto pData = getPData();


    switch(day)
    {
    case 5:
        for( int i= getStartIndex();i<getEndIndex();++i)
        {
            if( pData->kline[i].averageLine5 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (pData->kline[i].averageLine5 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 10:
        for( int i= getStartIndex();i<getEndIndex();++i)
        {
            if( pData->kline[i].averageLine10 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (pData->kline[i].averageLine10 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 20:
        for( int i= getStartIndex();i<getEndIndex();++i)
        {
            if( pData->kline[i].averageLine20 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (pData->kline[i].averageLine20 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 30:
        for( int i= getStartIndex();i<getEndIndex();++i)
        {
            if( pData->kline[i].averageLine30 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (pData->kline[i].averageLine30 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 60:
        for( int i= getStartIndex();i<getEndIndex();++i)
        {
            if( pData->kline[i].averageLine60 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (pData->kline[i].averageLine60 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    default:
        break;
    }


    QPainter painter(this);
    QPen     pen;

    switch(day)
    {
    case 5:
        pen.setColor(Qt::white);
        break;
    case 10:
        pen.setColor(Qt::yellow);
        break;
    case 20:
        pen.setColor(Qt::magenta);
        break;
    case 30:
        pen.setColor(Qt::green);
        break;
    case 60:
        pen.setColor(Qt::cyan);
        break;
    default:
        pen.setColor(Qt::white);
        break;
    }
    painter.setPen(pen);
    QPolygon polykline(point);
    painter.drawPolyline(polykline);

    pData = nullptr;
}



void KLineGrid::drawInformation()
{
    auto pData = getPData();
    if( nullptr == pData)
        return;

    QPainter painter(this);
    QPen     pen;

    QFont ft;
    ft.setPointSize(10);
    painter.setFont(ft);
    pen.setColor(Qt::white);
    painter.setPen(pen);



    QString str;
    int informatonWidth  = 150;
    int informatonHeight = 30;


   
	QRect rectText(getMarginLeft(), 5, informatonWidth, informatonHeight);
	painter.drawText(rectText,stockName + " MA5:" +
	                 str.sprintf("%.2f",pData->kline[getCurrentIndex()].averageLine5));
   // painter.drawText(rectText,QString::fromLocal8Bit("上海科技 MA5:") +
     //                str.sprintf("%.2f",pData->kline[getCurrentIndex()].averageLine5));


    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    QRect rectText2(getMarginLeft()+informatonWidth,5,informatonWidth,informatonHeight);
    painter.drawText(rectText2,QString::fromLocal8Bit("MA10:") +
                     str.sprintf("%.2f",pData->kline[getCurrentIndex()].averageLine10));


    pen.setColor(Qt::magenta);
    painter.setPen(pen);
    QRect rectText3(getMarginLeft()+informatonWidth+100,5,informatonWidth,informatonHeight);
    painter.drawText(rectText3,QString::fromLocal8Bit("MA20:") +
                     str.sprintf("%.2f",pData->kline[getCurrentIndex()].averageLine20));

    pen.setColor(Qt::green);
    painter.setPen(pen);
    QRect rectText4(getMarginLeft()+informatonWidth+200,5,informatonWidth,informatonHeight);
    painter.drawText(rectText4,QString::fromLocal8Bit("MA30:") +
                     str.sprintf("%.2f",pData->kline[getCurrentIndex()].averageLine30));

    pen.setColor(Qt::cyan);
    painter.setPen(pen);
    QRect rectText5(getMarginLeft()+informatonWidth+300,5,informatonWidth,informatonHeight);
    painter.drawText(rectText5,QString::fromLocal8Bit("MA60:") +
                     str.sprintf("%.2f",pData->kline[getCurrentIndex()].averageLine60));
}


void KLineGrid::drawCrossLine(double begin  , double end)
{
    StockGrid::drawCrossLine(lowestBid , highestBid);
}

void KLineGrid::drawCorssVerLine()
{
    StockGrid::drawCorssVerLine();
}

void KLineGrid::drawCorssHorLine()
{
    StockGrid::drawCorssHorLine();
}

void KLineGrid::drawTips(double begin , double end)
{
    StockGrid::drawTips(begin , end);
}



void KLineGrid::drawCrossLineKeyDown(double begin  , double end )
{
    StockGrid::drawCrossLineKeyDown(begin,end);
}

void KLineGrid::drawCorssVerLineKeyDown()
{
    StockGrid::drawCorssVerLineKeyDown();
}

void KLineGrid::drawCorssHorLineKeyDown(double start , double end,int types )
{
    StockGrid::drawCorssHorLineKeyDown(lowestBid , highestBid ,0);
}

void KLineGrid::drawTipsKeyDown(double begin  , double end  ,int types)
{
    StockGrid::drawTipsKeyDown(lowestBid,highestBid,0);


    auto pData = getPData();



    int currentDay = ( getMousePoint().x() - getMarginLeft() ) * getTotalIndex() / getGridWidth() + getStartIndex();
	

    if( currentDay ==0)
        return;

    QColor openingColor = pData->kline[currentDay+1].openingPrice > pData->kline[currentDay].closeingPrice ?
                          QColor("#FF0000"):QColor("#00FF00");

    QColor highestColor = pData->kline[currentDay+1].highestBid > pData->kline[currentDay].closeingPrice ?
                QColor("#FF0000"):QColor("#00FF00");

    QColor lowestColor = pData->kline[currentDay+1].lowestBid > pData->kline[currentDay].closeingPrice ?
                QColor("#FF0000"):QColor("#00FF00");


    QColor closeingColor = pData->kline[currentDay+1].closeingPrice > pData->kline[currentDay+1].openingPrice ?
                QColor("#FF0000"):QColor("#00FF00");


    QColor amountOfIncreaseColor = pData->kline[currentDay+1].amountOfIncrease > 0 ?
                QColor("#FF0000"):QColor("#00FF00");
	

    pdetail->receiveParams(
                             pData->kline[currentDay + 1].time,QColor("#FFFFFF"),
                             pData->kline[currentDay + 1].closeingPrice,QColor("#FF0000"),
                             pData->kline[currentDay + 1].openingPrice,openingColor,
                             pData->kline[currentDay + 1].highestBid,highestColor,
                             pData->kline[currentDay + 1].lowestBid,lowestColor,
                             pData->kline[currentDay + 1].closeingPrice,closeingColor,
                             pData->kline[currentDay + 1].amountOfIncrease,amountOfIncreaseColor,
                             pData->kline[currentDay + 1].amountOfAmplitude,QColor("#02E2F4"),
                             pData->kline[currentDay + 1].ftotalVolume,QColor("#02E2F4"),
                             pData->kline[currentDay + 1].totalAmount,QColor("#02E2F4"),
                             pData->kline[currentDay + 1].turnoverRate,QColor("#02E2F4")
                          );

    update();
}


