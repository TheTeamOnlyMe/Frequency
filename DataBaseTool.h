#pragma once

#include <QtCore/QCoreApplication>  
#include <QSqlDatabase>	
#include <QSqlQuery>  
#include <QSqlError>  
#include <QSqlDriver>  
#include <QSqlTableModel>	
#include <qhostaddress.h>
#include <QMutex>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>

enum ModeType
{
	NULL_TYPE = 0x0,
	DTBM_TYPE = 0x1,
	FM_TYPE = 0x2,
	AM_TYPE = 0x4,
	SW_TYPE = 0x8,
	INVALID_TYPE = 0xF
};
enum ModeTypeID
{
	DTMB = 0,
	FM,
	AM,
	SW,
	TYPE_COUNT
};
enum PageIndex
{
	NAVIGATION = 0,
	TESTMODE,
	REPORT,
	RECORD
};
enum TestMainPage
{
	DATAPAGE = 0,
	MAPPAGE,
	MULTIPATH,
	SWEEPFREQUENCY,

	SETTING
};

enum OperationBar
{
	RETURN_BTN = 0
};

struct DataType {
	int		type;		//类型（DTMB/FM/AM/SW）
	double	value;		//具体数值
	int		modle;		//模式类型（单点模式、循环模式）
};

struct FrequencyDataRecord
{
	int		id;						//唯一标识
	int		row;					//行号
	QString stationName;			//台站名称
	double	frequencyValue;			//频点数值
	int		type;					//频率类型
	int		status;					//状态
};

class DataBaseTool
{
public:

	static DataBaseTool* GetInstance()
	{
		if (m_database == NULL)  //判断是否第一次调用
			m_database = new DataBaseTool();
		return m_database;
	}
	static void Release()    //必须，否则会导致内存泄露
	{
		if (NULL != m_database)
		{
			delete m_database;
			m_database = NULL;
		}
	}
	DataBaseTool();
	~DataBaseTool();
private:
	static DataBaseTool * m_database;
	QSqlDatabase m_db;
	bool m_bConnectStatus;
	QMutex m_mutex;


public:
	bool Db_Init();
	//void Db_UnInit();

};

