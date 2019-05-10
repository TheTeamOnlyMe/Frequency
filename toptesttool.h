#ifndef TOPTOOLBAR_H
#define TOPTOOLBAR_H

#include <QWidget>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qbuttongroup.h>
#include <qstackedlayout.h>
#include <QGridLayout>
#include "DataBaseTool.h"
#include "singlepatterncombox.h"
#include "cyclepatternconbox.h"
enum LeftBtnNum
{
	TESTDATABUTTON = 0,
	MAPBUTTON,
	MULTIPATHBTN,
	STARMAPBTN,
	RETURNHOME,
};
class TopTestTool : public QWidget
{
	Q_OBJECT

public:
	TopTestTool(QWidget *parent);
	~TopTestTool();
signals:
	void startTest(bool bstart);
	void setType(int type);
	//��ʼ��ť�ź�
	void startPainLimitLine(bool bStart);
	//�Զ���combox���ò������ͣ�type��DMTB��FM��AM��SW��
	void setTypeList(int typeList);
	//�����л���ť�ź�
	void changeTestPage(int type);
public slots:
	void stopTest();
private slots:
	void changeMode();
	void changeCombox(bool bstart);
	void setBarCell(int modeType);
private:
	void initCombox();
	void initLeftButton();
	void paintEvent(QPaintEvent *event);
	void setLeftBtn(QString btnName, int btnNum);
private:
	QHBoxLayout *m_mainLayout;
	QButtonGroup *m_leftBtnGroup;
	SinglePatternCombox *m_customCombox;
	CyclePatternConbox *m_cycliCombox;
	QPushButton *m_modeChangeBtn;
	QPushButton *m_startControlBtn;
	bool m_bSelectSigle;
	QStackedLayout *m_stackLayout;
	bool m_bStartTest;
};

#endif // TOPTOOLBAR_H
