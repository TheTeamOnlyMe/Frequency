#ifndef REVISESETTING_H
#define REVISESETTING_H

#include <QWidget>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include "DataBaseTool.h"

class ReviseSetting : public QWidget
{
	Q_OBJECT

public:
	ReviseSetting(QWidget *parent);
	~ReviseSetting();
private:
	void paintEvent(QPaintEvent *event);
	void addSetOption(QString name);
private slots:
	void widgetStatus();
private:
	int count;
	QGridLayout *m_layout;
	
};

#endif // REVISESETTING_H
