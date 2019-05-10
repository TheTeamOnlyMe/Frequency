#ifndef DATASAVESETTING_H
#define DATASAVESETTING_H

#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include "DataBaseTool.h"

class DataSaveSetting : public QWidget
{
	Q_OBJECT

public:
	DataSaveSetting(QWidget *parent);
	~DataSaveSetting();

private:
	void paintEvent(QPaintEvent *event);
private:
	QGridLayout *m_layout;
	QLabel *m_title;

};

#endif // DATASAVESETTING_H
