#include "SelfSelect.h"


#include <qtablewidget.h>
#include <qlayout.h>
#include <qheaderview.h>
#include "ConfigIni.h"
#include <QtNetwork\QtNetwork.h>
#include "TcpSingleton.h"


SelfSelect::SelfSelect(QWidget* parent) :QWidget(parent)
{

	QFont font;
	font.setFamily("΢���ź�");
	font.setPointSize(12);


	this->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Window, QColor("#000000"));
	this->setPalette(palette);


	//~~~~~~~~~~~~~~~~
	pSelfSelect = new QTableWidget(100, 16);
	QStringList strHeader;
	strHeader << u8"" << u8"����" << u8"����" << u8"�Ƿ�" << u8"�ּ�" << u8"���̼�" << u8"��߼�" << u8"��ͼ�" << u8"�������̼�" << u8"�ɽ���"
		<< u8"����" << u8"�ɽ���" << u8"��ӯ��" << u8"�о���" << u8"����ֵ" << u8"��ͨ��ֵ" ;

	pSelfSelect->setHorizontalHeaderLabels(strHeader);
	pSelfSelect->setSelectionBehavior(QAbstractItemView::SelectRows);
	pSelfSelect->setFont(font);

	pSelfSelect->horizontalHeader()->setFont(font);


	//����ini�ļ��е���ѡ��
	ConfigIni* pConfigIni = ConfigIni::GetInstance();
	pConfigIni->SetConfigPath(".\\itsut.ini");
	int iSelfSelect = pConfigIni->GetSelfSelectNum();
	stSelfSelect* pstSelfSelect = pConfigIni->GetSelfSelect();
	for (int i = 0; i < iSelfSelect; ++i)
	{
		m_strCode.push_back(pstSelfSelect[i].stock_code);
	}

	//��ini�ļ��е���ѡ�ɲ��뵽�����

	for (int i = 0; i < iSelfSelect; ++i)
	{
		QTableWidgetItem* pItem1 = new QTableWidgetItem();
		pItem1->setText(QString::number(i + 1, 10));
		pItem1->setTextColor(QColor("#FFFFFF"));
		pSelfSelect->setItem(i, 0, pItem1);

		QTableWidgetItem* pItem2 = new QTableWidgetItem();
		pItem2->setText(m_strCode[i]);
		pItem2->setTextColor(QColor("#FFFFFF"));
		pSelfSelect->setItem(i, 1, pItem2);
	}



	pSelfSelect->setShowGrid(false);
	//pSelfSelect->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	pSelfSelect->verticalHeader()->hide();
	pSelfSelect->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QGridLayout * layout = new QGridLayout(this);
	layout->addWidget(pSelfSelect);



	TcpSingleton* pConnection = TcpSingleton::GetInstance();
	QByteArray ba = QString("getall").toLatin1();
	char* ch = ba.data();
	pConnection->write(ch);
	pConnection->flush();
}
	


SelfSelect::~SelfSelect()
{

}


void SelfSelect::Test(int row, int column)
{

	pClient->close();

	QTableWidgetItem* pItem = pSelfSelect->item(row, 1);	
	QString strCode = pItem->text();

	QTableWidgetItem* pItem2 = pSelfSelect->item(row, 2);
	QString strName = pItem2->text();
	emit(ShowKLine(strCode , strName));
}



