#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QWidget>
#include <QPushButton>
#include <qdebug.h>
#include <QDialog>
#include <qsqltablemodel.h>
#include <QStandardItemModel>
#include <QHeaderView>
#include <qtableview.h>
#include <qgridlayout.h>
#include <qstackedlayout.h>
#include <QHBoxLayout>

#include <qbuttongroup.h>
#include "frequencyconfigform.h"
#include "stationconfigform.h"
#include "DataBase.h"
class CustomTableView : public QWidget
{
	Q_OBJECT

public:
	CustomTableView(QWidget *parent);
	~CustomTableView();
	void initHeader();

	void setHeaderWidth(int logicIndex, int nwidth);
	void setHeaderItem(QStringList headerList);
	void setHiddenColumn(int column);
	void setCheckButtonExclusive(bool bselect);
	void deleteRowData(const int logicIndex);
private:
	void initForm();
	void addStatusButton();
	void addCheckButton();

signals:
	void modifyOneData(QStringList &data);
	void addOneData(const QModelIndex &index);
	void createForm(const FrequencyDataRecord &index,int rowCount);
public slots:
	void clickCurrentRow(const QModelIndex &index);
	//void currentChanged(int index);
	void setTypeList(int typeList);//设置当前所测类型有哪几种
	//void showDataByType(int typeList);//根据所选类型，显示表格数据
	//void createStationForm(const QModelIndex &index);
	void addRowData(const QStringList &data);
	void modifyRowData(QStringList &data);
	void hideStatusButton(bool bAddStatusBtn);

private:
	QHBoxLayout *m_layout;
	QTableView *m_tableView;
	QStandardItemModel *m_model;

	QStackedLayout *m_stackedLayout;
	FrequencyConfigForm *m_frequencyForm;
	StationConfigForm *m_stationForm;

	QButtonGroup *m_statusButtonGroup;
	QButtonGroup *m_checkButtonGroup;
	int m_rowCount;
	int m_columnCount;
	int m_typeList;
	bool m_bAddButton;
};

#endif // CUSTOMTABLEVIEW_H
