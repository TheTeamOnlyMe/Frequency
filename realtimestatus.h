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
	RealTimeStatus(QWidget *parent);//����ҳ���±���ʾ��Ӧ�Ļ���ҳ��������Ƶ����������˫������
	~RealTimeStatus();
	void initWidgetLayout();
public slots:
	void startTest(bool bstart);
	void setType(int type);	
	void testStart();
private:
	//���沼�ֹ�����
	QHBoxLayout *m_layout;
	//��ƵDTMB
	//˫����
	CustomSprogressBar *m_sprogressLeftBar;
	CustomSprogressBar *m_sprogressRightBar;


	QTimer *timer;
};

#endif // REALTIMESTATUS_H
