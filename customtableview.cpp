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
	m_model->setHorizontalHeaderItem(0, new QStandardItem());//��ӹ�ѡ��ť

	m_model->setRowCount(m_rowCount);
	m_tableView->setModel(m_model);
	m_tableView->horizontalHeader()->setStretchLastSection(true);
	m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	m_tableView->setColumnWidth(0, 31);

	connect(m_tableView, &QTableView::clicked, this, &CustomTableView::clickCurrentRow);//�����񴴽���Ӧ��
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
	record.type = index.data(3).toInt();//��ȡ��ǰ����DTMB��FM��AM��SW
	record.status = index.data(4).toInt();
	emit createForm(record, m_rowCount);
}


void CustomTableView::setHiddenColumn(int column)
{
	m_tableView->setColumnHidden(column,true);
}
//���ñ�ͷQStringList :0-�кţ�1-̨վ����2-��Ƶ��ֵ��3-Ƶ�������ַ�����4-״̬��5-��ǰƵ������ֵ
void CustomTableView::setHeaderItem(QStringList headerList)
{
	m_columnCount = headerList.size();
	for (int i = 0; i < headerList.size(); i++)
	{
		m_model->setHorizontalHeaderItem(i+1, new QStandardItem(headerList.at(i)));
		m_tableView->horizontalHeader()->setSectionResizeMode(i+1, QHeaderView::Stretch);
	}
}
//���õ�Ԫ����
void CustomTableView::setHeaderWidth(int logicIndex,int nwidth)
{
	m_tableView->horizontalHeader()->setSectionResizeMode(logicIndex, QHeaderView::Fixed);
	m_tableView->setColumnWidth(logicIndex, nwidth);
}
//���checkbutton
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

//����һ������
void CustomTableView::addRowData(const QStringList &data)
{
	//�������ݲ��洢�����ݿ���

	qDebug() << QString::fromLocal8Bit("����һ������");
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
//���ɾ����ť
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
//�޸ı�������
void CustomTableView::modifyRowData(QStringList &data)
{
	qDebug() << QString::fromLocal8Bit("�޸ı������");
	for (int i = 1; i < data.size(); i++)
	{
		const QModelIndex index = m_tableView->model()->index(data.at(0).toInt(), i);
		m_tableView->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
		m_tableView->model()->setData(index, data.at(i));
	}
}
//ɾ����������
void CustomTableView::deleteRowData(const int logicIndex)
{

}
void CustomTableView::initForm()
{

}
//��ȡ��ǰ���Ե���������DTMB��FM��AM��SW
void CustomTableView::setTypeList(int typeList)
{
	m_typeList = typeList;
}
//�������ذ�ť
void CustomTableView::hideStatusButton(bool bAddStatusBtn)
{
	m_bAddButton = bAddStatusBtn;
}

//������ѡ������ʾ����
//void CustomTableView::showDataByType(int typeList)
//{
//
//}