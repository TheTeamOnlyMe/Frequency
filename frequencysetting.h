#ifndef FREQUENCYSETTING_H
#define FREQUENCYSETTING_H

#include <QWidget>
#include <qtableview.h>
#include <qsqldatabase.h>
#include <qsqltablemodel.h>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <qdebug.h>
#include <QDialog>
#include "customtableview.h"
#include "frequencyconfigform.h"
class FrequencySetting : public QWidget
{
	Q_OBJECT

public:
	FrequencySetting(QWidget *parent);
	~FrequencySetting();
private:
	void initTable();
signals:
	void setType(int typelist);
	void currentChanged(int index);
	void processData(const FrequencyDataRecord &index,int rowcount);
	
public slots:
	void setTypeList(int typeList);
	void closeForm();
	void createForm(const FrequencyDataRecord &index, int rowcount);
private:
	QHBoxLayout *m_layout;
	CustomTableView *m_table;
	FrequencyConfigForm *m_frequencyForm;
	int m_typeList;
};

#endif // FREQUENCYSETTING_H
