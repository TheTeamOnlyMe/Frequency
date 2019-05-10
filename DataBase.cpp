#include "DataBase.h"

DataBase* DataBase::m_database =NULL;
DataBase::DataBase()
{
	db = QSqlDatabase::addDatabase("QSQLITE","one");
	db.setDatabaseName("DataBase.db"); // 数据库名与路径, 此时是放在同目录下
	listFrequencyUnits.append("MHz");
	listFrequencyUnits.append("KHz");
	listFrequencyUnits.append("KHz");
	listFrequencyUnits.append("CH");
	listFrequencyUnits.append("CH");
	listFrequencyType.append(QObject::tr("FM"));
	listFrequencyType.append(QObject::tr("MW"));
	listFrequencyType.append(QObject::tr("SW"));
	listFrequencyType.append(QObject::tr("TV"));
	listFrequencyType.append(QObject::tr("DTMB"));
	listColorType.append(QObject::tr("FS"));
	listColorType.append(QObject::tr("SNR")); //信噪比
	listColorType.append(QObject::tr("MER")); //Mer调制误码率
	listColorType.append(QObject::tr("LDPC"));

	//QStringList drivers = QSqlDatabase::drivers();  
	//foreach(QString driver, drivers)  
		//qDebug() << "66666" << driver;  
}
DataBase::~DataBase()
{
	QStringList drivers = QSqlDatabase::drivers();  
	foreach(QString driver, drivers)  
	qDebug() << "66666" << driver;  

	db.close(); 
}
bool DataBase::Db_Init()
{	bool b = false ;
	QMutex mutex;
	QMutexLocker locker(&mutex);
	if (m_database !=NULL)
	  b =  db.open(); 	
	return b;
	//return false;
}
void DataBase::Db_UnInit()
{
	QMutex mutex;
	QMutexLocker locker(&mutex);
	db.close(); 
}
//查找所有台站
bool DataBase::GetALLTower(QList<Tower> &list_tower)
{
    if (Db_Init()) {
        QSqlQuery query(db);
        query.exec("SELECT * FROM Tower");
        //尝试列出  表的所有记录
        while (query.next()) {
            Tower tower;
            tower.TowerID =query.value(0).toInt();
            tower.TowerStatus =e_DefaultStatus(query.value(1).toInt());
            tower.TowerName =query.value(2).toString();
            tower.Longitude =query.value(3).toString();
            tower.Latitude =query.value(4).toString();
            tower.Address =query.value(5).toString();
            list_tower.append(tower);
        }
		Db_UnInit();
        return true;
    }
    return false;
}

bool DataBase::GetTowerByName(QString towrName ,Tower &tower)
{
	if (Db_Init()) {
		QSqlQuery query(db);
		QString data_sql = QString("SELECT * FROM Tower where TowerName= %1").arg(towrName) ;
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			tower.TowerID =query.value(0).toInt();
			tower.TowerStatus =e_DefaultStatus(query.value(1).toInt());
			tower.TowerName =query.value(2).toString();
			tower.Longitude =query.value(3).toString();
			tower.Latitude =query.value(4).toString();
			tower.Address =query.value(5).toString();
		}
		Db_UnInit();
		return true;
	}
	return false;
}

bool DataBase::GetTowerByID( int towerid, Tower &tower )
{
	if (Db_Init()) {
		QSqlQuery query(db);
		QString data_sql = QString("SELECT * FROM Tower where TowerID= %1").arg(towerid) ;
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			tower.TowerID =query.value(0).toInt();
			tower.TowerStatus =e_DefaultStatus(query.value(1).toInt());
			tower.TowerName =query.value(2).toString();
			tower.Longitude =query.value(3).toString();
			tower.Latitude =query.value(4).toString();
			tower.Address =query.value(5).toString();
		}
		Db_UnInit();
		return true;
	}
	return false;

}

