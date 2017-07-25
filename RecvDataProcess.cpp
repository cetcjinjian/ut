#include "RecvDataProcess.h"
#include "TcpSingleton.h"
#include <QtNetwork\QtNetwork.h>
#include "ConfigIni.h"
#include <qtablewidget.h>
#include "SelfSelect.h"
#include "DataFile.h"
#include "KDayGrid.h"
#include "StockDetail.h"
#include "LimitOrder.h"
#include "StockInfo.h"

RecvDataProcess::RecvDataProcess(QWidget* parent) : QWidget(parent)
{
	pTcpSocket = TcpSingleton::GetInstance();


	//加载ini文件中的自选股
	ConfigIni* pConfigIni = ConfigIni::GetInstance();
	pConfigIni->SetConfigPath(".\\itsut.ini");
	int iSelfSelect = pConfigIni->GetSelfSelectNum();
	stSelfSelect* pstSelfSelect = pConfigIni->GetSelfSelect();
	for (int i = 0; i < iSelfSelect; ++i)
	{
		m_strCode.push_back(pstSelfSelect[i].stock_code);
	}
}


RecvDataProcess::~RecvDataProcess()
{

}

void RecvDataProcess::SetDayGrid(kDayGrid* day)
{
	pDayGrid = day;
}

void RecvDataProcess::SetStockDetail(StockDetail* detail)
{
	pStockDetail = detail;
}
void RecvDataProcess::ProcessKLine(QString data)
{
	QStringList mlist;
	mlist = data.split(' ');
	auto pDataTemp = new DataFile;
	pDataTemp->readTcp(mlist);

	pDayGrid->pLine->setPData(pDataTemp);
	pDayGrid->pLine->initial();
	pDayGrid->pVolume->setPData(pDataTemp);
	pDayGrid->pVolume->initial();
	pDayGrid->pMacd->setPData(pDataTemp);
	pDayGrid->pMacd->initial();


}
void RecvDataProcess::ProcessRealTime(QString data)
{
	QStringList mlist;
	mlist = data.split(' ');	

	pDayGrid->pLine->stockName = mlist[35];

	pStockDetail->pLimitOrder->SetOrderInformation(mlist);
	pStockDetail->pLimitOrder->update();
	pStockDetail->pStockInfo->SetInformation(mlist);
	pStockDetail->pStockInfo->update();
}


