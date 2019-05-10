#ifndef _DATABASE_H
#define _DATABASE_H
#include <QtCore/QCoreApplication>  
#include <QSqlDatabase>	
#include <QSqlQuery>  
#include <QSqlError>  
#include <QSqlDriver>  
#include <qDebug>  
#include <QString>  
#include <QVector>  
#include <QMutex>
#include <QList>  
#include <QFile>  
#include <QDateTime>
#include <QSqlTableModel>	
#include <qhostaddress.h>

enum e_MediaStatus{
	Close =0,
	Play,
	MediaPause,
	Default,
};

enum e_FrequencyType {
	e_FM = 0,
	e_MW = 1,
	e_SW = 2,
	e_TV = 3,
	e_DTMB = 4,
	e_NONE
};

enum e_ColorType {
	e_Fre = 0,
	e_SNR = 1,
	e_MER = 2,
	e_LDPC = 3,
};

enum e_FrequencyCommand {
	e_Switch = 0,
	e_Sweep = 1
};
enum e_FrequencyUnits
{
	e_FMUnits = 0,
	e_SWUnits = 1,
	e_MWUnits = 2,
	e_TVUnits = 3,
	e_DTMBUnits = 4
};
enum e_Teststatus
{
	Start=0,
	Pause,
	Stop
};
enum e_DataType
{
	HEARTBEAT=0, //
	AUTOSEARCH,
	SEARCH,
	DISCONNECT,
	PLANISPHERE,
	Multianalysis,
	DTMBSEARCHSTATE


};
enum e_Palystatus
{
	VIDEO_PLAY=0,
	VIDEO_STOP,
	AUDIO_PALY,
	AUDIO_STOP
};
enum e_ControlType
{
	LEFT =0,
	RIGHT,
	UP,
	DOWN,
	PLAY,
	STOP,
	SERARH
};
enum e_SearchType
{
	e_SearchPoint =0,
	e_SearchCover =1,
	e_SearchDatadownLoad =2,
	e_SearchWroldLoad =3
};
enum e_Operation {

	SWITCH_FREQUENCY        =0,//切换频率
	SWITCH_MODE			    =1,//切换模式 
	AUTO_SERARH   		    =2,//自动搜台
	STOP_SERARH   		    =3,//停止搜台
	OPENVIDEO   		  	=4,//打开视频
	CLOSEVIDEO 		 	    =5,//关闭视频
	OPENAUDIO		  		=6,//打开音频
	CLOSEAUDIO	 		 	=7,//关闭音频
	CLOSEDEVICE	 		 	=8,//关闭设备
	STARTSWEEP      	    =9,//开始扫频
	STOPSWEEP      	     	=10,//停止扫频
	PAUSESWEEP				=11,//暂停扫频
	NEXTSWEEP				=12, //暂停扫频情况，下一步操作
	UPSWEEP					=13, //暂停扫频情况，上一步操作	
	GOSWEEP					=14,//暂停扫频情况下，继续扫频
	NEXTDTMB				=15, //数字电视下翻台
	UPDTMB					=16, //数字电视上翻台
	REDUCEAUDIO				=17, //音量减小
	RISEAUDIO				=18, //音量增大
	PLANI					=19, // 星座图
	MULTIANALYSIS			=20	//多经分析

};
enum e_DefaultStatus
{
	e_UnDefault = 0,
	e_Default = 1
	
};
struct TowerFrequency
{
	int FrequencyID;
	int	TowerID;
	int IsEnable;
	QString	Frequency; //频率值
	e_FrequencyType	FrequencyType; //频率类型
	e_FrequencyUnits FrequencyUnits;//频率单位
	e_DefaultStatus FrequencyStatus;//频率状态（是否为默认）
};
struct Tower
{
	int TowerID;
	e_DefaultStatus	TowerStatus;
	QString	TowerName; 
	QString Longitude; 
	QString Latitude;
	QString Address;
};
struct SocketInfo
{
	QHostAddress _addr;
	quint16 _port;
	bool isConnected;
};
struct Monitoring
{
	int MonitoringID;
	QString	Frequency;
	int TowerID;
	int	FrequencyType;		//记录类型
	QDateTime Time;			//记录时间
	float Longitude;			
	float Latitude;
	float Altitude;			//海拔
	float FieldStrength;	//场强
	QString SNR;			//信噪比
	float Distance;			//距离
	QString	Angle;			//方位角
	QString CarrierMod;		//载波模式
	QString	StartBtiMapMod;	//星位图模式
	QString GI;				//保护间隔
	QString	FEC;			//前向纠错
	QString TI;				//交织深度
	QString BER;			//LDPC误码率
	QString MER;			//调制误码率
	float Speed;			//速度
};
struct FieldStrengthColor {
    int	  ColorID;
    int   IsEnable;
    int   FieldStrengthStart;	//场强值开始
    int	  FieldStrengthEnd;		
	//场强值结束
	e_ColorType ColorType;
    QString ColorValue;			//记录类型
};
struct RandomKey
{
	int RandomID;
	QString Frequency;
	int	FrequencyType;	
	float Radius;			
	float RandomValue;
};
class DataBase
{
public: 
	static DataBase* GetInstance()
	{
		if ( m_database == NULL )  //判断是否第一次调用
			m_database = new DataBase();
		return m_database;
	}
	static void Release()    //必须，否则会导致内存泄露
	{
		if(NULL != m_database)
		{
			delete m_database;
			m_database = NULL;
		}
	}
	DataBase();
	~DataBase();

