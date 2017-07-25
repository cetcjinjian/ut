#pragma once
#include "qwidget.h"



class LimitOrder;
class StockInfo;
class RealTimeTrade;



class StockDetail :public QWidget
{
public:
	StockDetail(QWidget* parent = 0);
	~StockDetail();

public:
	LimitOrder* pLimitOrder;
	StockInfo* pStockInfo;
	RealTimeTrade* pRealTimeTrade;
};

