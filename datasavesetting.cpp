#include "datasavesetting.h"
#include <qpushbutton.h>

DataSaveSetting::DataSaveSetting(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("settingPage");
	m_layout = new QGridLayout(this);
	m_title = new QLabel(QString::fromLocal8Bit("数据保存设置"), this);
	m_title->setObjectName("Title");
	QLabel *label = new QLabel(QString::fromLocal8Bit("数据保存："), this);
	label->setAlignment(Qt::AlignCenter);
	QPushButton *saveBtn = new QPushButton(this);
	saveBtn->setObjectName("onOffBtn");
	saveBtn->setCheckable(true);
	m_layout->addWidget(m_title, 0, 0);
	m_layout->addWidget(label, 1, 0);
	m_layout->addWidget(saveBtn, 1, 1);
	m_layout->setContentsMargins(10, 0, 10, 30);
	setLayout(m_layout);
}

DataSaveSetting::~DataSaveSetting()
{

}
void DataSaveSetting::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}