	QList<QString> listFrequencyUnits;
	QList<QString> listFrequencyType;
	QList<QString> listColorType;
private:
	static DataBase * m_database;
	QSqlDatabase db;
	bool bConnectStatus;

public:
	bool Db_Init();
	void Db_UnInit();
	bool GetALLTower(QList<Tower> &list_tower);
	bool GetTowerByID(int towerid, Tower &tower);
	bool GetTowerByName(QString towrName ,Tower &tower) ;
	bool GetTowerByStatus(e_DefaultStatus e_Status,QList<Tower> &list_tower);
	bool GetTowerByWhere(QList<Tower> &list_tower,QString strwhere);
	bool GetALLTowerFrequency(QList<TowerFrequency> &list_towerfrequency);
	bool GetFrequencyByTowerID(int TowerID,e_FrequencyType e_frequencytype, QList<TowerFrequency> &list_towerfrequency);
	bool GetFrequencyByTowerID(int TowerID,e_FrequencyType e_frequencytype,e_DefaultStatus e_defaultstatus, QList<TowerFrequency> &list_towerfrequency);
	bool GetFrequencyByTowerID(int TowerID,QList<TowerFrequency> &list_towerfrequency);
	bool GetFrequencyByEnable(bool IsEnable, int Count, QList<TowerFrequency> &list_towerfrequency);
	bool GetMonitoring(QStringList s_list,  QList<Monitoring> &list_monitoring , e_SearchType e_serchtype=e_SearchWroldLoad);
    QSqlTableModel* GetMonitoringModel(QStringList s_list);
	bool GetALLColor(QList<FieldStrengthColor> &list_fieldstrengthcolor);
	bool GetColorByType(e_ColorType e_color, QList<FieldStrengthColor> &list_fieldstrengthcolor );
	bool GetColorByEnable(e_ColorType e_color,bool IsEnable,QList<FieldStrengthColor> &list_fieldstrengthcolor);
	bool GetRandomKey(QString Frequency,float Radius,QList<RandomKey> &list_randomkey,e_FrequencyType efrequencytype);
	bool InsertTower(Tower* tower);
	bool InsertTowerFrequency(TowerFrequency*towerfrequency);
	bool InsertColor(FieldStrengthColor *color);
	bool InsertRandomKey(RandomKey *key);
	bool InsertMonitoringData(Monitoring* monitoring);
	bool InsertMonitoringByLoad(Monitoring* monitoring) ;
	bool DeletTowerByTowerID(int towerid);
	bool DeletFrequencyByID(int frequencyid);
	bool DeleteColorByID(int colorid);
	bool UpdateTower(Tower * tower);
	//************************************
	// Method:    UpdateFrequency
	// FullName:  DataBase::UpdateFrequency
	// Access:    public 
	// Returns:   bool
	// Qualifier:更新台站频率信息 
	// Parameter: TowerFrequency * towerfrequency
	//************************************
	bool UpdateFrequency(TowerFrequency*towerfrequency);
	bool UpdateFrequencyEnable( int  i_frequencyId,int b_isEnable );
	bool UpdateColorEnable( int  i_colorId,int b_isEnable );
	bool UpdateColor(FieldStrengthColor * fieldstrengthcolor);

	QString GetFrequencyUnitsByID(e_FrequencyType e);
	QString GetFrequencyTypeByID(e_FrequencyType e);
	QString GetColorNameTypeID( e_ColorType ecolortype );
	int GetColorTypeIDByName( QString s_name );
	int GetFrequencyTypeIDByName(QString s_name);


	bool GetDataTableInfo(QString tableName , QStringList &s_Info) ;

	struct testValue{

		int i_frequencyvalue;
		int i_fieldstrengthvalue;
		int i_fieldstrengthvalueB;
		double d_frequencyvalue; //频率值
		double d_leftvoice;      //左声道
		double d_rightvoice;	 //右声道
		double d_cnr;			 //载噪比
		double d_frequencyoffset;//频偏	

		int i_carrierwaveM;	 //载波
		int i_starbitmap; //星位图(DTMB专有)
		int i_fec; //前向纠错(DTMB专有)
		int i_gi; //保护间隔(DTMB专有)
		int i_ti; //交织深度(DTMB专有)
		double d_ber; //比特误码率(DTMB专有)

		double d_longitude ; //经度
		double d_latitude ;  //纬度
		double d_distance;   //距离(距离默认台站)
		int i_altitude;	 //海拔
		int i_satellitenumber;

		double d_speed;		//速度

	};
};


#endif