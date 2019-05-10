#ifndef MULTIPATHPAGE_H
#define MULTIPATHPAGE_H

#include <QWidget>
#include "ui_CustomPlotexpend.h"
#include "DataBaseTool.h"
class MultiPathPage : public QWidget
{
	Q_OBJECT

public:
	MultiPathPage(QWidget *parent);
	~MultiPathPage();
	void initPlot();
public slots:
	void startTest(bool bpause);

private:
	Ui::CustomPlotPage *ui;
};

#endif // MULTIPATHPAGE_H
