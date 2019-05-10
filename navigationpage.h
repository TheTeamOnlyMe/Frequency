#ifndef NAVIAGATIONPAGE_H
#define NAVIAGATIONPAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <QDebug>
#include <QButtonGroup>
#include <QStyleOption>
#include <QPainter>
#include <qlabel.h>
#include <qabstractbutton.h>
#include <QTextBrowser>
#include "DataBaseTool.h"
class NavigationPage : public QWidget
{
	Q_OBJECT

public:
	NavigationPage(QWidget *parent);
	~NavigationPage();
private:
	void initButton();
	void initBtnSize();
	void init();
	void signalConnect();
	void paintEvent(QPaintEvent *event);
signals:
	void modeType(int selectedBtn);
	void changePage(int pageIndex);
public slots:
	void changeToTestPage(int pageIndex);
	void buttonJudge(int btnValue);
private:
	QButtonGroup *m_btnStyleGroup;
	QButtonGroup *m_btnPageGroup;
	QHBoxLayout *m_pHStyle;
	QGridLayout *m_pPageBtnLayout;
	QHBoxLayout *m_pCloseBtnLayout;
	QGridLayout *m_pMainLayout;

	int m_selectedBtn;	//ÒÑÑ¡°´Å¥
};

#endif // NAVIAGATIONPAGE_H
