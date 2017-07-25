#ifndef KLINEDETAIL_H
#define KLINEDETAIL_H


#include "FrameLessWnd.h"


class KLineDetail : public FrameLessWnd
{

    Q_OBJECT

public:
    explicit KLineDetail(QWidget* parent);
    void virtual paintEvent(QPaintEvent* event);
    void virtual drawBK();
    void drawStr();


private:

    QString time = "";
    double currentPrice = 0;
    double openingPrice = 0;
    double highestBid = 0;
    double lowestBid =0;
    double closeingPrice =0;
    double amountOfIncrease=0;
    double amountOfAmplitude =0;
    double totalVolume = 0;
    QString totalAmount = "";
    double turnoverRate = 0;



    QColor timeColor ;
    QColor currentPriceColor ;
    QColor openingPriceColor ;
    QColor highestBidColor ;
    QColor lowestBidColor ;
    QColor closeingPriceColor ;
    QColor amountOfIncreaseColor;
    QColor amountOfAmplitudeColor ;
    QColor totalVolumeColor ;
    QColor totalAmountColor ;
    QColor turnoverRateColor ;

    int height = 20;
    int width = 100;
    int margin_left = 10;

public :

  void receiveParams(QString time,QColor timeColor,
                     double currentPrice,QColor currentPriceColor,
                     double openingPrice,QColor openingPriceColor,
                     double highestBid,QColor highestBidColor,
                     double lowestBid,QColor lowestBidColor,
                     double closeingPrice,QColor closeingPriceColor,
                     double amountOfIncrease,QColor amountOfIncreaseColor,
                     double amountOfAmplitude,QColor amountOfAmplitudeColor,
                     double totalVolume,QColor totalVolumeColor,
                     QString totalAmount,QColor totalAmountColor,
                     double turnoverRate,QColor turnoverRateColor);
};

#endif // SHOWDETAIL_H
