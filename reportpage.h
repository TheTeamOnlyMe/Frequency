#ifndef REPORTPAGE_H
#define REPORTPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include "DataBaseTool.h"
#include "operationbuttonbar.h"
class ReportPage : public QWidget
{
	Q_OBJECT

public:
	ReportPage(QWidget *parent);
	~ReportPage();
signals:
	void returnNavigation(int pageIndex);
private slots:
	void changePage();
	void paintEvent(QPaintEvent *event);
private:
	QHBoxLayout *m_hLayout;
	QVBoxLayout *m_vLayout;
	OperationButtonBar *m_rightBar;
	QPushButton *m_dataOutBtn;//���ݵ�����ť
	QPushButton *m_reportOutBtn;//���浼����ť
	QPushButton *m_returnBtn;	//���ذ�ť

};

#endif // REPORTPAGE_H
