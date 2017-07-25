#pragma once


#include <QtNetwork\QtNetwork.h>

class TcpSingleton : public QTcpSocket
{
public:
	
	~TcpSingleton();
	static TcpSingleton* GetInstance();

private:
	TcpSingleton();
};

