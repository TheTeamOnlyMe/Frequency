#include "DataBaseTool.h"



DataBaseTool* DataBaseTool::m_database = NULL;
DataBaseTool::DataBaseTool()
{

	m_db = QSqlDatabase::addDatabase("QSQLITE","data");
	m_db.setDatabaseName("FrequencyDataBase.db");
	if (!m_db.open()) {
		qDebug() << "open db file false";
	}
	
}


DataBaseTool::~DataBaseTool()
{
	m_db.close();
}
bool DataBaseTool::Db_Init()
{
	if (m_database != NULL)
		return m_db.open();
	return false;
	QSqlQuery query(m_db);
	query.exec("select count(*)  from sqlite_master where type='table' and name = 'yourtablename';");
}