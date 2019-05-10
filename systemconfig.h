#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <string.h>
#include <QString>
#include <QStringList>
#include <qdebug.h>
#include "Xml\tinyxml.h"
using namespace std;

class SystemConfig
{
public:
	static SystemConfig *GetInstance()
	{
		if (s_sys_config == NULL)
			s_sys_config = new SystemConfig();
		return s_sys_config;
	}
	static void Release()
	{
		if (s_sys_config != NULL)
		{
			delete s_sys_config;
			s_sys_config = NULL;
		}
	}
private:
	SystemConfig();
	~SystemConfig();
	void init();
	bool readxmlfile();

private:
	TiXmlDocument *m_configFile;
	static SystemConfig * s_sys_config;
	string fileName;
};

#endif // SYSTEMCONFIG_H
