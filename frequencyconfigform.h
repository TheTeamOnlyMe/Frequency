#ifndef DATAFORM_H
#define DATAFORM_H

#include <QDialog>
#include <QEvent>
#include <QKeyEvent>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <QListView>
#include <QStyleOption>
#include <QPainter>
#include "DataBaseTool.h"
class FrequencyConfigForm : public QDialog
{
	Q_OBJECT

public:
	FrequencyConfigForm(QWidget *parent);
	~FrequencyConfigForm();
	void setCurrentIndex(int pageIndex) { m_pageIndex = pageIndex; }
signals:
	void addData(QStringList &dataList);
	void modifyData(QStringList &data);
	void getModifiedData(const QStringList &data);
	void closeFrom();
public slots:
	void processData(const FrequencyDataRecord &index, int rowcount);
	void modifyOneData(const QModelIndex &index);
	void addOneData(const QModelIndex &index);
	void acceptData();
	void closeFrequncyDialog();
	void setTypeList(int typeList);
private:
	void init();
	void paintEvent(QPaintEvent *event);
	bool event(QEvent *event);
private:
	QGridLayout *m_layout;
	QComboBox *m_stationCombox;
	QComboBox *m_typeCombox;
	QLineEdit *m_lineEdit;
	QPushButton *m_autoBtn;	//自动搜台按钮
	QPushButton *m_acceptButton;
	QPushButton *m_closeButton;
	int m_formType;
	int m_currentRow;
	int m_pageIndex;
	
};

#endif // DATAFORM_H