bool DataBase::GetTowerByWhere(QList<Tower> &list_tower,QString strwhere)
{
	if (Db_Init()) {
		QSqlQuery query(db);
		QString data_sql = QString("SELECT * FROM Tower where %1").arg(strwhere) ;
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			Tower tower;
			tower.TowerID =query.value(0).toInt();
			tower.TowerStatus =e_DefaultStatus(query.value(1).toInt());
			tower.TowerName =query.value(2).toString();
			tower.Longitude =query.value(3).toString();
			tower.Latitude =query.value(4).toString();
			tower.Address =query.value(5).toString();
			list_tower.append(tower);
		}
		Db_UnInit();
		return true;
	}
	return false;
}
//根据台站状态进行查询
bool DataBase::GetTowerByStatus(e_DefaultStatus e_Status,QList<Tower> &list_tower)
{
    if (Db_Init()) {
        QString data_sql = QString("SELECT * FROM Tower  where TowerStatus = '%1'").arg(int(e_Status)) ;
        QSqlQuery query(db);
        query.exec(data_sql);
        //尝试列出  表的所有记录
        while (query.next()) {
            Tower tower;
            tower.TowerID =query.value(0).toInt();
            tower.TowerStatus =e_DefaultStatus(query.value(1).toInt());
            tower.TowerName =query.value(2).toString();
            tower.Longitude =query.value(3).toString();
            tower.Latitude =query.value(4).toString();
            tower.Address =query.value(5).toString();
            list_tower.append(tower);
        }
		Db_UnInit();
        return true;
    }
    return false;
}
bool DataBase::GetALLTowerFrequency(QList<TowerFrequency> &list_towerfrequency)
{
    if (Db_Init()) {
        QString data_sql = "SELECT * FROM TowerFrequency order by TowerID";
        QSqlQuery query(db);
        query.exec(data_sql);
        //尝试列出  表的所有记录
        while (query.next()) {
            TowerFrequency towerfrequency;
            towerfrequency.FrequencyID =query.value(0).toInt();
            towerfrequency.TowerID =query.value(1).toInt();
            towerfrequency.IsEnable =query.value(2).toBool();
            towerfrequency.Frequency =query.value(3).toString();
            towerfrequency.FrequencyType = e_FrequencyType(query.value(4).toInt());
            towerfrequency.FrequencyUnits =e_FrequencyUnits(query.value(5).toInt());
            towerfrequency.FrequencyStatus =e_DefaultStatus(query.value(6).toInt());
            list_towerfrequency.append(towerfrequency);
        }
		Db_UnInit();
        return true;
    }
    return false;
}
bool  DataBase::GetFrequencyByTowerID(int TowerID,e_FrequencyType e_frequencytype,QList<TowerFrequency> &list_towerfrequency)
{
    if (Db_Init()) {
        QString data_sql = QString("SELECT * FROM TowerFrequency where TowerID = '%1' and FrequencyType = '%2'").arg(int(TowerID)).arg(int(e_frequencytype)) ;
        QSqlQuery query(db);
        query.exec(data_sql);
        //尝试列出  表的所有记录
        while (query.next()) {
            TowerFrequency towerfrequency;
            towerfrequency.FrequencyID =query.value(0).toInt();
            towerfrequency.TowerID =query.value(1).toInt();
            towerfrequency.IsEnable =query.value(2).toBool();
            towerfrequency.Frequency =query.value(3).toString();
			towerfrequency.FrequencyType = e_FrequencyType(query.value(4).toInt());
			towerfrequency.FrequencyUnits =e_FrequencyUnits(query.value(5).toInt());
			towerfrequency.FrequencyStatus =e_DefaultStatus(query.value(6).toInt());
            list_towerfrequency.append(towerfrequency);
        }
		Db_UnInit();
        return true;
    }
    return false;
}


