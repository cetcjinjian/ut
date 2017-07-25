#pragma once

#include <qwidget.h>
class QTcpSocket;
class SelfSelect;
class kDayGrid;
class StockDetail;

class RecvDataProcess :public QWidget
{
	Q_OBJECT

public:
	RecvDataProcess(QWidget* parent = 0);
	void SetSelfSelect(SelfSelect* select);
	void SetDayGrid(kDayGrid* day);
	void SetStockDetail(StockDetail* detail);

	void ProcessGetAll(QString data);
	void ProcessKLine(QString data);
	void ProcessRealTime(QString data);


	~RecvDataProcess();

private:
	QTcpSocket* pTcpSocket;
	SelfSelect* pSelfSelect;
	kDayGrid* pDayGrid;
	StockDetail* pStockDetail;


	QVector<QString> m_strCode;

	int recvType = 0;
	QString list_DataAll;

public slots:

void ProcessData();




signals:

};

