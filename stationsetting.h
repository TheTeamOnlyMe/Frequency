#ifndef STATIONSETTING_H
#define STATIONSETTING_H

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
class StationSetting : public QWidget
{
	Q_OBJECT

public:
	StationSetting(QWidget *parent);
	~StationSetting();
private:
	void initTable();
signals:
	void currentChanged(int index);
	void setTypeList(int typeList);
private:
	QHBoxLayout *m_layout;
	CustomTableView *m_table;
};

#endif // STATIONSETTING_H
