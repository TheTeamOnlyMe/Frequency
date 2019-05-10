#ifndef DATAPRESENTATIONPAGE_H
#define DATAPRESENTATIONPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <qgridlayout.h>
#include <QStyleOption>
#include <QPainter>
#include "realtimedata.h"
#include "realtimestatus.h"
#include "DataBaseTool.h"
class DataPresentationPage : public QWidget
{
	Q_OBJECT

public:
	DataPresentationPage(QWidget *parent);
	~DataPresentationPage();
private:
	void paintEvent(QPaintEvent *event);
	void initData();
	void initConnect();
signals:
	void startTest(bool bstart);
	void setType(int type);
public slots:
	//void setData(DataType *type);
private:
	QHBoxLayout *m_HLayout;
	RealTimeData *m_data;
	RealTimeStatus *m_status;
	
};

#endif // DATAPRESENTATIONPAGE_H