void SelfSelect::readClient()
{
	QString str = pClient->readAll();
	//str = str.simplified();
	QStringList strCode = str.split(' ');

	for (int i = 0; i < m_strCode.length(); ++i)
	{
		for (int j = 0; j < strCode.length(); j+=1)
		{
			if (m_strCode[i] == strCode[j])
			{
				QTableWidgetItem* pItem = new QTableWidgetItem();
				//����
				pItem->setText(strCode[j+1]);
				pItem->setTextColor(QColor("#FFFFFF"));
				pSelfSelect->setItem(i, 2, pItem);


				//�Ƿ�
				QTableWidgetItem* pItem2 = new QTableWidgetItem();
				if(strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem2->setTextColor(QColor("#FF0000"));
				else
					pItem2->setTextColor(QColor("#00FF00"));
				
				double dTemp = strCode[j + 2].toDouble();
				QString strTemp = QString::number(dTemp, 'f', 2);
				pItem2->setText(strTemp);
				pSelfSelect->setItem(i, 3, pItem2);


				//�ּ�
				QTableWidgetItem* pItem3 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem3->setTextColor(QColor("#FF0000"));
				else
					pItem3->setTextColor(QColor("#00FF00"));
				
				dTemp = strCode[j + 3].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem3->setText(strTemp);
				pSelfSelect->setItem(i, 4, pItem3);


				//����
				QTableWidgetItem* pItem4 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem4->setTextColor(QColor("#FF0000"));
				else
					pItem4->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 4].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem4->setText(strTemp);
				pSelfSelect->setItem(i, 5, pItem4);


				//��߼�
				QTableWidgetItem* pItem5 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem5->setTextColor(QColor("#FF0000"));
				else
					pItem5->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 5].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem5->setText(strTemp);
				pSelfSelect->setItem(i, 6, pItem5);




				//��ͼ�
				QTableWidgetItem* pItem6 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem6->setTextColor(QColor("#FF0000"));
				else
					pItem6->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 6].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem6->setText(strTemp);
				pSelfSelect->setItem(i, 7, pItem6);

				//�������̼�
				QTableWidgetItem* pItem7 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem7->setTextColor(QColor("#FF0000"));
				else
					pItem7->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 7].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem7->setText(strTemp);
				pSelfSelect->setItem(i, 8, pItem7);


				//�ɽ���
				QTableWidgetItem* pItem8 = new QTableWidgetItem();
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem8->setTextColor(QColor("#FF0000"));
				else
					pItem8->setTextColor(QColor("#00FF00"));
				dTemp = strCode[j + 8].toDouble();
				if(dTemp> 1000000)
					strTemp = QString::number(dTemp/1000000, 'f', 2) + u8"��";
				else
					strTemp = QString::number(dTemp / 100, 'f', 2) ;
				pItem8->setText(strTemp);
				pSelfSelect->setItem(i, 9, pItem8);




				//������
				QTableWidgetItem* pItem9 = new QTableWidgetItem();
				pItem9->setTextColor(Qt::white);
				dTemp = strCode[j + 9].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem9->setText(strTemp+ "%");
				pSelfSelect->setItem(i, 10, pItem9);




				//�ɽ���
				QTableWidgetItem* pItem10 = new QTableWidgetItem();
				pItem10->setTextColor(Qt::cyan);
				dTemp = strCode[j + 10].toDouble();
				if(dTemp>100000000)
					strTemp = QString::number(dTemp/100000000, 'f', 2)+ u8"��";
				else
					strTemp = QString::number(dTemp / 10000, 'f', 2) + u8"��";
				pItem10->setText(strTemp);
				pSelfSelect->setItem(i, 11, pItem10);




				//��ӯ��
				
				QTableWidgetItem* pItem11 = new QTableWidgetItem();
				pItem11->setTextColor(Qt::white);			

				dTemp = strCode[j + 11].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem11->setText(strTemp);
				pSelfSelect->setItem(i, 12, pItem11);




				//�о���
				QTableWidgetItem* pItem12 = new QTableWidgetItem();
				pItem12->setTextColor(Qt::white);
				if (strCode[j + 3].toFloat() - strCode[j + 4].toFloat() > 0)
					pItem12->setTextColor(QColor("#FF0000"));
				else
					pItem12->setTextColor(QColor("#00FF00"));

				dTemp = strCode[j + 12].toDouble();
				strTemp = QString::number(dTemp, 'f', 2);
				pItem12->setText(strTemp);
				pSelfSelect->setItem(i, 13, pItem12);



				//����ֵ
				QTableWidgetItem* pItem13 = new QTableWidgetItem();
				pItem13->setTextColor(Qt::cyan);

				dTemp = strCode[j + 13].toDouble();
				strTemp = QString::number(dTemp/10000, 'f', 2) + u8"��";
				pItem13->setText(strTemp);
				pSelfSelect->setItem(i, 14, pItem13);



				//��ͨ
				QTableWidgetItem* pItem14 = new QTableWidgetItem();
				pItem14->setTextColor(Qt::cyan);


				dTemp = strCode[j + 14].toDouble();
				strTemp = QString::number(dTemp / 10000, 'f', 2) + u8"��";

				pItem14->setText(strTemp);
				pSelfSelect->setItem(i, 15, pItem14);

				break;
			}
		}
	}
}