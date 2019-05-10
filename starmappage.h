#ifndef STARMAPPAGE_H
#define STARMAPPAGE_H

#include <QWidget>
#include "ui_CustomPlotexpend.h"
#include "DataBaseTool.h"
class StarMapPage : public QWidget
{
	Q_OBJECT

public:
	StarMapPage(QWidget *parent);
	~StarMapPage();
	void initPlot();
public slots:
	void startTest(bool bstart);

private:
	Ui::CustomPlotPage *ui;

};

#endif // STARMAPPAGE_H
