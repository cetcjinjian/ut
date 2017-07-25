#include "limitOrder.h"
#include <QPainter>
#include <QPen>



LimitOrder::LimitOrder(QWidget* parent) : QWidget(parent)
{

}

void LimitOrder::initial()
{

}

void LimitOrder::drawGrid()
{
    //draw background
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    this->setPalette(palette);
    drawBorder();
}

void LimitOrder::drawBorder()
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



    //画两条水平分割线 - 第一条
    int ySplitter = ( this->height()-marginTop - marginBottom -30 ) /10;
    xstart = marginLeft;
    ystart = marginTop + 30;
    xend =  this->width() - marginRight;
    yend = marginTop + 30;
    painter.drawLine(xstart,ystart,xend,yend);


    //第二条
    xstart = marginLeft;
    ystart = marginTop + 6*ySplitter;
    xend =  this->width() - marginRight;
    yend = marginTop + 6*ySplitter;
    painter.drawLine(xstart,ystart,xend,yend);

    //画买盘，卖盘的两条竖线


    xstart = marginLeft + textWidth;
    ystart = marginTop + 30;
    xend =  marginLeft + textWidth;
    yend = this->height() - marginBottom;
    painter.drawLine(xstart,ystart,xend,yend);

}


void LimitOrder::drawText()
{

    int ySplitter = ( this->height()-marginTop - marginBottom ) /11;

    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::white);
    QFont ft;
    ft.setPointSize(13);
	
    painter.setFont(ft);
    painter.setPen(pen);
    QString str;

    QRect rectText(getMarginLeft()+5,getMarginTop()+8,200,ySplitter);
    painter.drawText(rectText,QString::fromLocal8Bit("委比"));



    ft.setPointSize(14);
    painter.setFont(ft);
    rectText = QRect(getMarginLeft()+4,getMarginTop()+3*ySplitter - 10,
                     textWidth,textHeight);
    painter.drawText(rectText,QString::fromLocal8Bit("卖"));

    rectText = QRect(getMarginLeft()+4,getMarginTop()+4*ySplitter,
                     textWidth,textHeight);
    painter.drawText(rectText,QString::fromLocal8Bit("盘"));


    rectText = QRect(getMarginLeft()+4,getMarginTop()+8*ySplitter - 10,
                     textWidth,textHeight);
    painter.drawText(rectText,QString::fromLocal8Bit("买"));
    rectText = QRect(getMarginLeft()+4,getMarginTop()+9*ySplitter ,
                     textWidth,textHeight);
    painter.drawText(rectText,QString::fromLocal8Bit("盘"));









	//画实时委托信息

	ft.setBold(true);

	int fontSize = 12;
	int fontMargin = (this->height() - marginTop - marginBottom - 30 - 10 * 2.5* fontSize) / 9;
	//if (fontMargin < 0)
	//	fontMargin = 0;
	int width = (this->width() - marginLeft - marginRight - textWidth) / 3;


	ft.setPointSize(fontSize);
	pen.setColor(Qt::white);
	painter.setPen(pen);
	painter.setFont(ft);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	QString str1[10] = { "5","4","3", "2", "1", "1", "2", "3", "4", "5" };
	QString price[10] = { fSell5Price ,fSell4Price ,fSell3Price ,fSell2Price ,fSell1Price,
						  fBuy1Price,fBuy2Price,fBuy3Price,fBuy4Price,fBuy5Price };
	QString volume[10] = { fSell5Volume ,fSell4Volume ,fSell3Volume ,fSell2Volume ,fSell1Volume,
							fBuy1Volume ,fBuy2Volume ,fBuy3Volume ,fBuy4Volume ,fBuy5Volume };

	for (int i = 0; i < 10; ++i)
	{
		pen.setColor(Qt::white);
		painter.setPen(pen);
		rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + i*(2.5*fontSize + fontMargin),200, fontSize + 5);
		painter.drawText(rectText, str1[i]);

		rectText = QRect(getMarginLeft() + 5 + textWidth + width - 30, getMarginTop() + 30 + i*(2.5*fontSize + fontMargin),200, fontSize + 5);
		if (price[i].toDouble() > fPreClosePrice.toDouble())
			pen.setColor(Qt::red);
		else if (fSell5Price.toDouble() == fPreClosePrice.toDouble())
			pen.setColor(Qt::white);
		else
			pen.setColor(Qt::green);
		painter.setPen(pen);
		painter.drawText(rectText, price[i]);


		rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + i*(2.5*fontSize + fontMargin),200, fontSize + 5);
		pen.setColor(Qt::cyan);
		painter.setPen(pen);
		painter.drawText(rectText, volume[i]);
	}

	/*

	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30,
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("5"));



	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30,
		200, fontSize + 5);
	if (fSell5Price.toDouble() > fOpenPrice.toDouble())
		pen.setColor(Qt::red);
	else if (fSell5Price.toDouble() == fOpenPrice.toDouble())
		pen.setColor(Qt::white);
	else
		pen.setColor(Qt::green);
	painter.setPen(pen);
	painter.drawText(rectText, fSell5Price);



	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30,
		200, fontSize + 5);
	pen.setColor(Qt::cyan);
	painter.setPen(pen);
	painter.drawText(rectText, fSell5Volume);



	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 2.5*fontSize + fontMargin,
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("4"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 2.5*fontSize + fontMargin,
		200, fontSize + 5);
	painter.drawText(rectText, fSell4Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 2.5*fontSize + fontMargin,
		200, fontSize + 5);
	painter.drawText(rectText, fSell4Volume);


	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 2 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("3"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 2 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fSell3Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 2 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fSell3Volume);


	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 3 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("2"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 3 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fSell2Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 3 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fSell2Volume);




	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 4 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("1"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 4 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fSell1Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 4 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fSell1Volume);


	//~~~~~~~~~~~~~~


	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 5 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("1"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 5 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy1Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 5 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy1Volume);




	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 6 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("2"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 6 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy2Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 6 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy2Volume);




	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 7 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("3"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 7 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy3Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 7 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy3Volume);




	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 8 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("4"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 8 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy4Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 8 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy4Volume);



	rectText = QRect(getMarginLeft() + 5 + textWidth, getMarginTop() + 30 + 9 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, QString::fromLocal8Bit("5"));

	rectText = QRect(getMarginLeft() + 5 + textWidth + width, getMarginTop() + 30 + 9 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy5Price);


	rectText = QRect(getMarginLeft() + 5 + textWidth + 2 * width, getMarginTop() + 30 + 9 * (2.5*fontSize + fontMargin),
		200, fontSize + 5);
	painter.drawText(rectText, fBuy5Volume);

	*/

}



