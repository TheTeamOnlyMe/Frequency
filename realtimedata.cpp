#include "realtimedata.h"

RealTimeData::RealTimeData(QWidget *parent,int modetype)
	: QWidget(parent)
	, m_type(0)
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &RealTimeData::start);
	m_layout = new QGridLayout(this);
	m_layout->setSpacing(10);
	initLabel();
	setDataName();
}

RealTimeData::~RealTimeData()
{

}
void RealTimeData::setValue(QStringList valuelist)
{

}
void RealTimeData::initLabel()
{
	m_labfrequency = new QLableExpand(this, QString::fromLocal8Bit("Ƶ��"));
	m_labfieldstrengthvalueA = new QLableExpand(this, QString::fromLocal8Bit("��ǿ"));
	m_labfieldstrengthvalueB = new QLableExpand(this, QString::fromLocal8Bit("��ǿ"), false);
	m_labcnr = new QLableExpand(this, QString::fromLocal8Bit("�����"));
	//m_labsnr = new QLableExpand(this, QString::fromLocal8Bit("�����"));
	m_labfrequencyoffset = new QLableExpand(this, QString::fromLocal8Bit("Ƶƫ"));
	m_labsavedata = new QLableExpand(this, QString::fromLocal8Bit("��������"));
	m_labsatellite = new QLableExpand(this, QString::fromLocal8Bit("����"));
	//m_labtestmode = new QLableExpand(this, QString::fromLocal8Bit("ģʽ"));

	m_labcarrierwaveM = new QLableExpand(this, QString::fromLocal8Bit("�ز�"),false);
	m_labstarbitmap = new QLableExpand(this, QString::fromLocal8Bit("��λͼ"),false);
	m_labfec = new QLableExpand(this, QString::fromLocal8Bit("ǰ�����"),false);
	m_labgi = new QLableExpand(this, QString::fromLocal8Bit("�������"),false);
	m_labti = new QLableExpand(this, QString::fromLocal8Bit("��֯���"), false);
	m_labber = new QLableExpand(this, QString::fromLocal8Bit("����������"), false);
	m_labmer = new QLableExpand(this, QString::fromLocal8Bit("����������"), false);

	m_layout->addWidget(m_labfrequency, 0, 0);
	m_layout->addWidget(m_labfieldstrengthvalueA, 0, 1);
	m_layout->addWidget(m_labcnr, 1, 0);
	//m_layout->addWidget(m_labtestmode, 1, 1);
	m_layout->addWidget(m_labsavedata, 2, 0);
	m_layout->addWidget(m_labsatellite, 2, 1);

	m_layout->addWidget(m_labcarrierwaveM, 3, 0);
	m_layout->addWidget(m_labstarbitmap, 3, 1);
	m_layout->addWidget(m_labfec, 4, 0);
	m_layout->addWidget(m_labgi, 4, 1);
	m_layout->addWidget(m_labti, 5, 0);
	m_layout->addWidget(m_labber, 5, 1);
	m_layout->addWidget(m_labmer, 6, 0);
	m_layout->addWidget(m_labfrequencyoffset, 7, 0);
	m_layout->addWidget(m_labfieldstrengthvalueB, 8, 0);
	setLayout(m_layout);
}
void RealTimeData::setDataName()
{

}
void RealTimeData::start()
{
	m_labfrequency->SetValue(QString("%1").arg(qrand() % 100));
	m_labfieldstrengthvalueA->SetValue(QString("%1").arg(qrand() % 80));
	m_labfieldstrengthvalueB->SetValue(QString("%1").arg(qrand() % 80));
	m_labcnr->SetValue(QString("%1").arg(qrand() % 90));
	m_labfrequencyoffset->SetValue(QString("%1").arg(qrand() % 70));
	//m_labtestmode->SetValue(QString("%1").arg(m_type));
	m_labsavedata->SetValue(QString::fromLocal8Bit("��"));
	m_labsatellite->SetValue(QString("%1").arg(qrand() % 60));
	m_labcarrierwaveM->SetValue(QString("%1").arg(qrand() % 66));
	m_labstarbitmap->SetValue(QString("%1").arg(qrand() % 88));
	m_labfec->SetValue(QString("%1").arg(qrand() % 99));
	m_labgi->SetValue(QString("%1").arg(qrand() % 77));
	m_labti->SetValue(QString("%1").arg(qrand() % 87));
	m_labber->SetValue(QString("%1").arg(qrand() % 83));
	m_labmer->SetValue(QString("%1").arg(qrand() % 92));
}
void RealTimeData::setType(int type)//��ǰ��������
{
	//m_type = type;
	//���ֵ���ģʽ
	if (type == ModeType::DTBM_TYPE)
	{
		m_labcarrierwaveM->show();
		m_labstarbitmap->show();
		m_labfec->show();
		m_labgi->show();
		m_labti->show();
		m_labber->show();
		m_labmer->show();
	}
	else
	{
		m_labcarrierwaveM->hide();
		m_labstarbitmap->hide();
		m_labfec->hide();
		m_labgi->hide();
		m_labti->hide();
		m_labber->hide();
		m_labmer->hide();
	}

}
void RealTimeData::startTest(bool bpause)
{
	if (bpause) {
		timer->stop();
		m_labfrequency->SetNull();
		m_labfieldstrengthvalueA->SetNull();
		m_labfieldstrengthvalueB->SetNull();
		m_labcnr->SetNull();
		m_labfrequencyoffset->SetNull();
		m_labsavedata->SetNull();
		m_labsatellite->SetNull();
		m_labcarrierwaveM->SetNull();
		m_labstarbitmap->SetNull();
		m_labfec->SetNull();
		m_labgi->SetNull();
		m_labti->SetNull();
		m_labber->SetNull();
		m_labmer->SetNull();
	}
	else
	{
		timer->start(1000);
	}
}
