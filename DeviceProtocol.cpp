#include "DeviceProtocol.h"

#define  MINSIZE 6
#define  AUTOSEARCHSIZE 12
#define  MAXSIZE 42
#define  HEARTSIZE 4
#define  PLANISPHERESIZE 2054
#define	 MULTIPATH  8//多经分析

DeviceProtocol::DeviceProtocol()

{
	m_tcpSocket =NULL;
	init();
	connectToHost();
	qtimer =new QTimer();
	connect(qtimer,SIGNAL(timeout()),this,SLOT(slottimeout()));
	qtimer->start(20000);
}
DeviceProtocol::~DeviceProtocol()
{
	sysConfig->Release();
	if (m_tcpSocket)
		delete m_tcpSocket,m_tcpSocket =NULL;
	if (qtimer !=NULL)
	{
		disconnect(qtimer,SIGNAL(timeout()),this,SLOT(slottimeout()));
		delete qtimer,qtimer =NULL;
	}
}
bool DeviceProtocol::init()
{
	sysConfig = SysConfig::GetInstance();
	_head =0xAA;_end =0x55;_zero =0x00;
	_productID =0x00;
	heartSend.append(_head);heartSend.append(0xF4);heartSend.append(0x04);heartSend.append(_end);	
	socketinfo._addr =QHostAddress(sysConfig->s_serverip);
	socketinfo._port =sysConfig->i_serverport;
	socketinfo.isConnected =false;
	i_heartcount =0;
	m_tcpSocket= new QTcpSocket(this);
	connect(m_tcpSocket,SIGNAL(connected()),this,SLOT(slottcpConnected()));
	connect(m_tcpSocket,SIGNAL(readyRead()),this,SLOT(slottcpRecData()));
	connect(m_tcpSocket,SIGNAL(disconnected()),this,SLOT(slottcpDisConn()));
	return true;

}
//查询频率
void DeviceProtocol::switchFrequency( e_FrequencyType efrequencytype,float Frequency,bool b_isloop )
{
	QByteArray byteCommand;
	byteCommand.append(_head);
	byteCommand.append(0x22);
	byteCommand.append(0x0a);
	byteCommand.append(_zero);
	switch (efrequencytype) {
	case e_FrequencyType::e_FM:
		byteCommand.append(0x01);
		break;
	case e_FrequencyType::e_MW:
		byteCommand.append(_zero);
		break;
	case e_FrequencyType::e_SW:
		byteCommand.append(0x02);
		break;
	case e_FrequencyType::e_TV:
		byteCommand.append(0x03);
		break;
	case e_FrequencyType::e_DTMB:
		byteCommand.append(0x05);
		break;
	default:
		break;
	}
	byteCommand.append(convertFrequency(Frequency,efrequencytype,e_Operation::SWITCH_FREQUENCY,b_isloop));
	byteCommand =xorByte(byteCommand);

	sendData(byteCommand);
	//一开始只需要切换一次频率。后多次查询
}


