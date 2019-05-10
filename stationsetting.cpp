#include "stationsetting.h"

StationSetting::StationSetting(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QHBoxLayout(this);
	m_table = new CustomTableView(this);
	connect(this, &StationSetting::setTypeList, m_table, &CustomTableView::setTypeList);
	//connect(this, &StationSetting::setTypeList, m_table, &CustomTableView::showDataByType);
	initTable();
	m_layout->addWidget(m_table);
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
}

StationSetting::~StationSetting()
{

}
void StationSetting::initTable()
{
	QStringList headerList;
	headerList << QString::fromLocal8Bit("̨վ����") << QString::fromLocal8Bit("����") <<
		QString::fromLocal8Bit("γ��")<<QString::fromLocal8Bit("��ַ");
	m_table->setHeaderItem(headerList);
	m_table->setHeaderWidth(1, 200);
}