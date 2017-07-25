#include "stockgrid.h"
#include "autogrid.h"
#include <QWidget>
#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QKeyEvent>
#include <QFont>
#include <QMessageBox>
#include "DataFile.h"


StockGrid::StockGrid(QWidget* parent) : AutoGrid(parent)
{


    QFont ft;
    ft.setPointSize(10);
    this->setFont(ft);

    //开启鼠标追踪
    setMouseTracking(true);
}



void StockGrid::paintEvent(QPaintEvent* event)
{
    AutoGrid::paintEvent(event);

    if(!isKeyDown && bCross )
        drawCrossLine();

    if( isKeyDown && bCross)
        drawCrossLineKeyDown();

}

void StockGrid::resizeEvent(QResizeEvent* event)
{
    AutoGrid::resizeEvent(event);
}

void StockGrid::keyPressEvent(QKeyEvent* event)
{
    pSubscribe->Notify_keyPressEvent(event);
}

void StockGrid::mouseMoveEvent(QMouseEvent* event)
{
    pSubscribe->Notify_mouseMoveEvent(event);
}

void StockGrid::mousePressEvent(QMouseEvent* event)
{
    pSubscribe->Notify_mousePressEvent(event);
}

void StockGrid::keyPressEvent2(QKeyEvent* event)
{
    if( mousePoint.x() > getMarginLeft()+ getGridWidth() )
        return;
    if( mousePoint.x() < getMarginLeft() )
        return;

    isKeyDown = true;
    currentIndex = (double)( mousePoint.x() - getMarginLeft() ) /
                   (getGridWidth()) * totalIndex + startIndex;


    switch(event->key())
    {

    case Qt::Key_Left:
    {
        double xstep = getGridWidth() / totalIndex ;
        currentIndex--;

        if( mousePoint.x() - xstep < getMarginLeft())
        {
            if( startIndex -1 < 0)
                return;
            endIndex -= 1;
            startIndex -= 1;
        }
        else
        {
            mousePoint.setX(mousePoint.x() - xstep);
        }


        update();
        break;
    }


    case Qt::Key_Right:
    {
        double xstep = getGridWidth() / totalIndex ;


		if (currentIndex + 1 >= pData->kline.size() - 1)
			return;
        currentIndex++;

		if (mousePoint.x() + xstep > getWidgetWidth() - getMarginRight())
		{
			if (endIndex + 1 > pData->kline.size() - 1)
				return;
			endIndex += 1;
			startIndex += 1;
		}
		else
            mousePoint.setX(mousePoint.x() + xstep);
        update();
        break;
    }

    case Qt::Key_Up:
    {
        totalIndex = totalIndex /2;

        //最少显示10个
        if( totalIndex < 10)
        {
            totalIndex *= 2;
            return;
        }


        endIndex = currentIndex + totalIndex/2;
        startIndex = currentIndex - totalIndex/2;

        if( endIndex > pData->kline.size() -1)
        {
            endIndex = pData->kline.size() -1;
            startIndex = endIndex - totalIndex;
        }

        if(startIndex < 0 )
        {
            startIndex = 0;
            endIndex = startIndex + totalIndex;
        }
        update();
        break;
    }


    case Qt::Key_Down:
    {
        if(totalIndex == pData->kline.size() -1 )
            return;

        totalIndex = totalIndex * 2;
        if( totalIndex > pData->kline.size() -1)
        {
            totalIndex = pData->kline.size() -1;
        }
        endIndex = currentIndex + totalIndex/2;
        if( endIndex > pData->kline.size() -1)
        {
            endIndex = pData->kline.size() -1;
        }

        startIndex = currentIndex - totalIndex/2;
        if( startIndex < 0)
            startIndex = 0;

        totalIndex = endIndex - startIndex;

        update();
        break;

    }
    default:
        break;
    }
}

void StockGrid::mouseMoveEvent2(QMouseEvent* event)
{
    mousePoint = event->pos();
    isKeyDown = false;
    update();
}

