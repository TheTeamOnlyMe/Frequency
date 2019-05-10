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
	QPushButton *m_dataOutBtn;//数据导出按钮
	QPushButton *m_reportOutBtn;//报告导出按钮
	QPushButton *m_returnBtn;	//返回按钮

};

#endif // REPORTPAGE_H
