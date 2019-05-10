#ifndef CYCLESETTING_H
#define CYCLESETTING_H
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <QWidget>
#include <qlineedit.h>
#include "DataBaseTool.h"

class CycleSetting : public QWidget
{
	Q_OBJECT

public:
	CycleSetting(QWidget *parent);
	~CycleSetting();

private:
	void paintEvent(QPaintEvent *event);
private:
	QGridLayout *m_layout;

};

#endif // CYCLESETTING_H
