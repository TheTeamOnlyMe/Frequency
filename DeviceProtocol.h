#ifndef DeviceProtocol_H
#define DeviceProtocol_H
#include "QByteArray"
#include <QObject>
#include "database.h"
#include "SysConfig.h"
#include "QTcpSocket"
#include <QTimer>
#include <QtDebug>

class DeviceProtocol: public QObject
{
	Q_OBJECT
public:
	char _head;
	char _zero;
	char _productID;			//��Ʒ���к�
	char _end;					//β		

private:
	QTcpSocket *m_tcpSocket;
	SocketInfo socketinfo;
	SysConfig *sysConfig;
	QTimer * qtimer;
	QByteArray m_recvData;
	QByteArray m_buffer;
public:
	DeviceProtocol	();
	~DeviceProtocol	();
	bool init();
	//************************************
	// Method:    connectToHost
	// FullName:  DeviceProtocol::connectToHost
	// Access:    public 
	// Returns:   void
	// Qualifier: ��������
	//************************************
	void connectToHost();
	//************************************
	// Method:    switchFrequency
	// FullName:  DeviceProtocol::switchFrequency
	// Access:    public 
	// Returns:   void
	// Qualifier: �л�ָ��
	// Parameter: e_FrequencyType efrequencytype
	// Parameter: float Frequency
	//************************************
	void switchFrequency(e_FrequencyType efrequencytype,float Frequency,bool b_isloop =false);
	//************************************
	// Method:    searchCommand
	// FullName:  DeviceProtocol::searchCommand
	// Access:    public 
	// Returns:   void
	// Qualifier:��ѯָ��
	//************************************
	void searchCommand();
	//************************************
	// Method:    sweepFrequency
	// FullName:  DeviceProtocol::sweepFrequency
	// Access:    public 
	// Returns:   void
	// Qualifier: ɨƵ
	// Parameter: e_FrequencyType efrequencytype
	// Parameter: float f_frequencyStart
	// Parameter: float f_frequencyEnd
	//************************************
	void sweepFrequency(e_FrequencyType  efrequencytype,float f_frequencyStart = 0,float f_frequencyEnd = 0);
	//************************************
	// Method:    controlCommand
	// FullName:  DeviceProtocol::controlCommand
	// Access:    public 
	// Returns:   void
	// Qualifier: ��������(�������������Ƶ��ɨƵ���Զ���Ƶ)
	// Parameter: e_Operation e_operation
	// Parameter: e_FrequencyType e_frequencytype
	//************************************
	void controlCommand(e_Operation e_operation,e_FrequencyType e_frequencytype = e_FrequencyType::e_FM);
	//************************************
	// Method:    xorByte
	// FullName:  DeviceProtocol::xorByte
	// Access:    public 
	// Returns:   QT_NAMESPACE::QByteArray
	// Qualifier: �����
	// Parameter: QByteArray inbyte
	//************************************
	QByteArray xorByte(QByteArray inbyte);
	//************************************
	// Method:    convertFrequency
	// FullName:  DeviceProtocol::convertFrequency
	// Access:    public 
	// Returns:   QT_NAMESPACE::QByteArray
	// Qualifier: ת��Ƶ��
	// Parameter: float Frequency
	// Parameter: e_FrequencyType e_frequencytype
	// Parameter: e_Operation e_operation
	//************************************
	QByteArray convertFrequency(float Frequency,e_FrequencyType e_frequencytype,e_Operation e_operation,bool b_isloop =false);
	//************************************
	// Method:    convertByteArray
	// FullName:  DeviceProtocol::convertByteArray
	// Access:    public 
	// Returns:   QByteArray
	// Qualifier:
	// Parameter: QByteArray bytearray
	//************************************
	QByteArray convertByteArray(QByteArray bytearray);
	//************************************
	// Method:    processData
	// FullName:  DeviceProtocol::processData
	// Access:    public 
	// Returns:   void
	// Qualifier: ��������
	// Parameter: QByteArray byteArray
	//************************************
	void processData(QByteArray byteArray);
	bool checkData(QByteArray byteArray);//��֤Э��
	void sendData(QByteArray byteArray);
	QByteArray heartSend;
	int i_heartcount;
	private slots:
		void slottcpRecData();
		void slottcpConnected();
		void slottcpDisConn();
		void slottimeout();

	signals:
		void signalerror(QString,QString);

		void signaldatarev(QByteArray byteArray,e_DataType e_datatype);//����ɨƵ���߶����ѯ����
	
};

#endif
