#include "querycode.h"
#include "ui_querycode.h"
#include "TcpSingleton.h"


QueryCode::QueryCode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryCode)
{
    ui->setupUi(this);   
}



QueryCode::~QueryCode()
{
    delete ui;
}


void QueryCode::on_pushButton_clicked()
{
	QString str = ui->lineEdit->text();	
	TcpSingleton* pConnect = TcpSingleton::GetInstance();
	QByteArray ba = QString(str).toLatin1();
	char* ch = ba.data();
	pConnect->write(ch);
	pConnect->flush();
	this->hide();	

}
