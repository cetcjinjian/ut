#include "kmacdgrid.h"
#include "datafile.h"
#include "stockgrid.h"
#include <QPen>
#include <QPainter>
#include <QString>
#include <QVector>
#include <QPoint>



KMacdGrid::KMacdGrid(QWidget* parent) : StockGrid(parent)
{
	//this->setAttribute(Qt::WA_TransparentForMouseEvents);

	setAtomGridHeightMin(30);
}


void KMacdGrid::initial()
{
	StockGrid::initial();
	getSelfIndicator();
}

void KMacdGrid::drawLine()
{
	//画的k线所需的参数  最高价 最低价
	getSelfIndicator();

	//画y轴坐标轴
	drawYtick();

	//画macd方块
	drawBar();
	//画DIF DEA
	drawDifDea();
}


void KMacdGrid::paintEvent(QPaintEvent* event)
{
	StockGrid::paintEvent(event);

	if (getStartIndex() < 0)
		return;

	drawLine();
	drawInformation();
}

void KMacdGrid::keyPressEvent(QKeyEvent* event)
{
	StockGrid::keyPressEvent(event);
	update();
}

void KMacdGrid::getSelfIndicator()
{
	auto pData = getPData();
	if (nullptr == pData)
		return;

	highestMacd = 0;
	lowestMacd = 1000;

	for (int i = getStartIndex(); i <= getEndIndex(); ++i)
	{
		if (pData->kline[i].DIF > highestMacd)
			highestMacd = pData->kline[i].DIF;
		if (pData->kline[i].DEA > highestMacd)
			highestMacd = pData->kline[i].DEA;
		if (pData->kline[i].BAR> highestMacd)
			highestMacd = pData->kline[i].BAR;


		if (pData->kline[i].DIF < lowestMacd)
			lowestMacd = pData->kline[i].DIF;
		if (pData->kline[i].DEA < lowestMacd)
			lowestMacd = pData->kline[i].DEA;
		if (pData->kline[i].BAR < lowestMacd)
			lowestMacd = pData->kline[i].BAR;
	}
	pData = nullptr;
}

void KMacdGrid::drawYtick()
{

	StockGrid::drawYtick(lowestMacd, highestMacd);

}

void KMacdGrid::drawBar()
{
	QPainter painter(this);
	QPen     pen;
	pen.setColor(Qt::red);
	painter.setPen(pen);


	//y轴缩放
	double yscale = getGridHeight() / (highestMacd - lowestMacd);
	//x轴步进
	double xstep = getGridWidth() / getTotalIndex();

	//画线用到的点
	QPoint p1;
	QPoint p2;

	auto pData = getPData();

	for (int i = getStartIndex(); i<= getEndIndex(); ++i)
	{
		if (pData->kline[i].BAR < 0)
			pen.setColor(Qt::green);
		else
			pen.setColor(Qt::red);


		lineWidth = getGridWidth() / getTotalIndex();

		//为了各个k线之间不贴在一起，设置一个间隔
		lineWidth = lineWidth - 0.2*lineWidth;

		//最小线宽为3
		if (lineWidth < 3)
			lineWidth = 3;


		//画macd柱
		pen.setWidth(1);
		painter.setPen(pen);

		p1.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
		p1.setY(getWidgetHeight() - (0 - lowestMacd) *yscale - getMarginBottom());
		p2.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
		p2.setY(getWidgetHeight() - (pData->kline[i].BAR - lowestMacd) *yscale - getMarginBottom());
		painter.drawLine(p1, p2);
	}

	pData = nullptr;
}

