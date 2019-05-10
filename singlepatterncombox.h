#ifndef SINGLEPATTERNCOMBOX_H
#define SINGLEPATTERNCOMBOX_H

#include <QWidget>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <qlineedit.h>
#include <qlabel.h>
#include <QListView>
#include <QComboBox>
#include <QMessageBox>
#include "DataBaseTool.h"
class SinglePatternCombox : public QWidget
{
	Q_OBJECT

public:
	SinglePatternCombox(QWidget *parent);
	~SinglePatternCombox();
	int getCurrentType();
	void clear();
private:
	void initCombox();
	void paintEvent(QPaintEvent *event);
	void initLayout();
signals:
	void sendDataSignal(int typelist);
	void changeType(int type);
public slots:
	void sendDataSlot();
	void changeDataType(int index);
	void setType(int type);
private slots:
	void changeValueData(int index);
private:
	QHBoxLayout *m_layout;
	QPushButton *m_dataTypeBtn;
	QPushButton *m_valueBtn;
	int m_typeList;
	int m_currentType;

	QComboBox *m_typeCombox;
	QComboBox *m_valueCombox;
	QLabel *m_label;
	int m_typelist[4];

	
};

#endif // SINGLEPATTERNCOMBOX_H
