#ifndef TOPFREQUENCYTOOL_H
#define TOPFREQUENCYTOOL_H

#include <QWidget>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QListView>
#include "DataBaseTool.h"
class TopFrequencyTool : public QWidget
{
	Q_OBJECT

public:
	TopFrequencyTool(QWidget *parent);
	~TopFrequencyTool();
	void setValue(QString value);
private:
	void paintEvent(QPaintEvent *event);
private slots:
	void startFrequency();

signals:
	void moveRight(int limitValue);
	void moveLeft(int limitValue);
	void clearData();
	void startLimitData(double limitValue);
	void changeType(int type);
public slots:
	void moveLeftClicked();
	void moveRightClicked();
	void changeValueData(int value);
	void setType(int type);
private:
	QPushButton *m_startBtn;
	QPushButton *m_stepLeftBtn;
	QPushButton *m_stepRightBtn;
	QPushButton *m_screenshotBtn;
	QComboBox *m_combox;
	QLabel *m_label;
	QLineEdit *m_lineEdit;
	QBoxLayout *m_layout;
	int m_valuelist[4];
};

#endif // TOPFREQUENCYTOOL_H
