#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "xcustomstatus.h"
#include "centerwidget.h"
class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	void init();
	void initView();
	void paintEvent(QPaintEvent *event);
private:
	QVBoxLayout *m_pVLayout;
	CenterWidget *m_pCenterWidget;
	XCustomStatus *m_pStatus;
};

#endif // MAINWINDOW_H
