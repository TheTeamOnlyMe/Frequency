#ifndef FREQUENCYCOLORSETTING_H
#define FREQUENCYCOLORSETTING_H

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
class FrequencyColorSetting : public QWidget
{
	Q_OBJECT

public:
	FrequencyColorSetting(QWidget *parent);
	~FrequencyColorSetting();
private:
	void initTable();
signals:
	void currentChanged(int index);
	void setTypeList(int typeList);
private:
	QHBoxLayout *m_layout;
	CustomTableView *m_table;
};

#endif // FREQUENCYCOLORSETTING_H
