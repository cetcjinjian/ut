#include "KLineDetail.h"
#include <QPainter>
#include <QFont>
#include "KLineGrid.h"

KLineDetail::KLineDetail(QWidget* parent) : FrameLessWnd(parent)
{

    QFont ft;
    ft.setPointSize(12);
    this->setFont(ft);
}


void KLineDetail::drawBK()
{
    this->setAutoFillBackground(true);
    QPalette palette;
	palette.setColor(QPalette::Window, QColor("#00000000"));   
    this->setPalette(palette);
}

void KLineDetail::paintEvent(QPaintEvent *event)
{
    drawBK();
    drawStr();
}

void KLineDetail::drawStr()
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);

    int h = 0;

    QRect rectTime( margin_left,h,width,height);
    painter.drawText(rectTime,tr(u8"时间"));

    h += height;

    pen.setColor(timeColor);
    painter.setPen(pen);
    QRect rectTime2( margin_left,h,width,height);
    QString str = time.mid(0,4);
    painter.drawText(rectTime2,str);



    h += height;

    pen.setColor(timeColor);
    painter.setPen(pen);
    QRect rectTime2_2( margin_left,h,width,height);
    QString str2 = time.mid(5,2) + time.mid(8,2);
    painter.drawText(rectTime2_2,str2);


    h += height;

    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime3(margin_left,h,width,height);
    painter.drawText(rectTime3,tr(u8"数值"));


    h += height;


    pen.setColor(currentPriceColor);
    painter.setPen(pen);
    QRect rectTime4(margin_left,h,width,height);
    painter.drawText(rectTime4,str.sprintf("%.2f",currentPrice));


    h += height;

    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime5(margin_left,h,width,height);
    painter.drawText(rectTime5,tr(u8"开盘"));

    h += height;

    pen.setColor(openingPriceColor);
    painter.setPen(pen);
    QRect rectTime6(margin_left,h,width,height);
    painter.drawText(rectTime6,str.sprintf("%.2f",openingPrice));

    h += height;

    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime7(margin_left,h,width,height);
    painter.drawText(rectTime7,tr(u8"最高"));


    h += height;


    pen.setColor(highestBidColor);
    painter.setPen(pen);
    QRect rectTime8(margin_left,h,width,height);
    painter.drawText(rectTime8,str.sprintf("%.2f",highestBid));


    h += height;


    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime9(margin_left,h,width,height);
    painter.drawText(rectTime9,tr(u8"最低"));


    h += height;

    pen.setColor(lowestBidColor);
    painter.setPen(pen);
    QRect rectTime10(margin_left,h,width,height);
    painter.drawText(rectTime10,str.sprintf("%.2f",lowestBid));




    h += height;



    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime11(margin_left,h,width,height);
    painter.drawText(rectTime11,tr(u8"收盘"));




    h += height;


    pen.setColor(closeingPriceColor);
    painter.setPen(pen);
    QRect rectTime12(margin_left,h,width,height);
    painter.drawText(rectTime12,str.sprintf("%.2f",closeingPrice));



    h += height;


    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime13(margin_left,h,width,height);
    painter.drawText(rectTime13,tr(u8"涨幅"));



    h += height;



    pen.setColor(amountOfIncreaseColor);
    painter.setPen(pen);
    QRect rectTime14(margin_left,h,width,height);
    painter.drawText(rectTime14,str.sprintf("%.2f%",amountOfIncrease));




    h += height;



    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime15(margin_left,h,width,height);
    painter.drawText(rectTime15,tr(u8"振幅"));



    h += height;


    pen.setColor(amountOfAmplitudeColor);
    painter.setPen(pen);
    QRect rectTime16(margin_left,h,width,height);
    painter.drawText(rectTime16,str.sprintf("%.2f%",amountOfAmplitude));




    h += height;


    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime17(margin_left,h,width,height);
    painter.drawText(rectTime17,tr(u8"总手"));

    h += height;


	pen.setColor(totalVolumeColor);
	painter.setPen(pen);
	QRect rectTime18(margin_left, h, width, height);
	painter.drawText(rectTime18, str.sprintf("%.0f", (double)totalVolume));

	/*
	pen.setColor(totalVolumeColor);
	painter.setPen(pen);
	QRect rectTime18(margin_left,h,width,height);

	str = totalVolume;

	str = str.mid(1,str.length());
	str = str.mid(0,str.length()-1);
	str.split(',');
	str.replace(",","");

	int Volume = str.toInt();
	str = QString::number( (Volume / 100), 10);

	painter.drawText(rectTime18,str);
	*/








    h += height;


    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime19(margin_left,h,width,height);
    painter.drawText(rectTime19,tr(u8"金额"));

    h += height;

    pen.setColor(totalAmountColor);
    painter.setPen(pen);
    QRect rectTime20(margin_left,h,width,height);

    str = totalAmount;

    str = str.mid(1,str.length());
    str = str.mid(0,str.length()-1);
    str.split(',');
    str.replace(",","");

    int Amount = str.toInt();
    str = QString::number( (Amount / 10000), 10);
    painter.drawText(rectTime20,str);
    h += height;

    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime21(margin_left,h,width,height);
    painter.drawText(rectTime21,tr(u8"换手"));

    h += height;

    pen.setColor(turnoverRateColor);
    painter.setPen(pen);
    QRect rectTime22(margin_left,h,width,height);
    painter.drawText(rectTime22,str.sprintf("%.2f%",turnoverRate));

}

void KLineDetail::receiveParams(QString time,QColor timeColor,
                               double currentPrice,QColor currentPriceColor,
                               double openingPrice,QColor openingPriceColor,
                               double highestBid,QColor highestBidColor,
                               double lowestBid,QColor lowestBidColor,
                               double closeingPrice,QColor closeingPriceColor,
                               double amountOfIncrease,QColor amountOfIncreaseColor,
                               double amountOfAmplitude,QColor amountOfAmplitudeColor,
                               double totalVolume,QColor totalVolumeColor,
                               QString totalAmount,QColor totalAmountColor,
                               double turnoverRate,QColor turnoverRateColor)
{
    this->time = time;
    this->currentPrice = currentPrice;
    this->openingPrice = openingPrice;
    this->highestBid = highestBid;
    this->lowestBid = lowestBid;
    this->closeingPrice = closeingPrice;
    this->amountOfIncrease = amountOfIncrease;
    this->amountOfAmplitude = amountOfAmplitude;
    this->totalVolume = totalVolume;
    this->totalAmount = totalAmount;
    this->turnoverRate = turnoverRate;


    this->timeColor = timeColor;
    this->currentPriceColor = currentPriceColor;
    this->openingPriceColor = openingPriceColor;
    this->highestBidColor = highestBidColor;
    this->lowestBidColor = lowestBidColor;
    this->closeingPriceColor = closeingPriceColor;
    this->amountOfIncreaseColor = amountOfIncreaseColor;
    this->amountOfAmplitudeColor = amountOfAmplitudeColor;
    this->totalVolumeColor = totalVolumeColor;
    this->totalAmountColor = totalAmountColor;
    this->turnoverRateColor = turnoverRateColor;

    update();
}
