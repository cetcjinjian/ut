#include "datafile.h"

//#include <ActiveQt/QAxObject>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include <algorithm>
#include <vector>

DataFile::DataFile()
{

}


DataFile::~DataFile()
{
    delete pfile;
    pfile = nullptr;
}

void DataFile::readTcp(QStringList strData)
{

	//std::vector<KLine>().swap(kline);

	strData.pop_back();
	strData.pop_front();

	KLine temp;
	for (int i = 15; i < strData.length()-15; i+=15)
	{
		temp.time = strData[i];
		temp.openingPrice = strData[i + 1].toDouble() ;
		temp.highestBid = strData[i + 2].toDouble();
		temp.closeingPrice = strData[i + 3].toDouble();
		temp.lowestBid = strData[i + 4].toDouble();
		temp.ftotalVolume = strData[i + 5].toDouble();
		temp.amountOfIncrease = strData[i + 7].toDouble();	
		temp.turnoverRate = strData[i + 14].toDouble();
		//计算振幅
		if( i>30)
			temp.amountOfAmplitude = (temp.highestBid - temp.lowestBid)/strData[i + 1 - 15].toDouble() *100;
		else
			temp.amountOfAmplitude = (temp.highestBid - temp.lowestBid)/ temp.openingPrice *100;

		kline.push_back(temp);
	}

	reverse(kline.begin(), kline.end());

	calAverageLine();
	calvolumeAverage5();
	calvolumeAverage10();


	kline[0].EMA12 = kline[0].closeingPrice;
	kline[0].EMA26 = kline[0].closeingPrice;
	kline[0].DIF = 0;
	kline[0].DEA = 0;
	kline[0].BAR = 0;


	calMACD();
	return;

}

void DataFile::readTxt(QString strPath)
{



    std::vector<KLine>().swap(kline);



    pfile = new QFile(strPath);
    if( !pfile->open(QFile::ReadOnly) )
        return ;

    char    line[1024];
    char    *token;
    KLine temp;


    //第一行跳过
    pfile->readLine(line,1024);

    while( pfile->readLine(line,1024)  > 0 )
    {
        token = strtok( line, "," );
        if( token != NULL )
            temp.time = token;

        token = strtok( NULL, "," );
        if( token != NULL )
            temp.openingPrice = atof(token);


        token = strtok( NULL, "," );
        if( token != NULL )
            temp.highestBid = atof(token);



        token = strtok( NULL, "," );
        if( token != NULL )
            temp.closeingPrice = atof(token);


        token = strtok( NULL, "," );
        if( token != NULL )
            temp.lowestBid = atof(token);



        token = strtok( NULL, "," );
        if( token != NULL )
            temp.ftotalVolume = atof(token);


        token = strtok( NULL, "," );
        if( token != NULL )
            temp.amountOfIncrease = atof(token);


        token = strtok( NULL, "," );
        if( token != NULL )
            temp.amountOfAmplitude = atof(token);


        float out;
        token = strtok( NULL, "," );
        if( token != NULL )
            out = atof(token);

        token = strtok( NULL, "," );
        if( token != NULL )
            out = atof(token);
        token = strtok( NULL, "," );
        if( token != NULL )
            out = atof(token);
        token = strtok( NULL, "," );
        if( token != NULL )
            out = atof(token);
        token = strtok( NULL, "," );
        if( token != NULL )
            out = atof(token);
        token = strtok( NULL, "," );
        if( token != NULL )
            out = atof(token);


        token = strtok( NULL, "," );
        if( token != NULL )
            temp.turnoverRate = atof(token);

        kline.push_back(temp);

    }


    reverse(kline.begin(), kline.end());


    calAverageLine();
    calvolumeAverage5();
    calvolumeAverage10();


    kline[0].EMA12 = kline[0].closeingPrice;
    kline[0].EMA26 = kline[0].closeingPrice;
    kline[0].DIF = 0;
    kline[0].DEA = 0;
    kline[0].BAR = 0;
    calMACD();
    return ;
}

