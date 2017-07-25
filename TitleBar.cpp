

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <qaction.h>
#include <qfont.h>
#include <qmenu.h>
#include <qmenubar.h>

#include "TitleBar.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	//设置TitleBar背景颜色
	QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(210,210,210));
	setAutoFillBackground(true);
	setPalette(pal);


	//设定高度
	setFixedHeight(24);
	

	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);
	m_pMinimizeButton = new QPushButton(this);
	m_pMaximizeButton = new QPushButton(this);
	m_pCloseButton = new QPushButton(this);


	//设置菜单栏

	m_pMenuBar = new QMenuBar(this);
	m_pMenuBar->setFixedHeight(25);
	m_pMenuBar->setFixedWidth(410);


	//设置菜单字体
	QFont font;
	font.setFamily(u8"微软雅黑");
	font.setPixelSize(13);
	m_pMenuBar->setFont(font);
	

	//设置背景透明
	m_pMenuBar->setAttribute(Qt::WA_TranslucentBackground);
	m_pMenuBar->setStyleSheet("background:rgba(255, 255, 255, 100);");

	//添加菜单 -系统
	m_pSystemMenu = new QMenu(u8"系统", this);	
	m_pMenuBar->addMenu(m_pSystemMenu);	

	QAction* paction = new QAction(u8"连接主站", this);
	m_pSystemMenu->addAction(paction);


	//添加菜单 -报价
	m_pBidMenu = new QMenu(u8"报价", this);
	m_pMenuBar->addMenu(m_pBidMenu);	
	//添加菜单 -分析
	m_pAnalyzeMenu = new QMenu(u8"分析", this);
	m_pMenuBar->addMenu(m_pAnalyzeMenu);
	//添加菜单 -扩展行情
	m_pMarketMenu = new QMenu(u8"扩展行情", this);
	m_pMenuBar->addMenu(m_pMarketMenu);
	//添加菜单 -委托
	m_pEntrustMenu = new QMenu(u8"委托", this);
	m_pMenuBar->addMenu(m_pEntrustMenu);
	//添加菜单 -智能
	m_pSmartMenu = new QMenu(u8"智能", this);
	m_pMenuBar->addMenu(m_pSmartMenu);
	//添加菜单 -工具
	m_pToolMenu = new QMenu(u8"工具", this);
	m_pMenuBar->addMenu(m_pToolMenu);
	//添加菜单 -资讯
	m_pInformationMenu = new QMenu(u8"资讯", this);
	m_pMenuBar->addMenu(m_pInformationMenu);
	//添加菜单 -帮助
	m_pHelpMenu = new QMenu(u8"帮助", this);
	m_pMenuBar->addMenu(m_pHelpMenu);




	m_pIconLabel->setFixedSize(20, 20);
	m_pIconLabel->setScaledContents(true);

	m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


	m_pMinimizeButton->setFixedSize(27, 22);	
	m_pMinimizeButton->setIcon(QIcon(":/icons/Resources/minimize_window.png"));
	m_pMinimizeButton->setIconSize(QSize(30, 22));


	m_pMaximizeButton->setFixedSize(27, 22);
	m_pMaximizeButton->setIcon(QIcon(":/icons/Resources/maximize_window.png"));
	m_pMaximizeButton->setIconSize(QSize(30, 22));


	m_pCloseButton->setFixedSize(27, 22);
	m_pCloseButton->setIcon(QIcon(":/icons/Resources/multiply_.png"));
	m_pCloseButton->setIconSize(QSize(30, 22));

	m_pTitleLabel->setObjectName("whiteLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton->setObjectName("closeButton");

	m_pMinimizeButton->setToolTip("Minimize");
	m_pMaximizeButton->setToolTip("Maximize");
	m_pCloseButton->setToolTip("Close");

	QHBoxLayout *pLayout = new QHBoxLayout(this);	
	pLayout->addWidget(m_pMenuBar);
	pLayout->addSpacing(5);
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(5, 0, 5, 0);

	setLayout(pLayout);

	connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
	connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

TitleBar::~TitleBar()
{

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);

	emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
	if (ReleaseCapture())
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
#else
#endif
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			m_pTitleLabel->setText(pWidget->windowTitle());
			return true;
		}
	}
	case QEvent::WindowIconChange:
	{
		QWidget *pWidget = qobject_cast<QWidget *>(obj);
		if (pWidget)
		{
			QIcon icon = pWidget->windowIcon();
			m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
			return true;
		}
	}
	case QEvent::WindowStateChange:
	case QEvent::Resize:
		updateMaximize();
		return true;
	}
	return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(sender());
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == m_pMinimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == m_pMaximizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == m_pCloseButton)
		{
			pWindow->close();
		}
	}
}

void TitleBar::updateMaximize()
{
	QWidget *pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized();
		if (bMaximize)
		{
			m_pMaximizeButton->setToolTip(tr("Restore"));
			m_pMaximizeButton->setProperty("maximizeProperty", "restore");
		}
		else
		{
			m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
			m_pMaximizeButton->setToolTip(tr("Maximize"));
		}

		m_pMaximizeButton->setStyle(QApplication::style());
	}
}