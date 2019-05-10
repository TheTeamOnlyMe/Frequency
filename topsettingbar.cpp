#include "topsettingbar.h"

TopSettingBar::TopSettingBar(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("TopBar");
	m_layout = new QHBoxLayout(this);
	m_buttonGroup = new QButtonGroup(this);
	m_frequencySetting = new QPushButton(QString::fromLocal8Bit("频点配置"), this);
	m_frequencySetting->setCheckable(true);
	m_frequencySetting->setChecked(true);
	m_stationSetting = new QPushButton(QString::fromLocal8Bit("发射台配置"), this);
	m_stationSetting->setCheckable(true);
	m_frequencyColorSetting = new QPushButton(QString::fromLocal8Bit("场强颜色配置"), this);
	m_frequencyColorSetting->setCheckable(true);
	m_otherSetting = new QPushButton(QString::fromLocal8Bit("其他配置"), this);
	m_otherSetting->setCheckable(true);
	m_buttonGroup->addButton(m_frequencySetting, 0);
	m_buttonGroup->addButton(m_stationSetting, 1);
	m_buttonGroup->addButton(m_frequencyColorSetting, 2);
	m_buttonGroup->addButton(m_otherSetting, 3);

	m_layout->addWidget(m_frequencySetting,1);
	m_layout->addWidget(m_stationSetting,1);
	m_layout->addWidget(m_frequencyColorSetting, 1);
	m_layout->addWidget(m_otherSetting,1);
	m_layout->addStretch();
	m_layout->setContentsMargins(10, 0, 10, 0);
	setLayout(m_layout);
	connect(m_buttonGroup, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), this, &TopSettingBar::setPageIndex);
}

TopSettingBar::~TopSettingBar()
{

}
void TopSettingBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}