bool DataFile::readData(QString filestr)
{
   // readExcel(QString("c:/day/600608.xlsx"));

    pfile = new QFile(filestr);
    if( !pfile->open(QFile::ReadOnly) )
        return false;

    char    line[1024];
    char    *token;
    KLine temp;

    while( pfile->readLine(line,1024)  > 0 )
    {
        token = strtok( line, "'\t'" );
        if( token != NULL )
            temp.time = token;

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.openingPrice = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.highestBid = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.lowestBid = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.closeingPrice = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.amountOfIncrease = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.amountOfAmplitude = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalVolume = (token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalAmount = (token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.turnoverRate = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.volumeAmount = atof(token);

        kline.push_back(temp);

        }

    calAverageLine();
    Corvert();
    calvolumeAverage5();
    calvolumeAverage10();

    kline[0].EMA12 = kline[0].closeingPrice;
    kline[0].EMA26 = kline[0].closeingPrice;
    kline[0].DIF = 0;
    kline[0].DEA = 0;
    kline[0].BAR = 0;


    calMACD();
    return true;
}


void DataFile::calAverageLine()
{

    // 初始化各均线的值
	if (kline.size() >= 5)
	{
		for (int i = 0; i<4; i++)
			kline[i].averageLine5 = 0;
		calAverageLine5();
	}


	if (kline.size() >= 10)
	{
		for (int i = 0; i<9; i++)
			kline[i].averageLine10 = 0;
		calAverageLine10();
	}


	if (kline.size() >= 20)
	{
		for (int i = 0; i<19; i++)
			kline[i].averageLine20 = 0;
		calAverageLine20();
	}


	if (kline.size() >= 30)
	{
		for (int i = 0; i<29; i++)
			kline[i].averageLine30 = 0;
		calAverageLine30();
	}


	if (kline.size() >= 60)
	{
		for (int i = 0; i<59; i++)
			kline[i].averageLine60 = 0;
		calAverageLine60();
	}    
}


void DataFile::calAverageLine5()
{
    for( int i=4;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-4;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine5 = sum /5;
    }
}


void DataFile::calAverageLine10()
{
    for( int i=9;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-9;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine10 = sum /10;
    }
}


void DataFile::calAverageLine20()
{
    for( int i=19;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-19;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine20 = sum /20;
    }
}


void DataFile::calAverageLine30()
{
    for( int i=29;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-29;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine30 = sum /30;
    }
}

void DataFile::calAverageLine60()
{
    for( int i=59;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-59;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine60 = sum /60;
    }
}

void DataFile::calvolumeAverage5()
{

    for( int i=4;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-4;j<=i;++j)
        {
            sum += kline[j].ftotalVolume;
        }
        kline[i].volumeAverage5 = sum /5;
    }
}

void DataFile::calvolumeAverage10()
{
    for( int i=9;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-9;j<=i;++j)
        {
            sum += kline[j].ftotalVolume;
        }
        kline[i].volumeAverage10 = sum /10;
    }
}

void DataFile::Corvert()
{
    for(int i=0;i<kline.size();++i)
    {
        QString strtemp = kline[i].totalVolume;
        strtemp = strtemp.mid(1,strtemp.length());
        strtemp = strtemp.mid(0,strtemp.length()-1);
        strtemp.replace(QString(","),QString(""));
        kline[i].ftotalVolume= strtemp.toInt();
    }
}

void DataFile::calMACD()
{
    for(int i=1;i<kline.size();++i)
      {
          kline[i].EMA12 = 0.1538*kline[i].closeingPrice
                          +0.8462*kline[i-1].EMA12;
          kline[i].EMA26 = 0.0741*kline[i].closeingPrice
                          +0.9259*kline[i-1].EMA26;
          kline[i].DIF = kline[i].EMA12-kline[i].EMA26;
          kline[i].DEA = 0.2*kline[i].DIF + 0.8*kline[i-1].DEA;
          kline[i].BAR = 2*(kline[i].DIF-kline[i].DEA);
      }
}


