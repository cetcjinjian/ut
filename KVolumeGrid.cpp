#include "kvolumegrid.h"
#include "datafile.h"
#include "stockgrid.h"
#include <QPen>
#include <QPainter>
#include <QString>
#include <QVector>
#include <QPoint>
#include <QFont>

KVolumeGrid::KVolumeGrid(QWidget* parent) : StockGrid(parent)
{
	//this->setAttribute(Qt::WA_TransparentForMouseEvents);

}

void KVolumeGrid::initial()
{
	StockGrid::initial();
	getSelfIndicator();
}


void KVolumeGrid::drawLine()
{
	//获取最大成交量
	getSelfIndicator();

	//画y轴坐标轴
	drawYtick();

	//画成交量的方柱线
	drawKVolume();
}


void KVolumeGrid::drawYtick()
{
	StockGrid::drawYtick(0, maxVolume);
}

void KVolumeGrid::drawKVolume()
{

	auto pData = getPData();

	QPainter painter(this);
	QPen     pen;

	double xstep = getGridWidth() / getTotalIndex();
	double yscale = getGridHeight() / maxVolume;


	//画线连接的点
	QPoint p1;
	QPoint p2;

	QPoint p3;
	QPoint p4;



	for (int i = getStartIndex(); i <= getEndIndex(); ++i)
	{
		if (pData->kline[i].openingPrice > pData->kline[i].closeingPrice)
			pen.setColor(QColor(85, 252, 252));
		else if (pData->kline[i].openingPrice < pData->kline[i].closeingPrice)
			pen.setColor(Qt::red);
		else if (pData->kline[i].openingPrice == pData->kline[i].closeingPrice)
		{
			if (i - 1 <0)
				pen.setColor(Qt::red);
			else if (pData->kline[i].openingPrice > pData->kline[i - 1].closeingPrice)
				pen.setColor(Qt::red);
			else if (pData->kline[i].openingPrice <pData->kline[i - 1].closeingPrice)
				pen.setColor(QColor(85, 252, 252));
		}

		//设置线宽
		lineWidth = getGridWidth() / getTotalIndex();

		//为了各个k线之间不贴在一起，设置一个间隔
		lineWidth = lineWidth - 0.2*lineWidth;

		//最小线宽为3
		if (lineWidth < 3)
			lineWidth = 3;

		double temp = pData->kline[i].ftotalVolume / 100;

		//阴线
		if (pen.color() == QColor(85, 252, 252))
		{
			pen.setWidth(lineWidth);
			painter.setPen(pen);
			p1.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
			p1.setY(getWidgetHeight() - temp*yscale - getMarginBottom() + 0.5*lineWidth);
			//p1.setY( getWidgetHeight() -  temp*yscale - getMarginBottom() );
			p2.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
			p2.setY(getWidgetHeight() - getMarginBottom() - 0.5*lineWidth);
			//p2.setY( getWidgetHeight()  - getMarginBottom() );
			painter.drawLine(p1, p2);

		}

		//阳线
		else
		{
			pen.setWidth(1);
			painter.setPen(pen);

			p1.setX(getMarginLeft() + xstep *(i - getStartIndex()));
			p1.setY(getWidgetHeight() - (temp)*yscale - getMarginBottom());
			p2.setX(getMarginLeft() + xstep *(i - getStartIndex()) + lineWidth);
			p2.setY(getWidgetHeight() - (temp)*yscale - getMarginBottom());
			p3.setX(getMarginLeft() + xstep *(i - getStartIndex()));
			p3.setY(getWidgetHeight() - getMarginBottom());
			p4.setX(getMarginLeft() + xstep *(i - getStartIndex()) + lineWidth);
			p4.setY(getWidgetHeight() - getMarginBottom());

			painter.drawLine(p1, p2);
			painter.drawLine(p1, p3);
			painter.drawLine(p2, p4);
			painter.drawLine(p3, p4);
		}

	}
	pData = nullptr;
}


