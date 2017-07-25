#ifndef CONFIGINI_H
#define CONFIGINI_H


#include <qstring.h>

class QSettings;

typedef struct SERVER_POINT
{
	QString system_class;
	QString system_enable;
	QString server_address;
	QString server_port;

}stServerPoint;


typedef struct SELF_SELECT
{
	QString stock_code;

}stSelfSelect;

class ConfigIni
{
public:
	
	~ConfigIni();
	static ConfigIni* GetInstance();


	void SetConfigPath(QString strConfigPath);	
	int GetSelfSelectNum();
	stServerPoint* GetServerPoint();
	stSelfSelect* GetSelfSelect();

private:
	QString m_strConfigPath;
	QSettings* pSettings;
	ConfigIni();

};



#endif 

