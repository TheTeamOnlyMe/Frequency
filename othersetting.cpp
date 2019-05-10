#include "othersetting.h"

OtherSetting::OtherSetting(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("OtherSetting");
	m_reviseSet = new ReviseSetting(this);
	m_cycleSet = new CycleSetting(this);
	m_dataSaveSet = new DataSaveSetting(this);
	m_layout = new QGridLayout(this);
	m_layout->addWidget(m_reviseSet, 0, 0, 2, 1);
	m_layout->addWidget(m_cycleSet, 0, 1, 1, 1);
	m_layout->addWidget(m_dataSaveSet, 1, 1, 1, 1);
	m_layout->setSpacing(30);
	m_layout->setContentsMargins(20,20,20,20);
	setLayout(m_layout);
}

OtherSetting::~OtherSetting()
{

}
void OtherSetting::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}