#ifndef CYCLEPATTERNCONBOX_H
#define CYCLEPATTERNCONBOX_H

#include <QWidget>
#include <QComboBox>
#include <QListView>
#include <QHBoxLayout>
#include <QLabel>
#include "DataBaseTool.h"
struct TestData
{
	int typeID;
	double value;
	QString typeName;
};
class CyclePatternConbox : public QWidget
{
	Q_OBJECT

public:
	CyclePatternConbox(QWidget *parent);
	~CyclePatternConbox();
	void setData(QStringList slist);
	int getCurrentType();
	void clear();
private:
	void initData();
	void paintEvent(QPaintEvent *event);
	void addData(int typeList, int modeType);
signals:
	void changeType(int type);
public slots:
	void changeDataType(int index);
	void setType(int type);
private:
	int m_currentType;
	QVector<TestData> m_vtAllData;
	QVector<TestData> m_vtShowData;
	QHBoxLayout *m_layout;
	QComboBox *m_combox;
	QLabel *m_label;
	
};

#endif // CYCLEPATTERNCONBOX_H
