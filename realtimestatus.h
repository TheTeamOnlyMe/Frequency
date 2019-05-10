#ifndef REALTIMESTATUS_H
#define REALTIMESTATUS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include "realtimedata.h"
#include "customsprogressbar.h"
#include "DataBaseTool.h"
class RealTimeStatus : public QWidget
{
	Q_OBJECT

public:
	RealTimeStatus(QWidget *parent);//根据页面下标显示对应的缓存页（电视视频，单声道，双声道）
	~RealTimeStatus();
	void initWidgetLayout();
public slots:
	void startTest(bool bstart);
	void setType(int type);	
	void testStart();
private:
	//界面布局管理器
	QHBoxLayout *m_layout;
	//视频DTMB
	//双声道
	CustomSprogressBar *m_sprogressLeftBar;
	CustomSprogressBar *m_sprogressRightBar;


	QTimer *timer;
};

#endif // REALTIMESTATUS_H
