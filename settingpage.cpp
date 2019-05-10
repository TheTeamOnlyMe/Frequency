#include "settingpage.h"

SettingPage::SettingPage(QWidget *parent)
	: QWidget(parent)
{
	setContentsMargins(0, 0, 0, 0);
	m_stackedLayout = new QStackedLayout(this);
	m_stackedLayout->setContentsMargins(0, 0, 0, 0);
	m_frequencySettingWidget = new FrequencySetting(this);
	m_stationSettingWidget = new StationSetting(this);
	m_frequencyColorSetting = new FrequencyColorSetting(this);
	m_otherSetting = new OtherSetting(this);
	connect(this, &SettingPage::setTypeList, m_frequencySettingWidget, &FrequencySetting::setTypeList);
	connect(this,&SettingPage::currentPage, m_frequencySettingWidget, &FrequencySetting::currentChanged);
	connect(this, &SettingPage::currentPage, m_stationSettingWidget, &StationSetting::currentChanged);
	connect(this, &SettingPage::currentPage, m_frequencyColorSetting, &FrequencyColorSetting::currentChanged);
	connect(this, &SettingPage::currentPage, m_otherSetting, &OtherSetting::currentChanged);

	m_stackedLayout->addWidget(m_frequencySettingWidget);
	m_stackedLayout->addWidget(m_stationSettingWidget);
	m_stackedLayout->addWidget(m_frequencyColorSetting);
	m_stackedLayout->addWidget(m_otherSetting);
	m_stackedLayout->setCurrentWidget(m_frequencySettingWidget);
	setLayout(m_stackedLayout);
}

SettingPage::~SettingPage()
{

}
void SettingPage::changeSettingPage(int index)
{
	emit currentPage(index);
	m_stackedLayout->setCurrentIndex(index);

}
