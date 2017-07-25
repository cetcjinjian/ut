#ifndef SELFSELECT_H
#define SELFSELECT_H

#include "qwidget.h"
#include <qvector.h>


class QTcpSocket;
class QTableWidget;
class QTableWidgetItem;
class QString;



typedef struct STOCK_CODE
{
	QString code;
	QString name;
	QString changepercent;
	QString trade;
	QString open;
	QString high;
	QString low;
	QString settlement;
	QString volume;
	QString turnoverratio;
	QString amount;
	QString per;
	QString pb;
	QString mktcap;
	QString nmc;
}stCode;


class SelfSelect :public QWidget
{
	Q_OBJECT
public:
	explicit SelfSelect(QWidget* parent=0);
	~SelfSelect();
	QVector<stCode> m_code;

public:
	QTableWidget* pSelfSelect;
	QVector<QString> m_strCode;
	QTcpSocket *pClient = nullptr;
	

public slots:
void readClient();
void Test(int, int);

signals:
void ShowKLine(QString strCode , QString name);

};

#endif // !SELFSELECT_H