void DeviceProtocol::searchCommand()
{
	QByteArray byteCommand;
	byteCommand.append(_head);
	byteCommand.append(0x11);
	byteCommand.append(0x0a);
	byteCommand.append(_zero);
	byteCommand.append(_zero);
	byteCommand.append(_zero);
	byteCommand.append(_zero);
	byteCommand.append(_zero);
	byteCommand.append(0x1b);
	byteCommand.append(0x55);
	//qDebug() << "查询指令:" << byteCommand.toHex();
	sendData(byteCommand);
}
//扫频
void DeviceProtocol::sweepFrequency( e_FrequencyType efrequencytype,float f_frequencyStart,float f_frequencyEnd )
{
	QByteArray byteCommand;
	byteCommand.append(_head);
	byteCommand.append(0x44);
	byteCommand.append(0x0c);
	byteCommand.append(_zero);
	char FrequencyHex;
	switch (efrequencytype) {
	case e_FrequencyType::e_FM:
		byteCommand.append(0x21);
		break;
	case e_FrequencyType::e_MW:
		byteCommand.append(_zero);
		if (f_frequencyStart ==0&&f_frequencyEnd) 
			byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero);		
		else{
			byteCommand.append(convertFrequency(f_frequencyStart,efrequencytype,e_Operation::STARTSWEEP));
			byteCommand.append(0x03);
			byteCommand.append(convertFrequency(f_frequencyEnd,efrequencytype,e_Operation::STARTSWEEP));
		}
		break;
	case e_FrequencyType::e_SW:
		byteCommand.append(0x06);
		if (f_frequencyStart ==0&&f_frequencyEnd) 
			byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero);		
		else{
			byteCommand.append(convertFrequency(f_frequencyStart,efrequencytype,e_Operation::STARTSWEEP));
			byteCommand.append(0x05);
			byteCommand.append(convertFrequency(f_frequencyEnd,efrequencytype,e_Operation::STARTSWEEP));
		}
		break;
	case e_FrequencyType::e_TV:
		byteCommand.append(0x03);
		break;
	case e_FrequencyType::e_DTMB:
		byteCommand.append(0x05);
		break;
	default:
		break;
	}
	if (efrequencytype == e_FrequencyType::e_FM||efrequencytype ==e_FrequencyType::e_TV||efrequencytype ==e_FrequencyType::e_DTMB)
	{
		byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero),byteCommand.append(_zero);
	}
	byteCommand =xorByte(byteCommand);
	sendData(byteCommand);
	//qDebug() << "扫频指令:" << byteCommand.toHex();

}
//
//enum e_Operation {
//
//	SWITCH_FREQUENCY        =0,//切换频率
//	SWITCH_MODE			    =1,//切换模式 
//	AUTO_SERARH   		    =2,//自动搜台
//	STOP_SERARH   		    =3,//停止搜台
//	OPENVIDEO   		  	=4,//打开视频
//	CLOSEVIDEO 		 	    =5,//关闭视频
//	OPENAUDIO		  		=6,//打开音频
//	CLOSEAUDIO	 		 	=7,//关闭音频
//	CLOSEDEVICE	 		 	=8,//关闭设备
//	STARTSWEEP      	    =9,//开始扫频
//	STOPSWEEP      	     	=10,//停止扫频
//	PAUSESWEEP				=11,//暂停扫频
//	NEXTSWEEP				=12, //暂停扫频情况，下一步操作
//	UPSWEEP					=13, //暂停扫频情况，上一步操作	
//	GOSWEEP					=14,//暂停扫频情况下，继续扫频
//	NEXTDTMB				=15, //数字电视下翻台
//	UPDTMB					=16, //数字电视上翻台
//	REDUCEAUDIO				=17, //音量减小
//	RISEAUDIO				=18	 //音量增大
//
//};
void DeviceProtocol::controlCommand( e_Operation e_operation ,e_FrequencyType e_frequencytype )
{
	QByteArray byteCommand;
	byteCommand.append(_head);
	if (e_operation>= 9 && e_operation <= 14)
		byteCommand.append(0x55);
	else if (e_operation == 15 || e_operation == 16)
		byteCommand.append(0xF6);
	else if (e_operation== 17 || e_operation == 18)
		byteCommand.append(0xF4);
	else if (e_operation== 6 || e_operation == 7)
		byteCommand.append(0xF5);
	else if (e_operation== 2 || e_operation == 3)
		byteCommand.append(0xF3);
	else if (e_operation== 4 || e_operation == 5)
		byteCommand.append(0xF7);
	else if (e_operation== 19)
		byteCommand.append(0xF9);
	else if (e_operation== 20)
		byteCommand.append(0xF1);
	byteCommand.append(0x08);
	byteCommand.append(_zero);
	byteCommand.append(_zero);
	switch (e_operation) {
	case e_Operation::PAUSESWEEP:
		byteCommand.append(0x02);
		break;
	case e_Operation::STOPSWEEP:
		byteCommand.append(0x04);
		break;
	case e_Operation::NEXTSWEEP:
		byteCommand.append(0x03);
		break;
	case e_Operation::UPSWEEP:
		byteCommand.append(0x01);
		break;
	case e_Operation::GOSWEEP:
		byteCommand.append(0x05);
		break;
	case e_Operation::NEXTDTMB:
		byteCommand.append(_zero);
		break;
	case e_Operation::UPDTMB:
		byteCommand.append(0x01);
		break;
	case e_Operation::REDUCEAUDIO:
		byteCommand.append(_zero);
		break;
	case e_Operation::RISEAUDIO:
		byteCommand.append(0x01);
		break;
	case e_Operation::OPENAUDIO:
		byteCommand.append(0x01);
		break;
	case e_Operation::CLOSEAUDIO:
		byteCommand.append(_zero);
		break;

	case e_Operation::OPENVIDEO:
		byteCommand.append(0x01);
		break;
	case e_Operation::CLOSEVIDEO:
		byteCommand.append(_zero);
		break;

	case e_Operation::AUTO_SERARH:
		{
			switch (e_frequencytype) {
	case e_FrequencyType::e_FM:
		byteCommand.append(0x0A);
		break;
	case e_FrequencyType::e_MW:
		byteCommand.append(0x0c);
		break;
	case e_FrequencyType::e_SW:
		byteCommand.append(0x0e);
		break;
	case e_FrequencyType::e_TV:
		byteCommand.append(0x10);
		break;
	case e_FrequencyType::e_DTMB:
		byteCommand.append(0x11);
		break;
	default:
		break;
			}
			break;
		}

	case e_Operation::STOP_SERARH:
		byteCommand.append(0x12);
		break;
	case e_Operation::PLANI:
		byteCommand.append(_zero);
		break;
	case e_Operation::MULTIANALYSIS:
		byteCommand.append(_zero);
		break;
	}
	byteCommand =xorByte(byteCommand);

	sendData(byteCommand);
	//qDebug() << "控制指令:"<< byteCommand.toHex();
}

