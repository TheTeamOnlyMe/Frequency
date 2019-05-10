#include "datapresentationpage.h"

DataPresentationPage::DataPresentationPage(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("dataPage");
	
	m_HLayout = new QHBoxLayout(this);
	m_data = new RealTimeData(this,1);
	m_status = new RealTimeStatus(this);
	initConnect();
	
	m_HLayout->addWidget(m_status);
	m_HLayout->addWidget(m_data);
	m_HLayout->setStretchFactor(m_status, 4);
	m_HLayout->setStretchFactor(m_data, 5);
	setLayout(m_HLayout);
}


DataPresentationPage::~DataPresentationPage()
{

}

void DataPresentationPage::initConnect()
{
	connect(this, &DataPresentationPage::setType, m_data, &RealTimeData::setType);
	connect(this, &DataPresentationPage::setType, m_status, &RealTimeStatus::setType);

	//点击开始按钮，启动测试
	connect(this, &DataPresentationPage::startTest, m_data, &RealTimeData::startTest);
	connect(this, &DataPresentationPage::startTest, m_status, &RealTimeStatus::startTest);
}

void DataPresentationPage::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void DataPresentationPage::initData()
{
	
}
