#include "frequencysetting.h"

FrequencySetting::FrequencySetting(QWidget *parent)
	: QWidget(parent)
	, m_typeList(0)
{
	m_layout = new QHBoxLayout(this);
	m_table = new CustomTableView(this);
	connect(this, &FrequencySetting::setTypeList, m_table, &CustomTableView::setTypeList);	//向表格传递测试类型DMTB、FM、AM、SW
	//connect(this, &FrequencySetting::setTypeList, m_table, &CustomTableView::showDataByType);
	//connect(this, &FrequencySetting::currentChanged, m_table, &CustomTableView::currentChanged);
	connect(m_table, &CustomTableView::createForm, this, &FrequencySetting::createForm);
	initTable();
	m_layout->addWidget(m_table);
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
}

FrequencySetting::~FrequencySetting()
{

}
void FrequencySetting::initTable()
{
	QStringList headerList;
	headerList <<QString::fromLocal8Bit("台站名称") << QString::fromLocal8Bit("频率") <<
		QString::fromLocal8Bit("类型") ;
	m_table->setCheckButtonExclusive(false);//设置按钮互斥
	m_table->setHeaderItem(headerList);
	//m_table->setHeaderWidth(1, 30);
	m_table->setHeaderWidth(1, 200);
}
void FrequencySetting::createForm(const FrequencyDataRecord &index,int rowcount)
{
	m_frequencyForm = new FrequencyConfigForm(this);
	connect(this, &FrequencySetting::setType, m_frequencyForm, &FrequencyConfigForm::setTypeList);

	emit setType(m_typeList);
	connect(this, &FrequencySetting::processData, m_frequencyForm, &FrequencyConfigForm::processData);//通过表格向表单添加数据
	emit processData(index, rowcount);

	connect(m_frequencyForm, &FrequencyConfigForm::addData, m_table, &CustomTableView::addRowData);//通过表单向表格添加一条数据
	connect(m_frequencyForm, &FrequencyConfigForm::modifyData, m_table, &CustomTableView::modifyRowData);//通过表单向表格修改一条数据
	connect(m_frequencyForm, &FrequencyConfigForm::closeFrom, this, &FrequencySetting::closeForm);//关闭表单界面，并释放内存


}
void FrequencySetting::setTypeList(int typelist)
{
	m_typeList = typelist;
}
void FrequencySetting::closeForm()
{
	m_frequencyForm->close();
	if (m_frequencyForm != nullptr) {
		m_frequencyForm->~FrequencyConfigForm();
	}
}
