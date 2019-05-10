#ifndef CUSTOMPLOTPAGE_H
#define CUSTOMPLOTPAGE_H

#include <QWidget>
#include <qlayout.h>
#include <QTimer>
#include <QMouseEvent>
#include "ui_CustomPlotexpend.h"
#include "DataBaseTool.h"
class CustomPlotPage : public QWidget
{
	Q_OBJECT

public:
	CustomPlotPage(QWidget *parent);
	~CustomPlotPage();
	QCPRange axisChanged(const double lower, const double upper, const QCPRange &newRange);
signals:
public slots :
	void rightStepOne(int limitValue);
	void leftStepOne(int limitValue);
	void startTest();
	void setRangeByType(const int type);
	void setData(const int index, const QVector<double> &x, const QVector<double> &y);
	void clearData();
private:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void initPlot();
private:
	Ui::CustomPlotPage *ui;
	QCPItemText *textLabel;

	QTimer *time;
	QVector<double> m_xValue;
	QVector<double> m_yValue;
	double m_stepone;
};

#endif // CUSTOMPLOTPAGE_H
