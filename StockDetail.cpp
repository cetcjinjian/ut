#include "StockDetail.h"
#include "LimitOrder.h"
#include "StockInfo.h"
#include "RealTimeTrade.h"

#include <qsplitter.h>
#include <qlayout.h>


#include <qwidget.h>


StockDetail::StockDetail(QWidget* parent) :QWidget(parent)
{


	pLimitOrder =new LimitOrder(this);
	pStockInfo = new StockInfo(this);
	pRealTimeTrade = new RealTimeTrade(this);


	QSplitter *splitterMain = new QSplitter(Qt::Vertical, 0); //新建主分割窗口，水平分割	
	splitterMain->addWidget(pLimitOrder);
	splitterMain->addWidget(pStockInfo);
	splitterMain->addWidget(pRealTimeTrade);

	splitterMain->setStretchFactor(0, 3);
	splitterMain->setStretchFactor(1, 2);
	splitterMain->setStretchFactor(2, 1);

	splitterMain->setHandleWidth(0);	

	//QList<int> list;
	//splitterMain->setSizes(list << 1 << 1 <<0.5);
	//splitterMain->setStretchFactor(2, 1);
	//splitterMain->setStretchFactor(2, 1);


	QPalette palette;
	palette.setColor(QPalette::Window, QColor("#000000"));
	splitterMain->setPalette(palette);


	//QGridLayout * layout = new QGridLayout();
	QVBoxLayout * layout = new QVBoxLayout();
	layout->addWidget(splitterMain);
	setLayout(layout);
}


StockDetail::~StockDetail()
{
}
