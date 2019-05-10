#ifndef TOPSETTINGBAR_H
#define TOPSETTINGBAR_H

#include <QWidget>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qbuttongroup.h>
#include "DataBaseTool.h"
class TopSettingBar : public QWidget
{
	Q_OBJECT

public:
	TopSettingBar(QWidget *parent);
	~TopSettingBar();
signals:
	void setType(int typeList);	//设置类型数据
	void setPageIndex(int index);//通过按钮控制设置子页面切换
private:
	void paintEvent(QPaintEvent *event);
private:
	QHBoxLayout *m_layout;
	QButtonGroup *m_buttonGroup;
	QPushButton *m_frequencySetting;
	QPushButton *m_stationSetting;
	QPushButton *m_frequencyColorSetting;
	QPushButton *m_otherSetting;

};

#endif // TOPSETTINGBAR_H
