#include "frequencysetting.h"

FrequencySetting::FrequencySetting(QWidget *parent)
	: QWidget(parent)
	, m_typeList(0)
{
	m_layout = new QHBoxLayout(this);
	m_table = new CustomTableView(this);
	connect(this, &FrequencySetting::setTypeList, m_table, &CustomTableView::setTypeList);	//���񴫵ݲ�������DMTB��FM��AM��SW
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
	headerList <<QString::fromLocal8Bit("̨վ����") << QString::fromLocal8Bit("Ƶ��") <<
		QString::fromLocal8Bit("����") ;
	m_table->setCheckButtonExclusive(false);//���ð�ť����
	m_table->setHeaderItem(headerList);
	//m_table->setHeaderWidth(1, 30);
	m_table->setHeaderWidth(1, 200);
}
void FrequencySetting::createForm(const FrequencyDataRecord &index,int rowcount)
{
	m_frequencyForm = new FrequencyConfigForm(this);
	connect(this, &FrequencySetting::setType, m_frequencyForm, &FrequencyConfigForm::setTypeList);

	emit setType(m_typeList);
	connect(this, &FrequencySetting::processData, m_frequencyForm, &FrequencyConfigForm::processData);//ͨ���������������
	emit processData(index, rowcount);

	connect(m_frequencyForm, &FrequencyConfigForm::addData, m_table, &CustomTableView::addRowData);//ͨ�����������һ������
	connect(m_frequencyForm, &FrequencyConfigForm::modifyData, m_table, &CustomTableView::modifyRowData);//ͨ���������޸�һ������
	connect(m_frequencyForm, &FrequencyConfigForm::closeFrom, this, &FrequencySetting::closeForm);//�رձ����棬���ͷ��ڴ�


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