void StockGrid::mousePressEvent2(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        bCross = !bCross;
        update();
    }
}


void StockGrid::initial()
{
    if( nullptr == getPData())
        return;

    endIndex = pData->kline.size() - 1 ;
    totalIndex = 200;
    startIndex = endIndex - totalIndex;
    currentIndex = startIndex + totalIndex / 2;

    if( startIndex < 0)
    {
        startIndex = 0;
        totalIndex = pData->kline.size();
        currentIndex = totalIndex / 2;
    }
}

void StockGrid::setData(DataFile* pData)
{
    this->pData = pData;
}


void StockGrid::drawLine()
{

}



void StockGrid::drawXtick()
{

}

void StockGrid::drawYtick(double begin, double  end )
{
    QPainter painter(this);
    QPen     pen;    
    pen.setColor(Qt::red);
    painter.setPen(pen);


    //y轴显示步进
    double ystep = (end - begin)/ getHGridNum();


    QString str;
    if( 0 == getHGridNum() )
    {
        str.sprintf("%.2f",begin);
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 5,
                                  getWidgetHeight() - getMarginBottom() ),
                          str);
        str.sprintf("%.2f",end);
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 5,
                                  getMarginTop() ),
                          str);
        return;
    }

    for( int i=0;i<=getHGridNum();++i)
    {
        str.sprintf("%.2f",begin+ i*ystep);
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 5,
                                  getWidgetHeight() - getMarginBottom() - i*getAtomGridHeight()),
                          str);
    }
}



void StockGrid::getSelfIndicator()
{

}



void StockGrid::drawCrossLine(double begin ,double end)
{
    drawCorssVerLine();
    drawCorssHorLine();
    drawTips(begin , end);
}

void StockGrid::drawCorssVerLine()
{
    if(mousePoint.x() < getMarginLeft() || mousePoint.x() > getWidgetWidth() - getMarginRight())
        return;

    if(mousePoint.y() < getMarginTop() || mousePoint.y() > getWidgetHeight() - getMarginBottom())
        return;

    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(mousePoint.x(),getMarginTop(),
                     mousePoint.x(),getWidgetHeight() - getMarginBottom());
}

void StockGrid::drawCorssHorLine()
{
    if(mousePoint.x() < getMarginLeft() || mousePoint.x() > getWidgetWidth() - getMarginRight())
        return;

    if(mousePoint.y() < getMarginTop() || mousePoint.y() > getWidgetHeight() - getMarginBottom())
        return;

    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawLine(getMarginLeft(),mousePoint.y(),
                     getWidgetWidth()-getMarginRight(),mousePoint.y());
}

void StockGrid::drawTips(double begin , double end )
{


    if(mousePoint.x() < getMarginLeft() || mousePoint.x() > getWidgetWidth() - getMarginRight())
        return;

    if(mousePoint.y() < getMarginTop() || mousePoint.y() > getWidgetHeight() - getMarginBottom())
        return;


    QPainter painter(this);
    QPen     pen;
    QBrush brush(QColor(64,0,128));
    painter.setBrush(brush);
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);



    double yscale = getGridHeight() / (end -begin ) ;
    double yval =  end - ( mousePoint.y() - getMarginTop() ) / yscale;
    double yPos = mousePoint.y();

    int iTipsWidth = 70;
    int iTipsHeight = 20;

    QString str;

    QRect rect( getWidgetWidth() - getMarginRight(),
                yPos - iTipsHeight/2,iTipsWidth,iTipsHeight);
    painter.drawRect(rect);


    QRect rectText( getWidgetWidth() - getMarginRight() + 2,
                yPos - iTipsHeight/4,iTipsWidth,iTipsHeight);
    painter.drawText(rectText, str.sprintf("%.2f",yval));


}



void StockGrid::drawCrossLineKeyDown(double begin , double end)
{
    drawCorssVerLineKeyDown();
    drawCorssHorLineKeyDown();
    drawTipsKeyDown(begin,end);
}