void LimitOrder::SetOrderInformation(QStringList info)
{


	fPreClosePrice = info[37];

	fBuy1Volume = info[45];
	fBuy1Price = info[46];

	fBuy2Volume = info[47];
	fBuy2Price = info[48];

	fBuy3Volume = info[49];
	fBuy3Price = info[50];

	fBuy4Volume = info[51];
	fBuy4Price = info[52];

	fBuy5Volume = info[53];
	fBuy5Price = info[54];

	fSell1Volume = info[55];
	fSell1Price = info[56];

	fSell2Volume = info[57];
	fSell2Price = info[58];

	fSell3Volume = info[59];
	fSell3Price = info[60];

	fSell4Volume = info[61];
	fSell4Price = info[62];

	fSell5Volume = info[63];
	fSell5Price = info[64];


}

void LimitOrder::drawBidAsk()
{

}

void LimitOrder::paintEvent(QPaintEvent *event)
{
    drawGrid();
    drawText();
}

void LimitOrder::keyPressEvent(QKeyEvent *event)
{

}


void LimitOrder::resizeEvent(QResizeEvent *event)
{

}


int LimitOrder::getMarginLeft() const
{
    return marginLeft;
}

void LimitOrder::setMarginLeft(int value)
{
    marginLeft = value;
}

int LimitOrder::getMarginRight() const
{
    return marginRight;
}

void LimitOrder::setMarginRight(int value)
{
    marginRight = value;
}

int LimitOrder::getMarginTop() const
{
    return marginTop;
}

void LimitOrder::setMarginTop(int value)
{
    marginTop = value;
}

int LimitOrder::getMarginBottom() const
{
    return marginBottom;
}

void LimitOrder::setMarginBottom(int value)
{
    marginBottom = value;
}
