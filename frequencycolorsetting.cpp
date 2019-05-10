#include "frequencycolorsetting.h"

FrequencyColorSetting::FrequencyColorSetting(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QHBoxLayout(this);
	m_table = new CustomTableView(this);
	connect(this, &FrequencyColorSetting::setTypeList, m_table, &CustomTableView::setTypeList);
	//connect(this, &FrequencyColorSetting::setTypeList, m_table, &CustomTableView::showDataByType);
	initTable();
	m_layout->addWidget(m_table);
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
}

FrequencyColorSetting::~FrequencyColorSetting()
{

}
void FrequencyColorSetting::initTable()
{
	QStringList headerList;
	headerList << QString::fromLocal8Bit("开始门限值") << 
		QString::fromLocal8Bit("结束门限值") <<
		QString::fromLocal8Bit("颜色值");
	m_table->setHiddenColumn(0);
	//m_table->setHiddenColumn(4);
	m_table->hideStatusButton(true);
	m_table->setHeaderItem(headerList);
	m_table->setHeaderWidth(1, 200);
}