void DataFile::readExcel(QString strPath)
{



 //   kline.clear();



 //   QFile file(strPath);
 //   while( !file.exists())
 //       ;

 //   /*
 //   QAxObject *excel = new QAxObject("Excel.Application");
 //   excel->setProperty("Visible", true);
 //   QAxObject * workBooks = excel->querySubObject("WorkBooks");
 //   workBooks->dynamicCall("Open(const QString&)",strPath);
 //   //QVariant titleValue = excel->property("Caption");    // 获取标题
 //   //qDebug() << "excel title : " << titleValue;

 //   QAxObject * workBook = excel->querySubObject("ActiveWorkBook");
 //   QAxObject * workSheets = workBook->querySubObject("Sheets");    // Sheets也可换作WorkSheets

	//*/


 //   QAxObject excel("Excel.Application");

 //   excel.setProperty("Visible", false);    // 调试的时候设为true，release模式设为false，不可见

 //   QAxObject * workBooks = excel.querySubObject("WorkBooks");

 //   workBooks->dynamicCall("Open(const QString&)", strPath);

 //   QVariant titleValue = excel.property("Caption");    // 获取标题

 //   qDebug() << "excel title : " << titleValue;

 //   QAxObject * workBook = excel.querySubObject("ActiveWorkBook");

 //   QAxObject * workSheets = workBook->querySubObject("Sheets");    // Sheets也可换作WorkSheets




 //   int sheetCount = workSheets->property("Count").toInt();    // 获取工作表数目

 //   qDebug() << "sheet count : " << sheetCount;

 //   for (int i = 1; i <= sheetCount; i++)

 //   {

 //       QAxObject *workSheet = workBook->querySubObject("Sheets(int)", i);    // 可以用WorkSheets(int)

 //       QString sheetName = workSheet->property("Name").toString();    // 获取工作表名称

 //       qDebug() << "sheet" << QString::number(i, 10) << " name: " << sheetName;

 //        QVariant var;


 //        QAxObject *usedRange = workSheet->querySubObject("UsedRange");
 //        if(NULL == usedRange || usedRange->isNull())
 //        {
 //            return ;
 //        }
 //        var = usedRange->dynamicCall("Value");
 //        delete usedRange;



 //        QVariantList varRows = var.toList();
 //        if(varRows.isEmpty())
 //        {
 //            return;
 //        }
 //        const int rowCount = varRows.size();
 //        QVariantList rowData;
 //        for(int i=0;i<rowCount;++i)
 //        {
 //            rowData = varRows[i].toList();
 //            klineExcel.push_back(rowData);
 //        }

 //   }



 //   workBook->dynamicCall("Close(Boolen)", false);    // 关闭文件

 //   excel.dynamicCall("Quit(void)");    // 退出



 //   qDebug()<<klineExcel.length()<<klineExcel[0].length()<<(klineExcel[1])[0]<<(klineExcel[1])[1];



 //   for( int i=klineExcel.length()-1 ;i>0;--i)
 //   {
 //       KLine temp;
 //       temp.time =((klineExcel[i])[0]).toString();
 //       temp.openingPrice =((klineExcel[i])[1]).toDouble();
 //       temp.highestBid = ((klineExcel[i])[2]).toDouble();
 //       temp.closeingPrice = ((klineExcel[i])[3]).toDouble();
 //       temp.lowestBid = ((klineExcel[i])[4]).toDouble();
 //       temp.ftotalVolume = ((klineExcel[i])[5]).toDouble();
 //       temp.amountOfIncrease = ((klineExcel[i])[6]).toDouble();
 //       temp.amountOfAmplitude = ((klineExcel[i])[7]).toDouble();
 //       temp.turnoverRate = ((klineExcel[i])[14]).toDouble();
 //       kline.push_back(temp);
 //   }
}

