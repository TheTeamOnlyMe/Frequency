#include "customtableview.h"

CustomTableView::CustomTableView(QWidget *parent)
	: QWidget(parent)
	, m_rowCount(1)
	, m_columnCount(0)
	, m_bAddButton(false)
{
	m_layout = new QHBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_tableView = new QTableView(this);
	m_model = new QStandardItemModel();
	initHeader();
	m_layout->addWidget(m_tableView);
	setLayout(m_layout);
}

CustomTableView::~CustomTableView()
{

}
void CustomTableView::initHeader()
{
	m_statusButtonGroup = new QButtonGroup(this);
	m_checkButtonGroup = new QButtonGroup(this);
	m_model->setHorizontalHeaderItem(0, new QStandardItem());//添加勾选按钮

	m_model->setRowCount(m_rowCount);
	m_tableView->setModel(m_model);
	m_tableView->horizontalHeader()->setStretchLastSection(true);
	m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	m_tableView->setColumnWidth(0, 31);

	connect(m_tableView, &QTableView::clicked, this, &CustomTableView::clickCurrentRow);//点击表格创建对应表单
	for (int i = 0; i < m_model->rowCount() - 1; i++)
	{
		QPushButton *button = new QPushButton(this);
		button->setObjectName("TableButtonImage");
		button->setCheckable(true);
		m_tableView->setIndexWidget(m_model->index(i, 0), button);
	}
}

void CustomTableView::clickCurrentRow(const QModelIndex &index)
{
	qDebug()<<"row:"<<index.row();
	for (int i = 0; i < index.column(); i++)
	{
		//qDebug() << "column "<<i<<":" << index.index;
	}
	FrequencyDataRecord record;
	record.row = index.row();
	record.stationName = index.data(1).toString();
	record.frequencyValue = index.data(2).toDouble();
	record.type = index.data(3).toInt();//获取当前类型DTMB、FM、AM、SW
	record.status = index.data(4).toInt();
	emit createForm(record, m_rowCount);
}


void CustomTableView::setHiddenColumn(int column)
{
	m_tableView->setColumnHidden(column,true);
}
//设置表头QStringList :0-行号，1-台站名，2-调频数值，3-频率类型字符串，4-状态，5-当前频率类型值
void CustomTableView::setHeaderItem(QStringList headerList)
{
	m_columnCount = headerList.size();
	for (int i = 0; i < headerList.size(); i++)
	{
		m_model->setHorizontalHeaderItem(i+1, new QStandardItem(headerList.at(i)));
		m_tableView->horizontalHeader()->setSectionResizeMode(i+1, QHeaderView::Stretch);
	}
}
//设置单元格宽度
void CustomTableView::setHeaderWidth(int logicIndex,int nwidth)
{
	m_tableView->horizontalHeader()->setSectionResizeMode(logicIndex, QHeaderView::Fixed);
	m_tableView->setColumnWidth(logicIndex, nwidth);
}
//添加checkbutton
void CustomTableView::addCheckButton()
{
	QPushButton *button = new QPushButton(this);
	button->setObjectName("TableButtonImage");
	button->setCheckable(true);
	m_checkButtonGroup->addButton(button, m_rowCount-1);
	m_tableView->setIndexWidget(m_model->index(m_rowCount - 1, 0), m_checkButtonGroup->button(m_rowCount-1));
}
void CustomTableView::setCheckButtonExclusive(bool bselect)
{
	m_checkButtonGroup->setExclusive(bselect);
}

//增加一行数据
void CustomTableView::addRowData(const QStringList &data)
{
	//设置数据并存储到数据库中

	qDebug() << QString::fromLocal8Bit("增加一行数据");
	addCheckButton();
	QList<QStandardItem *> list;
	for (int i = 1; i < data.size(); i++)
	{
		const QModelIndex index = m_tableView->model()->index(m_rowCount - 1, i );
		m_tableView->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
		m_tableView->model()->setData(index, data.at(i));
	}
	addStatusButton();

	m_rowCount++;
	m_model->setRowCount(m_rowCount);
}
//添加删除按钮
void CustomTableView::addStatusButton()
{
	if (m_bAddButton)
		return;
	QPushButton *button = new QPushButton(this);
	button->setObjectName("deleteButton");
	button->setCheckable(true);
	m_statusButtonGroup->addButton(button, m_rowCount - 1);
	m_tableView->setIndexWidget(m_model->index(m_rowCount - 1, m_columnCount + 1), m_statusButtonGroup->button(m_rowCount - 1));
}
//修改本行数据
void CustomTableView::modifyRowData(QStringList &data)
{
	qDebug() << QString::fromLocal8Bit("修改表格数据");
	for (int i = 1; i < data.size(); i++)
	{
		const QModelIndex index = m_tableView->model()->index(data.at(0).toInt(), i);
		m_tableView->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
		m_tableView->model()->setData(index, data.at(i));
	}
}
//删除该行数据
void CustomTableView::deleteRowData(const int logicIndex)
{

}
void CustomTableView::initForm()
{

}
//获取当前测试的所有类型DTMB、FM、AM、SW
void CustomTableView::setTypeList(int typeList)
{
	m_typeList = typeList;
}
//设置隐藏按钮
void CustomTableView::hideStatusButton(bool bAddStatusBtn)
{
	m_bAddButton = bAddStatusBtn;
}

//根据所选类型显示数据
//void CustomTableView::showDataByType(int typeList)
//{
//
//}