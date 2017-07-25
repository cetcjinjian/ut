#include "ConfigIni.h"


#include <qsettings.h>


ConfigIni::ConfigIni()
{

}

ConfigIni::~ConfigIni()
{

}

ConfigIni* ConfigIni::GetInstance()
{
	static ConfigIni instance;
	return &instance;
}


int ConfigIni::GetSelfSelectNum()
{
	pSettings = new QSettings(m_strConfigPath, QSettings::IniFormat);
	int iSelfSelectNum = pSettings->value("/itsut/self_select").toInt();
	return iSelfSelectNum;
}
stSelfSelect* ConfigIni::GetSelfSelect()
{
	stSelfSelect* pSelfSelect = new stSelfSelect[GetSelfSelectNum()];	
	for (int i = 0; i < GetSelfSelectNum() ; ++i)
	{
		QString strSection;
		strSection = QString::number(i + 1, 10);		
		strSection = "self_select_" + strSection + "/stock_code";		
		pSelfSelect[i].stock_code = pSettings->value(strSection).toString();

	}
	return pSelfSelect;
}

void ConfigIni::SetConfigPath(QString strConfigPath)
{
	m_strConfigPath = strConfigPath;
}


stServerPoint* ConfigIni::GetServerPoint()
{
	return nullptr;
}