void KVolumeGrid::drawAverageLine(int day)
{

	auto pData = getPData();

	//画线要连接的点
	QVector<QPoint> point;

	//临时点
	QPoint temp;

	//x轴步进
	double xstep = getGridWidth() / getTotalIndex();
	double yscale = getGridHeight() / maxVolume;



	switch (day)
	{
	case 5:
		for (int i = getStartIndex(); i<getEndIndex(); ++i)
		{
			if (pData->kline[i].volumeAverage5 == 0)
				continue;
			temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
			temp.setY(getWidgetHeight() - pData->kline[i].volumeAverage5 / 100 * yscale - getMarginBottom());
			point.push_back(temp);
		}
		break;
	case 10:
		for (int i = getStartIndex(); i<getEndIndex(); ++i)
		{
			if (pData->kline[i].volumeAverage10 == 0)
				continue;
			temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
			temp.setY(getWidgetHeight() - pData->kline[i].volumeAverage10 / 100 * yscale - getMarginBottom());
			point.push_back(temp);
		}
		break;
	}

	QPainter painter(this);
	QPen     pen;

	switch (day)
	{
	case 5:
		pen.setColor(Qt::white);
		break;
	case 10:
		pen.setColor(Qt::yellow);
		break;
	}


	painter.setPen(pen);
	QPolygon polykline(point);
	painter.drawPolyline(polykline);

}



void KVolumeGrid::drawCrossLine(double begin, double end)
{
	StockGrid::drawCrossLine(0, maxVolume);
}

void KVolumeGrid::drawCorssVerLine()
{
	StockGrid::drawCorssVerLine();
}

void KVolumeGrid::drawCorssHorLine()
{
	StockGrid::drawCorssHorLine();
}

void KVolumeGrid::drawTips(double begin, double end)
{
	StockGrid::drawTips(0, maxVolume);
}





void KVolumeGrid::drawCrossLineKeyDown(double begin, double end)
{
	StockGrid::drawCrossLineKeyDown(0, maxVolume);
}

void KVolumeGrid::drawCorssVerLineKeyDown()
{
	StockGrid::drawCorssVerLineKeyDown();
}

void KVolumeGrid::drawCorssHorLineKeyDown(double start, double end, int types)
{
	StockGrid::drawCorssHorLineKeyDown(0, maxVolume, 1);
}

void KVolumeGrid::drawTipsKeyDown(double begin, double end, int types)
{
	StockGrid::drawTipsKeyDown(0, maxVolume, 1);
}



void KVolumeGrid::paintEvent(QPaintEvent *event)
{
	StockGrid::paintEvent(event);

	if (getStartIndex() < 0)
		return;


	drawLine();
	drawAverageLine(5);
	drawAverageLine(10);
	drawInformation();

}


void KVolumeGrid::keyPressEvent(QKeyEvent* event)
{
	StockGrid::keyPressEvent(event);
	update();
}

void KVolumeGrid::getSelfIndicator()
{
	auto pData = getPData();
	if (nullptr == pData)
		return;

	maxVolume = 0;


	for (int i = getStartIndex(); i< getEndIndex(); ++i)
	{
		if (pData->kline[i].ftotalVolume / 100 > maxVolume)
			maxVolume = pData->kline[i].ftotalVolume / 100;
	}
	pData = nullptr;
}


void KVolumeGrid::drawInformation()
{


	auto pData = getPData();
	if (nullptr == pData)
		return;

	QPainter painter(this);
	QPen     pen;

	if (pData->kline[getCurrentIndex()].openingPrice > pData->kline[getCurrentIndex()].closeingPrice)
		pen.setColor(QColor(85, 252, 252));
	else
		pen.setColor(Qt::red);

	QFont ft;
	ft.setPointSize(10);
	painter.setFont(ft);
	painter.setPen(pen);
	QString str;


	int informatonWidth = 150;
	int informatonHeight = 30;


	QRect rectText(getMarginLeft(), 0, informatonWidth + 50, informatonHeight);
	painter.drawText(rectText, QString::fromLocal8Bit("总手") + str.sprintf(":%.0f", pData->kline[getCurrentIndex()].ftotalVolume / 100));


	pen.setColor(Qt::white);
	painter.setPen(pen);
	QRect rectText1(getMarginLeft() + 80, 0, informatonWidth, informatonHeight);
	painter.drawText(rectText1, tr("MAVOL5") + str.sprintf(":%.0f", pData->kline[getCurrentIndex()].volumeAverage5 / 100));

	pen.setColor(Qt::yellow);
	painter.setPen(pen);
	QRect rectText2(getMarginLeft() + 180, 0, informatonWidth, informatonHeight);
	painter.drawText(rectText2, tr("MAVOL10") + str.sprintf(":%.0f", pData->kline[getCurrentIndex()].volumeAverage10 / 100));

	//painter.drawLine(100,100,400,400);

}


