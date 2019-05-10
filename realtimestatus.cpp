#include "realtimestatus.h"

RealTimeStatus::RealTimeStatus(QWidget *parent)
	: QWidget(parent)
{
	m_sprogressLeftBar = new CustomSprogressBar(this);
	m_sprogressRightBar = new CustomSprogressBar(this);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &RealTimeStatus::testStart);
	m_layout = new QHBoxLayout(this);
	initWidgetLayout();
}

RealTimeStatus::~RealTimeStatus()
{

}
void RealTimeStatus::initWidgetLayout() 
{
	m_layout->addWidget(m_sprogressLeftBar);
	m_layout->addStretch();
	m_layout->addWidget(m_sprogressRightBar);
	m_layout->addStretch();
	setLayout(m_layout);
}
void RealTimeStatus::setType(int type)
{
	if (type == ModeType::FM_TYPE)
	{
		m_sprogressLeftBar->show();
		m_sprogressRightBar->show();
		m_sprogressRightBar->setBarName(QString::fromLocal8Bit("ÓÒÉùµÀ"));
		m_sprogressLeftBar->setBarName(QString::fromLocal8Bit("×óÉùµÀ"));
	}
	else if(type == ModeType::DTBM_TYPE){
		m_sprogressLeftBar->hide();
		m_sprogressRightBar->hide();
	}
	else {
		m_sprogressRightBar->show();
		m_sprogressLeftBar->hide();
		m_sprogressRightBar->setBarName(QString::fromLocal8Bit("ÉùµÀÖµ"));
	}
}
void RealTimeStatus::testStart()
{
	int leftValue = qrand() % 100 + 1;
	int rightValue = qrand() % 100 + 1;
	m_sprogressLeftBar->setValue(leftValue);
	m_sprogressRightBar->setValue(rightValue);
}
void RealTimeStatus::startTest(bool bstart)
{
	if (bstart) {
		timer->stop();
		m_sprogressLeftBar->setNull();
		m_sprogressRightBar->setNull();
	}
	else {
		timer->start(1000);
	}
}
