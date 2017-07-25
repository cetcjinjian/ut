#include "TcpSingleton.h"
#include <QtNetwork\QtNetwork.h>


TcpSingleton::TcpSingleton()
{
	connectToHost(QHostAddress("139.196.38.147"), 8000);
	waitForConnected();
}


TcpSingleton::~TcpSingleton()
{

}


TcpSingleton* TcpSingleton::GetInstance()
{
	static TcpSingleton instance;
	return &instance;
}