//去头取异或值
QByteArray  DeviceProtocol::xorByte(QByteArray inbyte)
{
	char c_byte = 0;
	int i;
	for (i = 1; i < inbyte.size(); i++)
		c_byte = c_byte ^ inbyte[i];
	inbyte.append(c_byte);
	inbyte.append(0x55);
	return inbyte;
}
QByteArray DeviceProtocol::convertFrequency(float Frequency,e_FrequencyType e_frequencytype,e_Operation e_operation,bool b_isloop)
{
	QByteArray abyte;

	int i_Frequency =(int)Frequency;
	if (e_operation==e_Operation::SWITCH_FREQUENCY)
	{
		abyte.resize(3);
		if (e_frequencytype == e_FrequencyType::e_TV||e_frequencytype == e_FrequencyType::e_DTMB)
		{
			if (!b_isloop)
				abyte[0] = (uchar) ((0x0000ff00 & i_Frequency) >> 8);
			else abyte[0] =0x01;
			abyte[1] = (uchar) ((0x00ff0000 & i_Frequency) >> 16);
			abyte[2] = (uchar)  (0x000000ff & i_Frequency);
		} 
		else
		{
			abyte[0] = (uchar) ((0x0000ff00 & i_Frequency) >> 8);
			abyte[1] = (uchar)  (0x000000ff & i_Frequency);
			abyte[2] = (uchar) ((0x00ff0000 & i_Frequency) >> 16);
		}
		qDebug() << "控制指令:"<< abyte.toHex();
	
	} 
	else if (e_operation==e_Operation::STARTSWEEP)
	{
		abyte.resize(2);
		if (e_frequencytype == e_FrequencyType::e_SW||e_frequencytype == e_FrequencyType::e_MW)
		{
			abyte[1] = (uchar)  (0x000000ff & i_Frequency);
			abyte[0] = (uchar) ((0x0000ff00 & i_Frequency) >> 8);
		} 
	}
	return abyte;
}
void DeviceProtocol::connectToHost()
{
	if (!socketinfo.isConnected)
	{
		i_heartcount =0;
		if (m_tcpSocket !=NULL)
			m_tcpSocket->connectToHost(socketinfo._addr,socketinfo._port);
		//m_tcpSocket->waitForConnected(3000);
		//Sleep(100);
	}
}

