#include "StockInfo.h"
#include <QPainter>
#include <QPen>


StockInfo::StockInfo(QWidget *parent) : QWidget(parent)
{

}

void StockInfo::initial()
{

}


void StockInfo::paintEvent(QPaintEvent *event)
{

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    this->setPalette(palette);

    drawBorder();
	drawText();
}


void StockInfo::keyPressEvent(QKeyEvent *event)
{

}


void StockInfo::resizeEvent(QResizeEvent *event)
{

}


void StockInfo::drawBorder()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#8F0000"));
    painter.setPen(pen);

    //上
    int xstart = marginLeft;
    int ystart = marginTop;
    int xend =  this->width() - marginRight;
    int yend = marginTop;

    painter.drawLine(xstart,ystart,xend,yend);


    //下
    xstart = marginLeft;
    ystart = this->height()-marginBottom;
    xend =  this->width() - marginRight;
    yend = this->height()-marginBottom;
    painter.drawLine(xstart,ystart,xend,yend);


    //左

    xstart = marginLeft;
    ystart = marginTop;
    xend =  marginLeft;
    yend = this->height()-marginBottom;
    painter.drawLine(xstart,ystart,xend,yend);

    //右

    xstart = this->width() - marginRight;
    ystart = marginTop;
    xend =  this->width() - marginRight;
    yend = this->height()-marginBottom;
    painter.drawLine(xstart,ystart,xend,yend);

}

void StockInfo::drawText()
{
	int fontSize = 12;
	int fontMargin = (this->height() - marginTop - marginBottom - 9 * 2.5* fontSize) / 8;
	int width = (this->width() - marginLeft - marginRight) / 2;

	QPainter painter(this);
	QPen     pen;
	QFont ft;
	ft.setPointSize(fontSize);
	pen.setColor(Qt::white);
	painter.setPen(pen);
	painter.setFont(ft);
	QRect rectText(getMarginLeft() + 5, getMarginTop() + 5,200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("最新"));



	if(dCurrentPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if(dCurrentPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width/2, getMarginTop() + 5,200, fontSize + 5);
	painter.drawText(rectText, dCurrentPrice);



	pen.setColor(Qt::white);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5,200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("开盘"));



	if (dOpeningPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if (dOpeningPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width + width / 2, getMarginTop() + 5,
		200, fontSize + 5);
	painter.drawText(rectText, dOpeningPrice);







	pen.setColor(Qt::white);
	painter.setPen(pen); 
	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 2.5* fontSize + fontMargin,
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("涨跌"));



	if (dCurrentPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if (dCurrentPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);	
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width / 2, getMarginTop() + 5 + 2.5* fontSize + fontMargin,200, fontSize + 5);
	QString temp = QString("%1").arg(dCurrentPrice.toDouble() - dPreClose.toDouble());
	painter.drawText(rectText, temp);



	pen.setColor(Qt::white);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop()+5 + 2.5* fontSize + fontMargin,200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("最高"));


	if (dHighPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if (dHighPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width + width / 2, getMarginTop() + 5 + 2.5* fontSize + fontMargin, 200, fontSize + 5);
	temp = QString("%1").arg(dHighPrice.toDouble());
	painter.drawText(rectText, temp);




	pen.setColor(Qt::white);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 2 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("涨幅"));


	if (dCurrentPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if (dCurrentPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5  + width / 2, getMarginTop() + 5 + 2*(2.5* fontSize + fontMargin), 200, fontSize + 5);
	double dtemp = (dCurrentPrice.toDouble() - dPreClose.toDouble()) / dPreClose.toDouble() * 100;
	temp = QString::number(dtemp, 'f', 2);
	temp += "%";
	painter.drawText(rectText, temp);





	pen.setColor(Qt::white);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 2 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("最低"));
	


	if (dLowPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if (dLowPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 +width+ width / 2, getMarginTop() + 5 + 2 * (2.5* fontSize + fontMargin), 200, fontSize + 5);
	temp = QString("%1").arg(dLowPrice.toDouble());
	painter.drawText(rectText, temp);





	pen.setColor(Qt::white);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 3 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("振幅"));


	if (dCurrentPrice.toDouble() > dPreClose.toDouble())
		pen.setColor(Qt::red);
	else if (dCurrentPrice.toDouble() == dPreClose.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width / 2, getMarginTop() + 5 + 3 * (2.5* fontSize + fontMargin), 200, fontSize + 5);
	dtemp = qAbs(dHighPrice.toDouble() - dLowPrice.toDouble()) / dPreClose.toDouble() * 100;
	temp = QString::number(dtemp, 'f', 2);
	temp += "%";
	painter.drawText(rectText, temp);


	pen.setColor(Qt::white);
	painter.setPen(pen);
	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 3 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("量比"));




	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 4 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("总手"));
	pen.setColor(Qt::cyan);
	painter.setPen(pen);

	rectText = QRect(getMarginLeft() + 5 + width / 2, getMarginTop() + 5 + 4 * (2.5* fontSize + fontMargin), 200, fontSize + 5);	
	dtemp = dVolume.toDouble() / 1000000;
	temp = QString::number(dtemp, 'f', 2) + u8"万";
	painter.drawText(rectText, temp);





	pen.setColor(Qt::white);
	painter.setPen(pen);

	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 4 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("换手"));




	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 5 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("金额"));
	pen.setColor(Qt::cyan);
	painter.setPen(pen);

	rectText = QRect(getMarginLeft() + 5 + width / 2, getMarginTop() + 5 + 5 * (2.5* fontSize + fontMargin), 200, fontSize + 5);
	dtemp = dAmount.toDouble() / 100000000;
	temp = QString::number(dtemp, 'f', 2) + u8"亿";
	painter.drawText(rectText, temp);







	pen.setColor(Qt::white);
	painter.setPen(pen);



	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 5 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("换手(实)"));



	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 6 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("市盈"));

	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 6 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("市盈(东)"));


	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 7 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("总市值"));

	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 7 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("流通值"));


	rectText = QRect(getMarginLeft() + 5, getMarginTop() + 5 + 8 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("外盘"));

	rectText = QRect(getMarginLeft() + 5 + width, getMarginTop() + 5 + 8 * (2.5* fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("内盘"));
}


void StockInfo::SetInformation(QStringList info)
{
	dAmount = info[44];
	dVolume = info[43];
	dLowPrice = info[40];
	dHighPrice = info[39];
	dCurrentPrice = info[38];
	dPreClose = info[37];
	dOpeningPrice = info[36];

}


int StockInfo::getMarginLeft() const
{
    return marginLeft;
}

void StockInfo::setMarginLeft(int value)
{
    marginLeft = value;
}

int StockInfo::getMarginRight() const
{
    return marginRight;
}

void StockInfo::setMarginRight(int value)
{
    marginRight = value;
}

int StockInfo::getMarginTop() const
{
    return marginTop;
}

void StockInfo::setMarginTop(int value)
{
    marginTop = value;
}

int StockInfo::getMarginBottom() const
{
    return marginBottom;
}

void StockInfo::setMarginBottom(int value)
{
    marginBottom = value;
}
