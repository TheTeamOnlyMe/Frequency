#ifndef RECORDPAGE_H
#define RECORDPAGE_H

#include <QWidget>
#include <qpushbutton.h>
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include "operationbuttonbar.h"
#include "DataBaseTool.h"
class RecordPage : public QWidget
{
	Q_OBJECT

public:
	RecordPage(QWidget *parent);
	~RecordPage();

signals:
	void returnNavigation(int pageIndex);
private slots:
	void changePage();
private:

	QHBoxLayout *m_hLayout;
	OperationButtonBar *m_rightBar;
	
};

#endif // RECORDPAGE_H
