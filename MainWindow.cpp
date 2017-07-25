#include "MainWindow.h"

#include <QtNetwork\QtNetwork.h>
#include <QtWebEngineWidgets/QtWebEngineWidgets.h>
#include <QtWebEngineWidgets/qwebengineview.h>


#include "TitleBar.h"
#include "SideBar.h"
#include "qlayout.h"
#include "SelfSelect.h"
#include "RecvDataProcess.h"
#include "TcpSingleton.h"
#include "KDayGrid.h"
#include <qpushbutton.h>
#include "StockDetail.h"
#include "qtablewidget.h"
#include "QueryCode.h"



#pragma comment(lib,"Qt5WebEngine.lib")
#pragma comment(lib,"Qt5WebEngineWidgets.lib")

MainWindow::MainWindow(QWidget *parent)
	: FrameLessWnd(parent)
{
	//�����������С
	resize(1800, 1200);

	//�趨��С��Ⱥ͸߶�
	setMinimumWidth(800);
	setMinimumHeight(600);


	//�趨������ɫ
	QPalette pal(palette());	
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);


	//���ر�����
	pTitleBar = new TitleBar(this);
	installEventFilter(pTitleBar);


	//���ز����
	pSideBar = new SideBar(this);
	pSideBar->setGeometry(0, 24, 24, 400);


	//���㲼����
	pTopLayout = new QVBoxLayout();
	pTopLayout->addWidget(pTitleBar);


	//������ѡ��
	pSelfSelect = new SelfSelect(this);


	//������k��
	pDayGrid = new kDayGrid(this);
	pDayGrid->hide();


	//������������
	pStockDetail = new StockDetail(this);
	pStockDetail->hide();



	//����web����
	pWebEngine = new QWebEngineView(this);
	pWebEngine->load(QUrl("http://192.168.5.51/index.php/admin/login/login"));
	pWebView = new QDockWidget(this);
	pWebView->setWidget(pWebEngine);
	pWebView->hide();







	//�м�㲼����
	pMiddleLayout = new QHBoxLayout();
	pMiddleLayout->addWidget(pSelfSelect);
	pMiddleLayout->addWidget(pDayGrid);
	pMiddleLayout->addWidget(pStockDetail);
	pMiddleLayout->addWidget(pWebView);
	pMiddleLayout->setContentsMargins(24, 10, 10, 10);	
	pMiddleLayout->setStretchFactor(pSelfSelect, 1);

	//��������
	pMainLayout = new QVBoxLayout();

	//������������������������
	pMainLayout->addLayout(pTopLayout);
	pMainLayout->addLayout(pMiddleLayout);
	pMainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(pMainLayout);



	//�������ݴ���
	pTcpSocket = TcpSingleton::GetInstance();
	pRecvDataProcess = new RecvDataProcess();
	pRecvDataProcess->SetSelfSelect(pSelfSelect);
	pRecvDataProcess->SetDayGrid(pDayGrid);
	pRecvDataProcess->SetStockDetail(pStockDetail);
	connect(pTcpSocket, SIGNAL(readyRead()), pRecvDataProcess, SLOT(ProcessData()));


	//��ർ������ť��Ӧ
	connect(pSideBar->m_pKLineBtn, SIGNAL(clicked()), this, SLOT(ShowKLine()));
	connect(pSideBar->m_pSelfStockBtn, SIGNAL(clicked()), this, SLOT(ShowSelfSelect()));


	connect(pSideBar->m_pMainPageBtn, SIGNAL(clicked()), this, SLOT(GetWebIndex()));
	connect(pSideBar->m_pLoginBtn, SIGNAL(clicked()), this, SLOT(WebLogin()));
	connect(pSideBar->m_pBlockDataBtn, SIGNAL(clicked()), this, SLOT(WebBlockData()));
	connect(pSideBar->m_pTradeManagerBtn, SIGNAL(clicked()), this, SLOT(WebTradeManage()));
	connect(pSideBar->m_pTradeCenterBtn, SIGNAL(clicked()), this, SLOT(WebTradeCenter()));



	//��ѡ��˫����Ӧ
	connect(pSelfSelect->pSelfSelect, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(GetStock(int, int)));



	//��ѯ����
	pQueryCode = new QueryCode(this);
	pQueryCode->hide();
}

void MainWindow::WebLogin()
{
	pDayGrid->hide();
	pStockDetail->hide();
	pSelfSelect->hide();
	pWebView->show();

	QWebEnginePage* page = pWebEngine->page();
	page->runJavaScript("document.getElementById('username').value = 'jinjian'");
	page->runJavaScript("document.getElementById('password').value = '123456'");
	page->runJavaScript("document.getElementById('referer').value = '1'");
	page->runJavaScript("document.getElementById('btnSubmit').click()");
}

void MainWindow::WebBlockData()
{
	pDayGrid->hide();
	pStockDetail->hide();
	pSelfSelect->hide();
	pWebView->show();
	pWebEngine->load(QUrl("http://192.168.5.51/index.php/admin/mgdata/index"));
}

void MainWindow::WebTradeManage()
{
	pDayGrid->hide();
	pStockDetail->hide();
	pSelfSelect->hide();
	pWebView->show();
	pWebEngine->load(QUrl("http://192.168.5.51/index.php/admin/trade_schemes/index"));
}

void MainWindow::WebTradeCenter()
{
	pDayGrid->hide();
	pStockDetail->hide();
	pSelfSelect->hide();
	pWebView->show();
	pWebEngine->load(QUrl("http://192.168.5.51/index.php/admin/virtual_accounts/index"));
}

void MainWindow::GetWebIndex()
{
	pDayGrid->hide();
	pStockDetail->hide();
	pSelfSelect->hide();
	pWebView->show();
}
void MainWindow::GetStock(int r, int c)
{

	ShowKLine();

	QTableWidgetItem* pItem = pSelfSelect->pSelfSelect->item(r, 1);
	QString strCode = pItem->text();



	QTableWidgetItem* pItem2 = pSelfSelect->pSelfSelect->item(r , 2);

	if (nullptr == pItem2)
		return;

	QString strName = pItem2->text();

	pDayGrid->pLine->stockName = strName;
	QByteArray ba = QString(strCode).toLatin1();
	char* ch = ba.data();
	pTcpSocket->write(ch);
	pTcpSocket->flush();
}

void MainWindow::ShowKLine()
{
	pWebView->hide();
	pSelfSelect->hide();
	pDayGrid->show();
	pStockDetail->show();
	pMiddleLayout->setStretchFactor(pDayGrid, 5);
	pMiddleLayout->setStretchFactor(pStockDetail, 1);

}

void MainWindow::ShowSelfSelect()
{
	pSelfSelect->show();
	pDayGrid->hide();
	pStockDetail->hide();
	pWebView->hide();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Enter:
		{
			pQueryCode->show();
			break;
		}
	}
}