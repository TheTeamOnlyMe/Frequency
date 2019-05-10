#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QWidget>
#include <qstackedlayout.h>
#include "frequencysetting.h"
#include "stationsetting.h"
#include "frequencycolorsetting.h"
#include "othersetting.h"
class SettingPage : public QWidget
{
	Q_OBJECT

public:
	SettingPage(QWidget *parent);
	~SettingPage();
signals:
	void setTypeList(int typeList);
	void currentPage(int pageIndex);
public slots:
	void changeSettingPage(int index);
private:
	QStackedLayout *m_stackedLayout;
	FrequencySetting *m_frequencySettingWidget;
	StationSetting *m_stationSettingWidget;
	FrequencyColorSetting *m_frequencyColorSetting;
	OtherSetting *m_otherSetting;

};

#endif // SETTINGPAGE_H
