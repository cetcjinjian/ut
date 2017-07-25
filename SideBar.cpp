#include "SideBar.h"
#include <qpushbutton.h>
#include <qlayout.h>

SideBar::SideBar(QWidget* parent):QWidget(parent)
{
	//����SideBar������ɫ
	QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(210, 210, 210));
	setAutoFillBackground(true);
	setPalette(pal);


	//���ÿ��
	setFixedWidth(24);
	setFixedHeight(400);


	//��ʼ���������ť
	m_pKLineBtn = new QPushButton(u8"K\n��\nͼ",this);
	m_pTimeShareBtn = new QPushButton(u8"��\nʱ\nͼ", this);
	m_pSelfStockBtn = new QPushButton(u8"��\nѡ\n��", this);	
	m_pMainPageBtn = new QPushButton(u8"��\nҳ", this);
	m_pLoginBtn = new QPushButton(u8"��\n½", this);
	m_pTradeManagerBtn = new QPushButton(u8"��\n��\n��\n��", this);
	m_pBlockDataBtn = new QPushButton(u8"��\n��\n��\n��", this);
	m_pTradeCenterBtn = new QPushButton(u8"��\n��\n��\n��", this);

	

	//���ô�ֱ�����������밴ť
	QVBoxLayout *pLayout = new QVBoxLayout(this);
	pLayout->addWidget(m_pKLineBtn);
	pLayout->addWidget(m_pTimeShareBtn);
	pLayout->addWidget(m_pSelfStockBtn);
	pLayout->addWidget(m_pMainPageBtn);
	pLayout->addWidget(m_pLoginBtn);
	pLayout->addWidget(m_pTradeManagerBtn);
	pLayout->addWidget(m_pBlockDataBtn);
	pLayout->addWidget(m_pTradeCenterBtn);
	pLayout->setSpacing(0);
	pLayout->addStretch();
	pLayout->setContentsMargins(0, 0, 0, 0);

}


SideBar::~SideBar()
{

}