void DeviceProtocol::slottcpRecData()
{
	QByteArray data=m_tcpSocket->readAll();
	m_buffer.append(data);
	int mesg_len;
	int totalLen = m_buffer.size();

	while( totalLen>=HEARTSIZE)
	{
		//不够包头的数据直接就不处理。	
		int i_index = m_buffer.indexOf(_head);
		if (i_index <0||totalLen<=i_index+1)
			return;
		bool falg =false;
		bool bplanisphere =false;
		switch ((unsigned char)m_buffer.at(i_index+1))
		{
		case 0x11://查询状态
			falg =true;
			break;
		case 0xF3://自动搜台后回复
			falg =true;
			break;
		case 0xF4://音量
			falg =true;
			break;
		case 0xF6://心跳
			falg =true;
			break;
		case 0x22://心跳
			falg =true;
			break;
		case 0xF9://星位图
			falg =true;
			bplanisphere =true;
			break;
		case 0xF1://多经分析
			falg =true;
			break;
		}
		if (falg)
		{
			if (totalLen <= i_index+2)
				return;
			if (!bplanisphere)
				mesg_len = int(m_buffer.at(i_index+2));
			else
			{
				QByteArray lenData =m_buffer.mid(i_index+2,2);
				mesg_len =convertByteArray(lenData).toHex().toInt(&falg,16);
			}
			if(totalLen < mesg_len+i_index)
				return;
			if (m_buffer.at(i_index+mesg_len-1) == _end)
			{
				QByteArray revData =m_buffer.mid(i_index,mesg_len);
				if (checkData(revData))
					processData(QByteArray::fromRawData(revData,revData.size()));
			}
			data = m_buffer.right(totalLen - mesg_len);
		}
		else
		{
		
			data.clear();
			data = m_buffer.left(i_index);
			//qDebug()<<"数据:"<<data.toHex();
		}
		totalLen = data.size();
		m_buffer = data;
	}
}

void DeviceProtocol::slottcpConnected()
{
	if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
	{
		socketinfo.isConnected =true;
		controlCommand(e_Operation::STOP_SERARH);
		controlCommand(e_Operation::STOPSWEEP);
	}
}

void DeviceProtocol::slottcpDisConn()
{
	//普通重连
	emit signaldatarev(heartSend,e_DataType::DISCONNECT);
	socketinfo.isConnected =false;
	//connectToHost();
}

bool DeviceProtocol::checkData( QByteArray data)
{
	if (data.at(0)==_head && data.at(data.size()-1)==_end)
		return true;
	return false;
}

void DeviceProtocol::processData( QByteArray data)
{
	switch ((unsigned char)data.at(1))
	{
	case 0x11://查询状态
		if (data.size()==MAXSIZE)
			//qDebug()<<"接受数据:"<<data.toHex();
			emit signaldatarev(data,e_DataType::SEARCH);
		if (data.size()==MULTIPATH)
		{
			qDebug()<<data.toHex();
			emit signaldatarev(data,e_DataType::DTMBSEARCHSTATE);
		}
		break;
	case 0xF3://自动搜台后回复
		if (data.size()==AUTOSEARCHSIZE)
			emit signaldatarev(data,e_DataType::AUTOSEARCH);
		break;
	case 0xF4://心跳
		if (data.size()==HEARTSIZE)
		{
			socketinfo.isConnected =true;
			i_heartcount =0;
			emit signaldatarev(data,e_DataType::HEARTBEAT);
		}
		break;
	
	case 0xF9://星座图
		if (data.size()==PLANISPHERESIZE)
			emit signaldatarev(data,e_DataType::PLANISPHERE);
		break;
	case 0xF1://多经分析
		if (data.size()==MULTIPATH)
			emit signaldatarev(data,e_DataType::Multianalysis);
		break;
	}
}
//发送心跳
void DeviceProtocol::slottimeout()
{

	if (socketinfo.isConnected&&m_tcpSocket->state() == QAbstractSocket::ConnectedState)
	{
		//定义心跳
		if (sysConfig->b_heartbeat)
		{
			sendData(heartSend);
			i_heartcount++;
			if (i_heartcount == 4)
			{
				m_tcpSocket->close();
				m_tcpSocket->waitForDisconnected(3000);
				//connectToHost();
				socketinfo.isConnected =false;
				emit signaldatarev(heartSend,e_DataType::DISCONNECT);
			}
		}
	}
	//else connectToHost();
}
void DeviceProtocol::sendData( QByteArray byteArray )
{
	if (socketinfo.isConnected){
		//qDebug()<<"发送数据:"<<byteArray.toHex();
		m_tcpSocket->write(byteArray);
	}
}

QByteArray DeviceProtocol::convertByteArray( QByteArray bytearray )
{
	QByteArray qbyte; 
	if(bytearray.length() ==2)
	{
		qbyte[0] =bytearray[1];
		qbyte[1] =bytearray[0];
		return qbyte;
	}
	else return qbyte;
}