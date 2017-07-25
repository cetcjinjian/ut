#ifndef LIMITORDER_H
#define LIMITORDER_H


#include <QWidget>
#include "FrameLessWnd.h"

class LimitOrder : public QWidget
{
public:
    explicit LimitOrder(QWidget* parent);
    void virtual initial();
    void virtual paintEvent(QPaintEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);
    void virtual resizeEvent(QResizeEvent* event);

    //画委托部分表格
    void drawGrid();

    //画委托表格的最外侧边框
    void drawBorder();


    //画字符
    void drawText();


    //画委托价格和委托数量
    void drawBidAsk();



    int getMarginLeft() const;
    void setMarginLeft(int value);

    int getMarginRight() const;
    void setMarginRight(int value);

    int getMarginTop() const;
    void setMarginTop(int value);

    int getMarginBottom() const;
    void setMarginBottom(int value);

	void SetOrderInformation(QStringList info);

private:

    //表格距边框距离
    int marginLeft      = 10;
    int marginRight     = 10;
    int marginTop       = 10;
    int marginBottom    = 10;
    int textWidth       = 30;
    int textHeight      = 20;



	//委托信息 买、卖价格及数量

	QString fPreClosePrice = 0;

	QString fSell1Price = 0;
	QString fSell1Volume = 0;

	QString fSell2Price = 0;
	QString fSell2Volume = 0;

	QString fSell3Price = 0;
	QString fSell3Volume = 0;

	QString fSell4Price = 0;
	QString fSell4Volume = 0;

	QString fSell5Price = 0;
	QString fSell5Volume = 0;



	//~~~~~~~~~~~~~~~~~~~~~~

	QString fBuy1Price = 0;
	QString fBuy1Volume = 0;

	QString fBuy2Price = 0;
	QString fBuy2Volume = 0;

	QString fBuy3Price = 0;
	QString fBuy3Volume = 0;

	QString fBuy4Price = 0;
	QString fBuy4Volume = 0;

	QString fBuy5Price = 0;
	QString fBuy5Volume = 0;




};

#endif // LIMITORDER_H
