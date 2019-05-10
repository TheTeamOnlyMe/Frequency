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
	int		type;		//���ͣ�DTMB/FM/AM/SW��
	double	value;		//������ֵ
	int		modle;		//ģʽ���ͣ�����ģʽ��ѭ��ģʽ��
};

struct FrequencyDataRecord
{
	int		id;						//Ψһ��ʶ
	int		row;					//�к�
	QString stationName;			//̨վ����
	double	frequencyValue;			//Ƶ����ֵ
	int		type;					//Ƶ������
	int		status;					//״̬
};

class DataBaseTool
{
public:

	static DataBaseTool* GetInstance()
	{
		if (m_database == NULL)  //�ж��Ƿ��һ�ε���
			m_database = new DataBaseTool();
		return m_database;
	}
	static void Release()    //���룬����ᵼ���ڴ�й¶
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

