#include "SideBar.h"
#include <qpushbutton.h>
#include <qlayout.h>

SideBar::SideBar(QWidget* parent):QWidget(parent)
{
	//设置SideBar背景颜色
	QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(210, 210, 210));
	setAutoFillBackground(true);
	setPalette(pal);


	//设置宽度
	setFixedWidth(24);
	setFixedHeight(400);


	//初始化侧边栏按钮
	m_pKLineBtn = new QPushButton(u8"K\n线\n图",this);
	m_pTimeShareBtn = new QPushButton(u8"分\n时\n图", this);
	m_pSelfStockBtn = new QPushButton(u8"自\n选\n股", this);	
	m_pMainPageBtn = new QPushButton(u8"主\n页", this);
	m_pLoginBtn = new QPushButton(u8"登\n陆", this);
	m_pTradeManagerBtn = new QPushButton(u8"方\n案\n管\n理", this);
	m_pBlockDataBtn = new QPushButton(u8"板\n块\n数\n据", this);
	m_pTradeCenterBtn = new QPushButton(u8"交\n易\n中\n心", this);

	

	//设置垂直布局器，放入按钮
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
