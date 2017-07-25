#pragma once

#include <QtWidgets/QMainWindow>
#include "FrameLessWnd.h"

class TitleBar;
class SideBar;
class QVBoxLayout;
class QHBoxLayout;
class SelfSelect;
class RecvDataProcess;
class QTcpSocket;
class kDayGrid;
class StockDetail;
class QWebEngineView;
class QWebEnginePage;
class QueryCode;

class MainWindow : public FrameLessWnd
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	void virtual keyPressEvent(QKeyEvent* event);

private:
	TitleBar* pTitleBar;
	SideBar* pSideBar;


	QVBoxLayout *pMainLayout;
	QVBoxLayout *pTopLayout;
	QHBoxLayout *pMiddleLayout;

	SelfSelect* pSelfSelect;
	RecvDataProcess* pRecvDataProcess;
	QTcpSocket* pTcpSocket;
	kDayGrid* pDayGrid;
	StockDetail* pStockDetail;


	//webÒýÇæ½Ó¿Ú
	QWebEngineView* pWebEngine;
	QWebEnginePage* pWebPage;
	QDockWidget* pWebView;



	QueryCode* pQueryCode;

public slots:
	void ShowKLine();
	void ShowSelfSelect();
	void GetStock(int, int);
	void GetWebIndex();
	void WebLogin();
	void WebBlockData();
	void WebTradeManage();
	void WebTradeCenter();
};
