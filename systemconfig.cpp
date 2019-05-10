#include "systemconfig.h"

SystemConfig * SystemConfig::s_sys_config = NULL;
SystemConfig::SystemConfig()
{
	m_configFile = NULL;

}

SystemConfig::~SystemConfig(void)
{
	if (m_configFile != NULL)
		delete m_configFile, m_configFile = 0;
}
void SystemConfig::init()
{
	m_configFile = new TiXmlDocument(fileName.c_str());
}
bool SystemConfig::readxmlfile()
{
	//读取Xml文件，并遍历
	try
	{
		//创建一个XML的文档对象。
		bool loadOkay = m_configFile->LoadFile();
		if (loadOkay) {
			//获得根元素
			TiXmlElement *RootElement = m_configFile->RootElement();
			if (RootElement) 
			{
				TiXmlElement *Element = RootElement->FirstChildElement("map_path");

			
			}
		}
	}
	catch (string& e) {
		return false;
	}
	return true;
}