bool DataBase::GetFrequencyByTowerID( int TowerID,e_FrequencyType e_frequencytype,e_DefaultStatus e_defaultstatus, QList<TowerFrequency> &list_towerfrequency )
{
	if (Db_Init()) {
		QString data_sql = QString("SELECT * FROM TowerFrequency where TowerID = '%1' and FrequencyType = '%2' and FrequencyStatus ='%3' ").arg(int(TowerID)).arg(int(e_frequencytype)).arg(int(e_defaultstatus)) ;
		QSqlQuery query(db);
		query.exec(data_sql);
		//尝试列出  表的所有记录lkpko
		while (query.next()) {
			TowerFrequency towerfrequency;
			towerfrequency.FrequencyID =query.value(0).toInt();
			towerfrequency.TowerID =query.value(1).toInt();
			towerfrequency.IsEnable =query.value(2).toBool();
			towerfrequency.Frequency =query.value(3).toString();
			towerfrequency.FrequencyType = e_FrequencyType(query.value(4).toInt());
			towerfrequency.FrequencyUnits =e_FrequencyUnits(query.value(5).toInt());
			towerfrequency.FrequencyStatus =e_DefaultStatus(query.value(6).toInt());
			list_towerfrequency.append(towerfrequency);
		}
		Db_UnInit();
		return true;
	}
	return false;
}

bool  DataBase::GetFrequencyByTowerID(int TowerID,QList<TowerFrequency> &list_towerfrequency)
{
	if (Db_Init()) {
		QString data_sql = QString("SELECT * FROM TowerFrequency where TowerID = '%1'").arg(int(TowerID));
		QSqlQuery query(db);
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			TowerFrequency towerfrequency;
			towerfrequency.FrequencyID =query.value(0).toInt();
			towerfrequency.TowerID =query.value(1).toInt();
			towerfrequency.IsEnable =query.value(2).toBool();
			towerfrequency.Frequency =query.value(3).toString();
			towerfrequency.FrequencyType = e_FrequencyType(query.value(4).toInt());
			towerfrequency.FrequencyUnits =e_FrequencyUnits(query.value(5).toInt());
			towerfrequency.FrequencyStatus =e_DefaultStatus(query.value(6).toInt());
			list_towerfrequency.append(towerfrequency);
		}
		Db_UnInit();
		return true;
	}
	return false;
}
bool  DataBase::GetFrequencyByEnable(bool IsEnable, int Count,QList<TowerFrequency> &list_towerfrequency)
{
    if (Db_Init()) {
        QString data_sql = QString("SELECT  * FROM TowerFrequency where IsEnable = %1 order by FrequencyID limit  0,%2").arg(bool(IsEnable)).arg(Count) ;
        QSqlQuery query(db);
        query.exec(data_sql);
        //尝试列出  表的所有记录
        while (query.next()) {
            TowerFrequency towerfrequency;
            towerfrequency.FrequencyID =query.value(0).toInt();
            towerfrequency.TowerID =query.value(1).toInt();
            towerfrequency.IsEnable =query.value(2).toBool();
            towerfrequency.Frequency =query.value(3).toString();
			towerfrequency.FrequencyType = e_FrequencyType(query.value(4).toInt());
			towerfrequency.FrequencyUnits =e_FrequencyUnits(query.value(5).toInt());
			towerfrequency.FrequencyStatus =e_DefaultStatus(query.value(6).toInt());
            list_towerfrequency.append(towerfrequency);
        }
		Db_UnInit();
        return true;
    }
    return false;
}
bool DataBase::GetRandomKey( QString Frequency,float Radius, QList<RandomKey> &list_randomkey,e_FrequencyType efrequencytype )
{
	if (Db_Init()) {
		QString data_sql = QString("SELECT  * FROM RandomKey where Frequency = %1 and FrequencyType =%2 and Radius ='%3'").arg(Frequency).arg(QString::number(int(efrequencytype))).arg(QString::number(Radius,'f',6)) ;
		QSqlQuery query(db);
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			RandomKey randomkey ;
			randomkey.RandomID =query.value(0).toInt();
			randomkey.Frequency =query.value(1).toString();
			randomkey.FrequencyType =query.value(2).toInt();
			randomkey.Radius =query.value(3).toFloat();
			randomkey.RandomValue = query.value(4).toFloat();
			list_randomkey.append(randomkey);
		}
		Db_UnInit();
		return true;
	}
	return false;
}