void RecvDataProcess::ProcessGetAll(QString data)
{
	QString str = data;
	QStringList strCode = str.split(' ');

	for (int i = 0; i < m_strCode.length(); ++i)
	{
		for (int j = 0; j < strCode.length(); j += 1)
		{
			if (m_strCode[i] == strCode[j])
			{
				QTableWidgetItem* pItem = new QTableWidgetItem();
				//名称
				pItem->setText(strCode[j + 1]);
				pItem->setTextColor(QColor("#FFFFFF"));
				pSelfSelect->pSelfSelect->setItem(i, 2, pItem);


				//涨幅
				QTableWidgetItem* pItem2 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem2->setTextColor(QColor("#FF0000"));
				else
					pItem2->setTextColor(QColor("#00FF00"));

				double dTemp = strCode[j + 2].toDouble();
				QString strTemp = QString::number(dTemp, 'f', 2);
				pItem2->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 3, pItem2);


				//现价
				QTableWidgetItem* pItem3 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem3->setTextColor(QColor("#FF0000"));
				else
					pItem3->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 3].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem3->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 4, pItem3);


				//开盘
				QTableWidgetItem* pItem4 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem4->setTextColor(QColor("#FF0000"));
				else
					pItem4->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 4].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem4->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 5, pItem4);


				//最高价
				QTableWidgetItem* pItem5 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem5->setTextColor(QColor("#FF0000"));
				else
					pItem5->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 5].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem5->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 6, pItem5);




				//最低价
				QTableWidgetItem* pItem6 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem6->setTextColor(QColor("#FF0000"));
				else
					pItem6->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 6].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem6->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 7, pItem6);

				//昨日收盘价
				QTableWidgetItem* pItem7 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem7->setTextColor(QColor("#FF0000"));
				else
					pItem7->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 7].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem7->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 8, pItem7);


				//成交量
				QTableWidgetItem* pItem8 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem8->setTextColor(QColor("#FF0000"));
				else
					pItem8->setTextColor(QColor("#00FF00"));
				dTemp = strCode[j + 8].toDouble();
				if (dTemp> 1000000)
					strTemp = QString::number(dTemp / 1000000, 'f', 2) + u8"万";
				else
					strTemp = QString::number(dTemp / 100, 'f', 2);
				pItem8->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 9, pItem8);




				//换手率
				QTableWidgetItem* pItem9 = new QTableWidgetItem();
				pItem9->setTextColor(Qt::white);
				dTemp = strCode[j + 9].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem9->setText(strTemp + "%");
				pSelfSelect->pSelfSelect->setItem(i, 10, pItem9);




				//成交额
				QTableWidgetItem* pItem10 = new QTableWidgetItem();
				pItem10->setTextColor(Qt::cyan);
				dTemp = strCode[j + 10].toDouble();
				if (dTemp>100000000)
					strTemp = QString::number(dTemp / 100000000, 'f', 2) + u8"亿";
				else
					strTemp = QString::number(dTemp / 10000, 'f', 2) + u8"万";
				pItem10->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 11, pItem10);




				//市盈率

				QTableWidgetItem* pItem11 = new QTableWidgetItem();
				pItem11->setTextColor(Qt::white);

				dTemp = strCode[j + 11].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem11->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 12, pItem11);




				//市净率
				QTableWidgetItem* pItem12 = new QTableWidgetItem();
				pItem12->setTextColor(Qt::white);
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem12->setTextColor(QColor("#FF0000"));
				else
					pItem12->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 12].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem12->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 13, pItem12);



				//总市值
				QTableWidgetItem* pItem13 = new QTableWidgetItem();
				pItem13->setTextColor(Qt::cyan);

				dTemp = strCode[j + 13].toDouble();
				strTemp = QString::number(dTemp / 10000, 'f', 2) + u8"亿";
				pItem13->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 14, pItem13);



				//流通
				QTableWidgetItem* pItem14 = new QTableWidgetItem();
				pItem14->setTextColor(Qt::cyan);


				dTemp = strCode[j + 14].toDouble();
				strTemp = QString::number(dTemp / 10000, 'f', 2) + u8"亿";

				pItem14->setText(strTemp);
				pSelfSelect->pSelfSelect->setItem(i, 15, pItem14);

				break;
			}
		}
	}
}


void RecvDataProcess::ProcessData()
{
	QString str = pTcpSocket->readAll();
	QStringList strCode = str.split(' ');

	if (0 == recvType)
	{
		if (strCode[0] == "CODEALL")
		{
			recvType = 1;
			list_DataAll.clear();			
		}
			
		else if (strCode[0] == "KLINE")
		{
			recvType = 2;
			list_DataAll.clear();
		}
			
		else if (strCode[0] == "REALTIME")
		{
			recvType = 3;
			list_DataAll.clear();
		}
			
	}

	switch (recvType)
	{
	case 1:
		if (strCode[0] == "CODEALL" && strCode[strCode.length() - 1] == "END")
		{
			list_DataAll = str;
			recvType = 0;
			ProcessGetAll(list_DataAll);
		}
		else if (strCode[strCode.length() - 1] != "END")
		{
			list_DataAll += str;
		}
		else if (strCode[strCode.length() - 1] == "END")
		{
			list_DataAll += str;
			recvType = 0;
			ProcessGetAll(list_DataAll);
		}
		break;
	case 2:
		if (strCode[0] == "KLINE" && strCode[strCode.length() - 1] == "END")
		{
			list_DataAll = str;
			recvType = 0;
			ProcessKLine(list_DataAll);
		}
		else if (strCode[strCode.length() - 1] != "END")
		{
			list_DataAll += str;
		}
		else if (strCode[strCode.length() - 1] == "END")
		{
			list_DataAll += str;
			recvType = 0;
			ProcessKLine(list_DataAll);
		}
		break;	
	case 3:
		if (strCode[0] == "REALTIME" && strCode[strCode.length() - 1] == "END")
		{
			list_DataAll = str;
			recvType = 0;
			ProcessRealTime(list_DataAll);
		}
		else if (strCode[strCode.length() - 1] != "END")
		{
			list_DataAll += str;
		}
		else if (strCode[strCode.length() - 1] == "END")
		{
			list_DataAll += str;
			recvType = 0;
			ProcessRealTime(list_DataAll);
		}
		break;		
	}
}

void RecvDataProcess::SetSelfSelect(SelfSelect* select)
{
	pSelfSelect = select;
}