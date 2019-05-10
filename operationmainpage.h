#ifndef TESTMAINWIDGET_H
#define TESTMAINWIDGET_H

#include <QWidget>

#include "testpage.h"
#include "DataBaseTool.h"
#include "customplotpage.h"
#include "settingpage.h"
class OperationMainPage : public QWidget
{
	Q_OBJECT

public:
	OperationMainPage(QWidget *parent);
	~OperationMainPage();

signals:
	void stopTest();
	void startTest(bool bstart);
	void setType(int type);
	//…Ë÷√¿‡–Õ
	void setTypeList(int typeList);
	void changeSettingPage(int pageIndex);
	void clearData();
	void setFrequencyLimitData(int type,const QVector<double> &x,const QVector<double> &y);
	void changeFrequencyRange(int type);
	void changeTestPage(int index);

	void moveRight(int limitValue);
	void moveLeft(int limitValue);
public slots:
	void startPainLimitLine(double limitValue);

	void setCurrentIndex(int index);
private:
	void paintEvent(QPaintEvent *event);
private:
	QStackedLayout *m_pStackPageLayout;
	TestPage *m_pageTest;
	SettingPage *m_settingPage;
	CustomPlotPage *m_widgetPlot;
};

#endif // TESTMAINWIDGET_H