bool DataBase::GetMonitoring( QStringList s_list, QList<Monitoring> &list_monitoring, e_SearchType e_serchtype)
{

	if (Db_Init())
	{
		QString data_sql ;
		//导出原始数据
		if(e_serchtype == e_SearchType::e_SearchDatadownLoad)
		{
			data_sql = QString("SELECT  * FROM Monitoring where TowerID = '%1' and Time >= '%2' and Time <= '%3' and  Longitude <>'0.000000' and Latitude <>'0.000000'").arg(s_list.at(0).toInt()).arg(s_list.at(2)).arg(s_list.at(3));
		}else
		{
			if (s_list.count() == 5)
				data_sql = QString("SELECT  * FROM Monitoring where TowerID = %1 and Frequency =%2 and Time >= '%3' and Time <= '%4' ").arg(s_list.at(0).toInt()).arg(s_list.at(1)).arg(s_list.at(2)).arg(s_list.at(3));
			else if (s_list.count() == 8)
				data_sql = QString("SELECT  * FROM Monitoring where TowerID = %1 and Frequency =%2 and Time >= '%3' and Time <= '%4' and %5 >= '%6' and %5 <= '%7' ").arg(s_list.at(0).toInt()).arg(s_list.at(1)).arg(s_list.at(2)).arg(s_list.at(3)).arg(s_list.at(5)).arg(s_list.at(6)).arg(s_list.at(7));
		}

		
		QSqlQuery query(db);
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			Monitoring monitoring;
			bool OK =true;
			monitoring.MonitoringID =query.value(0).toInt();
			monitoring.Frequency =query.value(1).toString();
			monitoring.TowerID =query.value(2).toInt();
			monitoring.FrequencyType =query.value(3).toInt();

			QString tempT = query.value(4).toString();
			int iIndex = tempT.indexOf(':') ;
			QString sHour = tempT.mid(iIndex-2 , 2).simplified() ;
			if(sHour.toInt() < 10)
				//sHour = QString(" 0")+sHour ;
				sHour.replace(0,1,"0") ;

			tempT.replace(iIndex-2 , 2,sHour) ;

			//qDebug()<<"*****************"<<sHour<<"xxxxx"<<tempT ;
			//monitoring.Time =QDateTime::fromString(query.value(4).toString(), "yyyy-MM-dd hh:mm:ss");
			monitoring.Time =QDateTime::fromString(tempT, "yyyy-MM-dd hh:mm:ss");
			monitoring.Longitude =query.value(5).toFloat(&OK);
			monitoring.Latitude =query.value(6).toFloat(&OK);
			monitoring.Altitude =query.value(7).toFloat(&OK);
			monitoring.FieldStrength =query.value(8).toFloat(&OK);
			monitoring.SNR =query.value(9).toString();
			monitoring.Distance =query.value(10).toFloat(&OK);
			monitoring.Angle =query.value(11).toString();
			monitoring.CarrierMod =query.value(12).toString();
			monitoring.StartBtiMapMod =query.value(13).toString();
			monitoring.GI =query.value(14).toString(); 
			monitoring.FEC =query.value(15).toString(); 
			monitoring.TI =query.value(16).toString();
			monitoring.BER =query.value(17).toString(); 
			monitoring.MER =query.value(18).toString();
			monitoring.Speed =query.value(19).toFloat(&OK);
			list_monitoring.append(monitoring);
		}
		Db_UnInit();
		return true;
	}
	Db_UnInit();
	return false;
}
QSqlTableModel* DataBase::GetMonitoringModel( QStringList s_list )
{
	Db_Init();
	QSqlTableModel* model =new QSqlTableModel(0,db);
	model->setTable("Monitoring");
	model->setHeaderData(0,Qt::Horizontal,QObject::tr("MonitoringID"));
	model->setHeaderData(1,Qt::Horizontal,QObject::tr("Frequency"));
	model->setHeaderData(2,Qt::Horizontal,QObject::tr("TowerID"));
	model->setHeaderData(3,Qt::Horizontal,QObject::tr("FrequencyType"));
	model->setHeaderData(4,Qt::Horizontal,QObject::tr("Time"));
	model->setHeaderData(5,Qt::Horizontal,QObject::tr("Longitude"));//5
	model->setHeaderData(6,Qt::Horizontal,QObject::tr("Latitude"));//6
	model->setHeaderData(7,Qt::Horizontal,QObject::tr("Altitude"));
	model->setHeaderData(8,Qt::Horizontal,QObject::tr("FieldStrength"));//7
	model->setHeaderData(9,Qt::Horizontal,QObject::tr("SNR"));
	model->setHeaderData(10,Qt::Horizontal,QObject::tr("Distance"));
	model->setHeaderData(11,Qt::Horizontal,QObject::tr("Angle"));
	model->setHeaderData(12,Qt::Horizontal,QObject::tr("CarrierMod"));
	model->setHeaderData(13,Qt::Horizontal,QObject::tr("StartBtiMapMod"));
	model->setHeaderData(14,Qt::Horizontal,QObject::tr("GI"));
	model->setHeaderData(15,Qt::Horizontal,QObject::tr("FEC"));
	model->setHeaderData(16,Qt::Horizontal,QObject::tr("TI"));
	model->setHeaderData(17,Qt::Horizontal,QObject::tr("BER"));
	model->setHeaderData(18,Qt::Horizontal,QObject::tr("MER"));
	model->setHeaderData(19,Qt::Horizontal,QObject::tr("Speed"));
	QString data_where = QString(" TowerID = '%1' and Time >= '%2' and Time <= '%3' and  Longitude <>'0.000000' and Latitude <>'0.000000'").arg(s_list.at(0).toInt()).arg(s_list.at(2)).arg(s_list.at(3));
	model->setFilter(data_where);
	model->select();
	while(model->canFetchMore())
	{
		model->fetchMore();
	}
	Db_UnInit();
	return model;
}


