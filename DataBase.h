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

	SWITCH_FREQUENCY        =0,//�л�Ƶ��
	SWITCH_MODE			    =1,//�л�ģʽ 
	AUTO_SERARH   		    =2,//�Զ���̨
	STOP_SERARH   		    =3,//ֹͣ��̨
	OPENVIDEO   		  	=4,//����Ƶ
	CLOSEVIDEO 		 	    =5,//�ر���Ƶ
	OPENAUDIO		  		=6,//����Ƶ
	CLOSEAUDIO	 		 	=7,//�ر���Ƶ
	CLOSEDEVICE	 		 	=8,//�ر��豸
	STARTSWEEP      	    =9,//��ʼɨƵ
	STOPSWEEP      	     	=10,//ֹͣɨƵ
	PAUSESWEEP				=11,//��ͣɨƵ
	NEXTSWEEP				=12, //��ͣɨƵ�������һ������
	UPSWEEP					=13, //��ͣɨƵ�������һ������	
	GOSWEEP					=14,//��ͣɨƵ����£�����ɨƵ
	NEXTDTMB				=15, //���ֵ����·�̨
	UPDTMB					=16, //���ֵ����Ϸ�̨
	REDUCEAUDIO				=17, //������С
	RISEAUDIO				=18, //��������
	PLANI					=19, // ����ͼ
	MULTIANALYSIS			=20	//�ྭ����

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
	QString	Frequency; //Ƶ��ֵ
	e_FrequencyType	FrequencyType; //Ƶ������
	e_FrequencyUnits FrequencyUnits;//Ƶ�ʵ�λ
	e_DefaultStatus FrequencyStatus;//Ƶ��״̬���Ƿ�ΪĬ�ϣ�
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
	int	FrequencyType;		//��¼����
	QDateTime Time;			//��¼ʱ��
	float Longitude;			
	float Latitude;
	float Altitude;			//����
	float FieldStrength;	//��ǿ
	QString SNR;			//�����
	float Distance;			//����
	QString	Angle;			//��λ��
	QString CarrierMod;		//�ز�ģʽ
	QString	StartBtiMapMod;	//��λͼģʽ
	QString GI;				//�������
	QString	FEC;			//ǰ�����
	QString TI;				//��֯���
	QString BER;			//LDPC������
	QString MER;			//����������
	float Speed;			//�ٶ�
};
struct FieldStrengthColor {
    int	  ColorID;
    int   IsEnable;
    int   FieldStrengthStart;	//��ǿֵ��ʼ
    int	  FieldStrengthEnd;		
	//��ǿֵ����
	e_ColorType ColorType;
    QString ColorValue;			//��¼����
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
		if ( m_database == NULL )  //�ж��Ƿ��һ�ε���
			m_database = new DataBase();
		return m_database;
	}
	static void Release()    //���룬����ᵼ���ڴ�й¶
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
	// Qualifier:����̨վƵ����Ϣ 
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
		double d_frequencyvalue; //Ƶ��ֵ
		double d_leftvoice;      //������
		double d_rightvoice;	 //������
		double d_cnr;			 //�����
		double d_frequencyoffset;//Ƶƫ	

		int i_carrierwaveM;	 //�ز�
		int i_starbitmap; //��λͼ(DTMBר��)
		int i_fec; //ǰ�����(DTMBר��)
		int i_gi; //�������(DTMBר��)
		int i_ti; //��֯���(DTMBר��)
		double d_ber; //����������(DTMBר��)

		double d_longitude ; //����
		double d_latitude ;  //γ��
		double d_distance;   //����(����Ĭ��̨վ)
		int i_altitude;	 //����
		int i_satellitenumber;

		double d_speed;		//�ٶ�

	};
};


#endif