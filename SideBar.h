#ifndef SIDEBAR_H
#define SIDEBAR_H


class QPushButton;

#include "qwidget.h"
class SideBar :public QWidget
{
	Q_OBJECT

public:
	SideBar(QWidget* parent = 0);
	~SideBar();

public:
	QPushButton *m_pKLineBtn;		//K线
	QPushButton *m_pSelfStockBtn;	//自选股
	QPushButton *m_pTimeShareBtn;	//分时线
	QPushButton *m_pMainPageBtn;	//主页
	QPushButton *m_pLoginBtn;		//登陆
	QPushButton *m_pTradeManagerBtn;//交易管理
	QPushButton *m_pBlockDataBtn;	//板块数据
	QPushButton *m_pTradeCenterBtn;	//交易中心
};

#endif // !SIDEBAR_H