bool DataBase::UpdateFrequencyEnable( int  i_frequencyId,int b_isEnable )
{
	if (Db_Init()&&i_frequencyId >0 ) {
		QSqlQuery query(db);
		query.prepare("update TowerFrequency set IsEnable=? where FrequencyID =?");
		query.addBindValue(b_isEnable);
		query.addBindValue(i_frequencyId);
		
		bool falg =query.exec();
		Db_UnInit();
		return falg;
	}
	Db_UnInit();
	return false;

}
bool DataBase::UpdateColorEnable( int i_colorId,int b_isEnable )
{
	if (Db_Init()&&i_colorId >0 ) {
		QSqlQuery query(db);
		query.prepare("update FieldStrengthColor set IsEnable=? where ColorID =?");
		query.addBindValue(b_isEnable);
		query.addBindValue(i_colorId);
		bool falg =query.exec();
		Db_UnInit();
		return falg;
	}
	Db_UnInit();
	return false;
}


bool DataBase::GetALLColor( QList<FieldStrengthColor> &list_fieldstrengthcolor )
{
    if (Db_Init()) {
        QString data_sql = "SELECT * FROM FieldStrengthColor" ;
        QSqlQuery query(db);
        query.exec(data_sql);
        //尝试列出  表的所有记录
        while (query.next()) {
            FieldStrengthColor item;
            item.ColorID =query.value(0).toInt();
            item.IsEnable=query.value(1).toBool();
            item.FieldStrengthStart =query.value(2).toInt();
            item.FieldStrengthEnd =query.value(3).toInt();
			item.ColorType =e_ColorType(query.value(4).toInt());
            item.ColorValue=query.value(5).toString();
            list_fieldstrengthcolor.append(item);
        }
		
		Db_UnInit();
		return true;
    }
    return false;
}
bool DataBase::GetColorByType( e_ColorType e_color, QList<FieldStrengthColor> &list_fieldstrengthcolor )
{
	if (Db_Init()) {
		QString data_sql = QString("SELECT * FROM FieldStrengthColor where  ColorType =%1 order by  FieldStrengthStart" ).arg(int(e_color));
		QSqlQuery query(db);
		query.exec(data_sql);
		//尝试列出  表的所有记录
		while (query.next()) {
			FieldStrengthColor item;
			item.ColorID =query.value(0).toInt();
			item.IsEnable=query.value(1).toBool();
			item.FieldStrengthStart =query.value(2).toInt();
			item.FieldStrengthEnd =query.value(3).toInt();
			item.ColorType =e_ColorType(query.value(4).toInt());
			item.ColorValue=query.value(5).toString();
			list_fieldstrengthcolor.append(item);
		}
		Db_UnInit();
		return true;
	}
	return false;
}