void StockGrid::drawCorssVerLineKeyDown()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);

    double xstep = getGridWidth() / totalIndex ;
    double xPos = getMarginLeft() ;
    while( mousePoint.x() - xPos > xstep )
    {
        xPos += xstep;
    }
    double lineWidth = xstep - 0.2* xstep ;
    if( lineWidth < 3)
        lineWidth = 3;

    xPos += 0.5*lineWidth;
    QLine horline(xPos,getMarginTop(),xPos,getWidgetHeight() - getMarginBottom());
    painter.drawLine(horline);
}

void StockGrid::drawCorssHorLineKeyDown(double start , double end,int types)
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);


    double yPos;
    currentIndex = ( mousePoint.x() - getMarginLeft() ) * totalIndex / getGridWidth() + startIndex;


    double yscale = getGridHeight() / (end -start );

    switch(types)
    {
    case 0:
        yPos = ( pData->kline[currentIndex+1].closeingPrice -  start) *yscale;
        break;
    case 1:
        yPos = ( pData->kline[currentIndex+1].ftotalVolume /100 - start) *yscale;
        break;
    }

    QLine verline ( getMarginLeft(),getWidgetHeight()-getMarginBottom()-yPos,
                    getWidgetWidth()-getMarginRight(),getWidgetHeight()-getMarginBottom()-yPos);
    painter.drawLine(verline);

}

void StockGrid::drawTipsKeyDown(double start , double end ,int types)
{
    QPainter painter(this);
    QPen     pen;
    QBrush brush(QColor(64,0,128));
    painter.setBrush(brush);
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);

    currentIndex = ( mousePoint.x() - getMarginLeft() ) * totalIndex / getGridWidth() + startIndex;

    double yval;
    switch(types)
    {
    case 0:
        yval = pData->kline[currentIndex+1].closeingPrice;
        break;
    case 1:
        yval = pData->kline[currentIndex+1].ftotalVolume /100;
        break;
    }

    double yscale = getGridHeight() / (end -start );
    double yPos=  ( yval - start ) * yscale ;

    yPos = getWidgetHeight()-getMarginBottom()-yPos;



    int iTipsWidth = 70;
    int iTipsHeight = 20;

    QString str;

    QRect rect( getWidgetWidth() - getMarginRight(),
                yPos - iTipsHeight/2,iTipsWidth,iTipsHeight);
    painter.drawRect(rect);


    QRect rectText( getWidgetWidth() - getMarginRight() + 2,
                yPos - iTipsHeight/4,iTipsWidth,iTipsHeight);
    painter.drawText(rectText, str.sprintf("%.2f",yval));
}

StockGrid::~StockGrid()
{

}


int StockGrid::getStartIndex() const
{
    return startIndex;
}

void StockGrid::setStartIndex(int value)
{
    startIndex = value;
}

int StockGrid::getEndIndex() const
{
    return endIndex;
}

void StockGrid::setEndIndex(int value)
{
    endIndex = value;
}

int StockGrid::getCurrentIndex() const
{
    return currentIndex;
}

void StockGrid::setCurrentIndex(int value)
{
    currentIndex = value;
}

int StockGrid::getTotalIndex() const
{
    return totalIndex;
}

void StockGrid::setTotalIndex(int value)
{
    totalIndex = value;
}

int StockGrid::getLineWidth() const
{
    return lineWidth;
}

void StockGrid::setLineWidth(int value)
{
    lineWidth = value;
}

QPoint StockGrid::getMousePoint() const
{
    return mousePoint;
}

void StockGrid::setMousePoint(const QPoint &value)
{
    mousePoint = value;
}

DataFile *StockGrid::getPData() const
{
    return pData;
}

void StockGrid::setPData(DataFile *value)
{
    pData = value;
}

void StockGrid::setSubscribe(Subscribe* pSubscribe)
{
    this->pSubscribe = pSubscribe;
}
