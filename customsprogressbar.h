#ifndef CUSTOMSPROGRESSBAR_H
#define CUSTOMSPROGRESSBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <qlabel.h>
#include <QTimer>
#include "SprogressBar.h"
class CustomSprogressBar : public QWidget
{
	Q_OBJECT

public:
	CustomSprogressBar(QWidget *parent);
	~CustomSprogressBar();
public:
	void setBarName(QString name);
	void setValue(int value);
	void setNull();
public slots:
	void animationBuffer();
private:
	SprogressBar *m_sprogressBar;
	QVBoxLayout *m_VLayout;
	QLabel *m_name;

	QTimer *timer;
	int animationValue;
};

#endif // CUSTOMSPROGRESSBAR_H