bool DataBase::GetColorByEnable(e_ColorType e_color, bool IsEnable,QList<FieldStrengthColor> &list_fieldstrengthcolor )
{
    if (Db_Init()) {
        QString data_sql = QString("SELECT * FROM FieldStrengthColor where IsEnable = %1 and ColorType =%2 order by  FieldStrengthStart" ).arg(bool(IsEnable)).arg(int(e_color)) ;
        QSqlQuery query(db);
        query.exec(data_sql);
        //尝试列出  表的所有记录
        while (query.next()) {
            FieldStrengthColor item;
            item.ColorID =query.value(0).toInt();
            item.IsEnable=query.value(1).toBool();
            item.FieldStrengthStart =query.value(2).toInt();
            item.FieldStrengthEnd =query.value(3).toInt();
			item.ColorType =e_ColorType(query.value(4).toInt());
			item.ColorValue=query.value(5).toString();
            list_fieldstrengthcolor.append(item);
        }
		Db_UnInit();
        return true;
    }
    return false;

}
bool DataBase::InsertTower( Tower *tower )
{
    if (Db_Init()&&tower != NULL) {
        QSqlQuery query(db);
        query.prepare("insert into Tower (TowerStatus , TowerName ,Longitude ,Latitude,Address) values(? , ?, ?, ?,?)");
        query.bindValue(0,tower->TowerStatus);
        query.bindValue(1, tower->TowerName);
        query.bindValue(2, tower->Longitude);
        query.bindValue(3, tower->Latitude);
        query.bindValue(4, tower->Address);
		bool falg =query.exec();
		Db_UnInit();
		return falg;
    }
    return false;
}

