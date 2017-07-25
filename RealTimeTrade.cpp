#include "RealTimeTrade.h"
#include <QGridLayout>
#include <QHeaderView>
#include <QScrollBar>

RealTimeTrade::RealTimeTrade(QWidget *parent) : QWidget(parent)
{


	this->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Window, QColor("#000000"));
	this->setPalette(palette);




    pTradeTable = new QTableWidget(60,4);
    int iTableHeight = 60;
    for(int i=0;i<iTableHeight;++i )
    {
        auto item =  new QTableWidgetItem;
		QString str;

		if( i <10 )
			str = QString("11:0") + QString::number(i, 10);
		else
			str = QString("11:")+ QString::number(i,10);
        item->setTextColor(QColor(255,0,0));
        item->setText(str);
        pTradeTable->setItem(i, 0, item);
    }
    //pTradeTable->setFrameShape(QFrame::NoFrame);
    pTradeTable->setShowGrid(false);
    pTradeTable->horizontalHeader()->hide();
    pTradeTable->verticalHeader()->hide();
    //pTradeTable->horizontalScrollBar()->hide();
    //pTradeTable->verticalScrollBar()->hide();

    //pTradeTable->setContentsMargins(-10,-10,-10,-10);


	pTradeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//pTradeTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	//pTradeTable->verticalHeader()->setResizeMode(QHeaderView::Stretch);

    //pTradeTable->set
   // pTradeTable->setStyleSheet("background-color:rgba(255,255,255,0)");
	pTradeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	pTradeTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	pTradeTable->verticalScrollBar()->hide();
	pTradeTable->horizontalScrollBar()->hide();
	pTradeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(pTradeTable);


}
