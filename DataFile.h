#ifndef DATAFILE_H
#define DATAFILE_H


#include <vector>
#include <QString>
#include <QFile>
#include <QList>
#include <QVariant>
#include <QScopedPointer>



typedef struct
{
    QString time;                   //时间
    double openingPrice;            //开盘
    double highestBid;              //最高
    double lowestBid;               //最低
    double closeingPrice;           //收盘
    double amountOfIncrease;        //涨幅
    double amountOfAmplitude;       //振幅
    QString totalVolume;             //总手
    QString totalAmount;             //金额
    double turnoverRate;            //换手率
    double volumeAmount;            //成交次数
    double averageLine5;            //5日均线
    double averageLine10;           //10日均线
    double averageLine20;           //20日均线
    double averageLine30;           //30日均线
    double averageLine60;           //60日均线
    double ftotalVolume;
    double ftotalAmount;
    double volumeAverage5;        //成交量5日均值
    double volumeAverage10;       //成交量10日均值



    double EMA12;
    double EMA26;
    double DIF;
    double DEA;
    double BAR;
}KLine;


typedef struct
{

    QString data;                   //时间
    double open ;                   //开盘
    double high;                    //最高价
    double close;                   //收盘价
    double low;                     //最低价
    double volume;                  //总手
    double price_change;            //涨跌额
    double p_change;                //涨跌幅度
    double turnover;                //换手
    double amplitude;               //振幅
    double averageLine5;            //5日均线
    double averageLine10;           //10日均线
    double averageLine20;           //20日均线
    double averageLine30;           //30日均线
    double averageLine60;           //60日均线
    double volumeAverage5;          //成交量5日均值
    double volumeAverage10;         //成交量10日均值



    //画MACD用到
    double EMA12;
    double EMA26;
    double DIF;
    double DEA;
    double BAR;










}KLine_txt;

class DataFile
{
public:
    explicit DataFile();
    ~DataFile();
    bool readData(QString filestr);



    std::vector<KLine> kline;
    QFile* pfile = nullptr;
    void calAverageLine();
    void calAverageLine5();
    void calAverageLine10();
    void calAverageLine20();
    void calAverageLine30();
    void calAverageLine60();

    void calvolumeAverage5();
    void calvolumeAverage10();

    void Corvert();

    void calMACD();

    void readExcel(QString strPath);
    void readTxt(QString strPath);
	void readTcp(QStringList strData);


    QList<QList<QVariant>> klineExcel;

public:




};

#endif // DATAFILE_H