bool DataBase::InsertTowerFrequency( TowerFrequency *towerfrequency )
{
    if (Db_Init()&&towerfrequency != NULL) {
        QSqlQuery query(db);
        query.prepare("insert into TowerFrequency (TowerID , IsEnable ,Frequency ,FrequencyType,FrequencyUnits,FrequencyStatus) values(?,?,?,?,?,?)");
        query.bindValue(0,towerfrequency->TowerID);
        query.bindValue(1, towerfrequency->IsEnable);
        query.bindValue(2, towerfrequency->Frequency);
        query.bindValue(3, towerfrequency->FrequencyType);
        query.bindValue(4, towerfrequency->FrequencyUnits);
        query.bindValue(5, towerfrequency->FrequencyStatus);
		bool falg =query.exec();
		Db_UnInit();
		return falg;
    }
    return false;
}
bool DataBase::InsertMonitoringData( Monitoring* monitoring )
{
	if (Db_Init()&&monitoring != NULL) {
		QSqlQuery query(db);
		query.prepare("insert into Monitoring (Frequency,TowerID ,FrequencyType ,Time,Longitude,Latitude,Altitude,FieldStrength,SNR,Distance,Angle,CarrierMod,StartBtiMapMod,GI,FEC,TI,BER,MER,Speed) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
		query.bindValue(0,monitoring->Frequency);
		query.bindValue(1, monitoring->TowerID);
		query.bindValue(2, monitoring->FrequencyType);
		//query.bindValue(3, monitoring->Time.toString("yyyy-MM-dd H:mm:ss"));
		query.bindValue(3, monitoring->Time.toString("yyyy-MM-dd hh:mm:ss"));
		query.bindValue(4, QString::number(monitoring->Longitude,'f',6));
		query.bindValue(5, QString::number(monitoring->Latitude,'f',6));
		query.bindValue(6, monitoring->Altitude);
		query.bindValue(7, monitoring->FieldStrength);
		query.bindValue(8, monitoring->SNR);
		query.bindValue(9, monitoring->Distance);
		query.bindValue(10, monitoring->Angle);
		query.bindValue(11, monitoring->CarrierMod);
		query.bindValue(12, monitoring->StartBtiMapMod);
		query.bindValue(13, monitoring->GI);
		query.bindValue(14, monitoring->FEC);
		query.bindValue(15, monitoring->TI);
		query.bindValue(16, monitoring->BER);
		query.bindValue(17, monitoring->MER);
		query.bindValue(18, monitoring->Speed);
		bool falg =query.exec();
		Db_UnInit();
		return falg;
	}
	return false;
}


bool DataBase::InsertMonitoringByLoad(Monitoring* monitoring)
{
	if (Db_Init()&&monitoring != NULL) 
	{
		QSqlQuery query(db);
		QString dateTime = monitoring->Time.toString("yyyy-MM-dd hh:mm:ss");
		//QString dateTime =QString("2016-03-22 14:00:22") ;
		//qDebug()<<dateTime;
		QString s_sql = QString("SELECT * FROM Monitoring WHERE Frequency = '%1' AND TowerID = '%2' AND Time = '%3'")
			.arg(monitoring->Frequency).arg(monitoring->TowerID).arg(dateTime) ;
		bool flag = query.exec(s_sql) ;
		
		if(query.next())
		{
			Db_UnInit();
			return false ;
		}

		Db_UnInit();

		return InsertMonitoringData(monitoring) ;
	}
}



bool DataBase::InsertColor( FieldStrengthColor *color )
{
    if (Db_Init()&&color != NULL) {
        QSqlQuery query(db);
        query.prepare("insert into FieldStrengthColor (IsEnable , FieldStrengthStart ,FieldStrengthEnd ,ColorType,ColorValue) values(?,?,?,?,?)");
        query.bindValue(0, color->IsEnable);
        query.bindValue(1, color->FieldStrengthStart);
        query.bindValue(2, color->FieldStrengthEnd);
		query.bindValue(3, color->ColorType);
        query.bindValue(4, color->ColorValue);

		bool falg =query.exec();
		Db_UnInit();
		return falg;
    }
    return false;
}

bool DataBase::InsertRandomKey( RandomKey *key )
{
	if (Db_Init()&&key != NULL) {
		QSqlQuery query(db);
		query.prepare("insert into RandomKey (Frequency , FrequencyType ,Radius ,RandomValue) values(?, ?, ?,?)");
		query.bindValue(0, key->Frequency);
		query.bindValue(1, key->FrequencyType);
		query.bindValue(2, QString::number(key->Radius,'f',6));
		query.bindValue(3, QString::number(key->RandomValue,'f',6));
		bool falg =query.exec();
		Db_UnInit();
		return falg;
	}
	return false;
}
bool DataBase::DeletTowerByTowerID(int towerid)
{
	if (Db_Init()&&towerid !=NULL&& towerid >0)
	{
		QString data_sql = QString("Delete  FROM Tower where TowerID = %1").arg(towerid) ;
		QSqlQuery query(db);
		bool falg =query.exec(data_sql);
		Db_UnInit();
		return falg;
	}
	return false;
}


bool DataBase::DeletFrequencyByID( int frequencyid )
{
	if (Db_Init()&&frequencyid !=NULL&& frequencyid >0)
	{
		QString data_sql = QString("Delete  FROM TowerFrequency where FrequencyID = %1").arg(frequencyid) ;
		QSqlQuery query(db);
		bool falg =query.exec(data_sql);
		Db_UnInit();
		return falg;
	}
	return false;
}

bool DataBase::DeleteColorByID( int colorid )
{
	if (Db_Init()&&colorid !=NULL&& colorid >0)
	{
		QString data_sql = QString("Delete  FROM FieldStrengthColor where ColorID = %1").arg(colorid) ;
		QSqlQuery query(db);
		bool falg =query.exec(data_sql);
		Db_UnInit();
		return falg;
	}
	return false;
}

bool DataBase::UpdateTower( Tower * tower )
{
	if (Db_Init()&&tower != NULL) {
		QSqlQuery query(db);
		query.prepare("update Tower set TowerStatus=?, TowerName=?,Longitude=?,Latitude=?,Address=? where TowerID =?");
		query.addBindValue(tower->TowerStatus);
		query.addBindValue(tower->TowerName);
		query.addBindValue(tower->Longitude);
		query.addBindValue(tower->Latitude);
		query.addBindValue(tower->Address);
		query.addBindValue(tower->TowerID);
		bool falg =query.exec();
		Db_UnInit();
		return falg;
	}
	return false;

}
bool DataBase::UpdateFrequency( TowerFrequency*towerfrequency )
{
	if (Db_Init()&&towerfrequency != NULL) {
		QSqlQuery query(db);
		query.prepare("update TowerFrequency set TowerID=?, IsEnable=?,Frequency=?,FrequencyType=?,FrequencyUnits=?,FrequencyStatus =? where FrequencyID =?");
		query.addBindValue(towerfrequency->TowerID);
		query.addBindValue(towerfrequency->IsEnable);
		query.addBindValue(towerfrequency->Frequency);
		query.addBindValue(towerfrequency->FrequencyType);
		query.addBindValue(towerfrequency->FrequencyUnits);
		query.addBindValue(towerfrequency->FrequencyStatus);
		query.addBindValue(towerfrequency->FrequencyID);

		bool falg =query.exec();
		Db_UnInit();
		return falg;

	}
	return false;


	//query.prepare("insert into TowerFrequency (TowerID , IsEnable ,Frequency ,FrequencyType,FrequencyUnits,FrequencyStatus) values(?,?,?,?,?,?)");
	
}
bool DataBase::UpdateColor( FieldStrengthColor * fieldstrengthcolor )
{
	if (Db_Init()&&fieldstrengthcolor != NULL) {
		QSqlQuery query(db);
		query.prepare("update FieldStrengthColor set ColorValue=? where ColorID =?");
		query.addBindValue(fieldstrengthcolor->ColorValue);
		query.addBindValue(fieldstrengthcolor->ColorID);
		bool falg =query.exec();
		Db_UnInit();
		return falg;
	}
	return false;
}
QString DataBase::GetFrequencyUnitsByID( e_FrequencyType e )
{
	int  i_listLength = listFrequencyUnits.count();
	if (i_listLength>0&& int(e)>=0)
	{
		for (int i=0;i<i_listLength;i++)
		{
			QString ValueName =listFrequencyUnits.at(i);
			if (i == e)
			{
				return ValueName;
				break;
			}
		}
	}
	return "";

}

QString DataBase::GetFrequencyTypeByID( e_FrequencyType e )
{
	int  i_listLength =listFrequencyType.count();
	if (i_listLength>0&&int(e)>=0)
	{
		for (int i=0;i<i_listLength;i++)
		{
			QString ValueName =listFrequencyType.at(i);
			if (i == e)
			{
				return ValueName;
				break;
			}
		}
	}
	return "";
}

int DataBase::GetFrequencyTypeIDByName( QString s_name )
{

	int  i_listLength =listFrequencyType.count();
	if (i_listLength>0 && s_name !="")
	{
		for (int i=0;i<i_listLength;i++)
		{
			QString ValueName =listFrequencyType.at(i);
			if (s_name == ValueName)
			{
				return i;
				break;
			}
		}
	}
}

int DataBase::GetColorTypeIDByName( QString s_name )
{

	int  i_listLength =listColorType.count();
	if (i_listLength>0 && s_name !="")
	{
		for (int i=0;i<i_listLength;i++)
		{
			QString ValueName =listColorType.at(i);
			if (s_name == ValueName)
			{
				return i;
				break;
			}
		}
	}
}
QString DataBase::GetColorNameTypeID( e_ColorType ecolortype )
{

	int  i_listLength =listColorType.count();
	if (i_listLength>0 && int(ecolortype)>=0)
	{
		for (int i=0;i<i_listLength;i++)
		{
			QString ValueName =listColorType.at(i);
			if (i == ecolortype)
			{
				return ValueName;
				break;
			}
		}
	}
}



bool DataBase::GetDataTableInfo(QString tableName , QStringList &s_Info)
{
	if (!Db_Init())
		return false ;

	QSqlQuery query(db);  
	QString str = "PRAGMA table_info(" + tableName + ")";  

	query.prepare(str);  
	if (query.exec())  
	{  
		while (query.next())  
		{ 
			QString sTemp =	query.value(1).toString() ;
			s_Info.append(sTemp) ;
		}
	}else
	{
		qDebug()<<"DataBase::GetDataTableInfo(QString tableName , QStringList &s_Info)" ;

		Db_UnInit();
		return false ;
	}

	Db_UnInit();
	return true ;
}


