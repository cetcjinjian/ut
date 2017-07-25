#include "kdaygrid.h"


#include <QSplitter>

#include <QKeyEvent>
#include <QMessageBox>
#include <QFile>
#include <QGridLayout>

void kDayGrid::showNewKline()
{
    //读取数据
    QFile mFile("c:/day/"+codeStr+".txt");
    while( !mFile.exists() )
        ;
    pData->readTxt("c:/day/"+codeStr+".txt");

    //各个部件初始化
    pLine->initial();
    pVolume->initial();
    pMacd->initial();
}


void kDayGrid::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    default:
        break;
    }
}

QString kDayGrid::getCodeStr() const
{
    return codeStr;
}

void kDayGrid::setCodeStr(const QString &value)
{
    codeStr = value;
}


void kDayGrid::mouseMoveEvent(QMouseEvent* event)
{
	setCursor(Qt::ArrowCursor);
}

kDayGrid::kDayGrid(QWidget* parent):QWidget(parent)
{

    //初始化数据
    pData = new DataFile;
    //if( 0 == pData->readData(tr("dataKLine.txt")) )
      // return;

    //pData->readTxt("C:/day/600608.txt");

	pData->readTxt(".\\600608.txt");

    //构造订阅者
    mSubscribe = new Subscribe(this);


    //构造k线
    pLine = new KLineGrid(this);
    mSubscribe->Attach(pLine);
    pLine->setSubscribe(mSubscribe);

    //构造成交量
    pVolume = new KVolumeGrid(this);
    mSubscribe->Attach(pVolume);
    pVolume->setSubscribe(mSubscribe);

    //构造macd
    pMacd = new KMacdGrid(this);
    mSubscribe->Attach(pMacd);
    pMacd->setSubscribe(mSubscribe);


    //各个部件初始化
    pLine->setPData(pData);
    pLine->initial();
    pLine->setFocusPolicy(Qt::StrongFocus);

    pVolume->setPData(pData);
    pVolume->initial();
    pVolume->setFocusPolicy(Qt::StrongFocus);

    pMacd->setPData(pData);
    pMacd->initial();
    pMacd->setFocusPolicy(Qt::StrongFocus);




    QSplitter *splitterMain = new QSplitter(Qt::Vertical, 0); //新建主分割窗口，水平分割

    splitterMain->setHandleWidth(0);


    splitterMain->addWidget(pLine);
    splitterMain->addWidget(pVolume);
    splitterMain->addWidget(pMacd);

    splitterMain->setStretchFactor(0,3);
    splitterMain->setStretchFactor(1,1);
    splitterMain->setStretchFactor(2,1);


    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    splitterMain->setPalette(palette);


    QGridLayout * layout = new QGridLayout();
    layout->addWidget(splitterMain);


    this->setLayout(layout);

    //this->

    //this->setWidget(splitterMain);
    //this->

}













