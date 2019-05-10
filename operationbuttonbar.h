#ifndef OPERATIONBUTTONBAR_H
#define OPERATIONBUTTONBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include "DataBaseTool.h"
class OperationButtonBar : public QWidget
{
	Q_OBJECT

public:
	OperationButtonBar(QWidget *parent);
	~OperationButtonBar();
	void addOperatButtons(QStringList buttonsName);
	void setBtnlayout();
signals:
	void returnMainPage();
	void clicked(int buttonId);
private slots:
	void slotReturnBtn();
private:
	void init();
	void paintEvent(QPaintEvent *event);
private:

	QVBoxLayout *m_pLayout;
	QButtonGroup *m_pBtnGroup;
	int m_nButtonCount;
	QStringList m_strButtonName;
};

#endif // OPERATIONBUTTONBAR_H
