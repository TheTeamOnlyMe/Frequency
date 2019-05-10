#include "operationmainpage.h"

OperationMainPage::OperationMainPage(QWidget *parent)
	: QWidget(parent)
{
	//����������
	m_pStackPageLayout = new QStackedLayout(this);
	setObjectName("test");

	m_pageTest = new TestPage(this);					//���Խ���
	m_widgetPlot = new CustomPlotPage(this);			//ɨƵ����
	m_settingPage = new SettingPage(this);				//���ý���
	connect(this, &OperationMainPage::changeTestPage, m_pageTest, &TestPage::changePage);					//ͨ���Ϸ�ҳ�水ť�л�����ҳ�����ҳ��
	connect(this, &OperationMainPage::changeFrequencyRange, m_widgetPlot, &CustomPlotPage::setRangeByType);	//���ݵ�ǰ����ֵ��ʾɨƵҳ���ʽ
	connect(this, &OperationMainPage::setFrequencyLimitData, m_widgetPlot, &CustomPlotPage::setData);		//������������ɨƵҳ������xy���ֵ
	connect(this, &OperationMainPage::clearData, m_widgetPlot, &CustomPlotPage::clearData);					//����plot����
	connect(this, &OperationMainPage::changeSettingPage, m_settingPage, &SettingPage::changeSettingPage);	//ͨ���Ϸ�ҳ�水ť�л�����ҳ�����ҳ��
	connect(this, &OperationMainPage::setTypeList, m_settingPage, &SettingPage::setTypeList);
	/***************TestPage connect*********************/
	connect(this, &OperationMainPage::stopTest, m_pageTest, &TestPage::stopTest);
	connect(this, &OperationMainPage::moveLeft, m_widgetPlot, &CustomPlotPage::leftStepOne);
	connect(this, &OperationMainPage::moveRight, m_widgetPlot, &CustomPlotPage::rightStepOne);
	connect(this, &OperationMainPage::setType, m_pageTest, &TestPage::setType);
	connect(this, &OperationMainPage::startTest, m_pageTest, &TestPage::startTest);
	m_pStackPageLayout->addWidget(m_pageTest);
	m_pStackPageLayout->addWidget(m_widgetPlot);
	m_pStackPageLayout->addWidget(m_settingPage);
	m_pStackPageLayout->setCurrentWidget(m_pageTest);
	setLayout(m_pStackPageLayout);
}

OperationMainPage::~OperationMainPage()
{

}
void OperationMainPage::setCurrentIndex(int index)
{
	m_pStackPageLayout->setCurrentIndex(index);
	//update();
}
void OperationMainPage::startPainLimitLine(double limitValue)
{
	QVector<double> xData(500),yData(500);
	for (int i = 0; i < 500; i++)
	{
		xData[i] = i;
		yData[i] = limitValue;
	}
	emit setFrequencyLimitData(1, xData, yData);
}


void OperationMainPage::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
