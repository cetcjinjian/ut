#ifndef STOCKINFO_H
#define STOCKINFO_H

#include "FrameLessWnd.h"

class StockInfo : public QWidget
{
    Q_OBJECT
public:
    explicit StockInfo(QWidget *parent = 0);


    void virtual initial();
    void virtual paintEvent(QPaintEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);
    void virtual resizeEvent(QResizeEvent* event);


    void drawBorder();
	void drawText();


    int getMarginLeft() const;
    void setMarginLeft(int value);

    int getMarginRight() const;
    void setMarginRight(int value);

    int getMarginTop() const;
    void setMarginTop(int value);

    int getMarginBottom() const;
    void setMarginBottom(int value);

	void SetInformation(QStringList info);
private:

    //表格距边框距离
    int marginLeft      = 10;
    int marginRight     = 10;
    int marginTop       = 10;
    int marginBottom    = 10;
    int textWidth       = 20;
    int textHeight      = 20;



	QString dCurrentPrice = "0";
	QString dOpeningPrice = "0";
	QString dPriceChange = "0";
	QString dHighPrice = "0";
	QString dIncreaseChange = "0";
	QString dLowPrice = "0";
	QString dAmplitudePrice = "0";
	QString dVolume = "0";
	QString dAmount = "0";
	QString dPreClose = "0";

signals:

public slots:
};

#endif // STOCKINFO_H
