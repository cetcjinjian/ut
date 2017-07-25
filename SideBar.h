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
	QPushButton *m_pKLineBtn;		//K��
	QPushButton *m_pSelfStockBtn;	//��ѡ��
	QPushButton *m_pTimeShareBtn;	//��ʱ��
	QPushButton *m_pMainPageBtn;	//��ҳ
	QPushButton *m_pLoginBtn;		//��½
	QPushButton *m_pTradeManagerBtn;//���׹���
	QPushButton *m_pBlockDataBtn;	//�������
	QPushButton *m_pTradeCenterBtn;	//��������
};

#endif // !SIDEBAR_H