void KMacdGrid::drawDifDea()
{
	//y轴缩放
	double yscale = getGridHeight() / (highestMacd - lowestMacd);

	//画线要连接的点
	QVector<QPoint> point_DIF;
	QVector<QPoint> point_DEA;
	//临时点
	QPoint temp;

	//x轴步进
	double xstep = getGridWidth() / getTotalIndex();



	auto pData = getPData();


	if (getStartIndex() < 0)
		return;


	//DIF
	for (int i = getStartIndex(); i<getEndIndex(); ++i)
	{
		temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
		temp.setY(getWidgetHeight() - (pData->kline[i].DIF - lowestMacd) *yscale - getMarginBottom());
		point_DIF.push_back(temp);
	}

	QPainter painter(this);
	QPen     pen;
	pen.setColor(Qt::white);
	painter.setPen(pen);
	QPolygon polykline_DIF(point_DIF);
	painter.drawPolyline(polykline_DIF);




	//DEA
	for (int i = getStartIndex(); i<getEndIndex(); ++i)
	{
		temp.setX(getMarginLeft() + xstep *(i - getStartIndex()) + 0.5*lineWidth);
		temp.setY(getWidgetHeight() - (pData->kline[i].DEA - lowestMacd) *yscale - getMarginBottom());
		point_DEA.push_back(temp);
	}
	pen.setColor(Qt::yellow);
	painter.setPen(pen);
	QPolygon polykline_DEA(point_DEA);
	painter.drawPolyline(polykline_DEA);
	pData = nullptr;
}



void KMacdGrid::drawCrossLine(double begin, double end)
{
	StockGrid::drawCrossLine(lowestMacd, highestMacd);
}

void KMacdGrid::drawCorssVerLine()
{
	StockGrid::drawCorssVerLine();
}

void KMacdGrid::drawCorssHorLine()
{
	StockGrid::drawCorssHorLine();
}

void KMacdGrid::drawTips(double begin, double end)
{
	StockGrid::drawTips(begin, end);
}



void KMacdGrid::drawCrossLineKeyDown(double begin, double end)
{
	StockGrid::drawCrossLineKeyDown(begin, end);
}

void KMacdGrid::drawCorssVerLineKeyDown()
{
	StockGrid::drawCorssVerLineKeyDown();
}

void KMacdGrid::drawCorssHorLineKeyDown(double start, double end, int types)
{
	StockGrid::drawCorssHorLineKeyDown(lowestMacd, highestMacd, 0);
}

void KMacdGrid::drawTipsKeyDown(double begin, double end, int types)
{
	StockGrid::drawTipsKeyDown(lowestMacd, highestMacd, 0);
}


void KMacdGrid::calAtomGridHeight()
{
	int hGridNum = 0;
	int height = getGridHeight();
	while (height - 2 * getAtomGridHeightMin() > 2 * getAtomGridHeightMin())
	{
		hGridNum += 2;
		height -= 2 * getAtomGridHeightMin();
	}
	setHGridNum(hGridNum);
	setAtomGridHeight(getGridHeight() / hGridNum);
}

void KMacdGrid::resizeEvent(QResizeEvent *event)
{
	AutoGrid::resizeEvent(event);
	calAtomGridHeight();

}


void KMacdGrid::drawInformation()
{
	auto pData = getPData();
	if (nullptr == pData)
		return;

	QPainter painter(this);
	QPen     pen;

	QFont ft;
	ft.setPointSize(10);
	painter.setFont(ft);
	pen.setColor(Qt::white);
	painter.setPen(pen);




	int informatonWidth = 100;
	int informatonHeight = 30;

	QRect rectText(getMarginLeft(), 0, informatonWidth, informatonHeight);
	painter.drawText(rectText, tr("MACD(12,26,9)"));


	QString str;


	if (pData->kline[getCurrentIndex()].BAR >0)
		pen.setColor(Qt::red);
	else
		pen.setColor(Qt::green);

	painter.setPen(pen);
	QRect rectText2(getMarginLeft() + informatonWidth, 0, informatonWidth, informatonHeight);
	painter.drawText(rectText2, tr("MACD") + str.sprintf(":%.3f", pData->kline[getCurrentIndex()].BAR));


	pen.setColor(Qt::white);
	painter.setPen(pen);
	QRect rectText3(getMarginLeft() + 2 * informatonWidth, 0, informatonWidth, informatonHeight);
	painter.drawText(rectText3, tr("DIFF") + str.sprintf(":%.3f", pData->kline[getCurrentIndex()].DIF));



	pen.setColor(Qt::yellow);
	painter.setPen(pen);
	QRect rectText4(getMarginLeft() + 3 * informatonWidth, 0, informatonWidth, informatonHeight);
	painter.drawText(rectText4, tr("DEA") + str.sprintf(":%.3f", pData->kline[getCurrentIndex()].DEA));
}
