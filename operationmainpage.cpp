#include "operationmainpage.h"

OperationMainPage::OperationMainPage(QWidget *parent)
	: QWidget(parent)
{
	//二级主界面
	m_pStackPageLayout = new QStackedLayout(this);
	setObjectName("test");

	m_pageTest = new TestPage(this);					//测试界面
	m_widgetPlot = new CustomPlotPage(this);			//扫频界面
	m_settingPage = new SettingPage(this);				//设置界面
	connect(this, &OperationMainPage::changeTestPage, m_pageTest, &TestPage::changePage);					//通过上方页面按钮切换测试页面的子页面
	connect(this, &OperationMainPage::changeFrequencyRange, m_widgetPlot, &CustomPlotPage::setRangeByType);	//根据当前类型值显示扫频页面格式
	connect(this, &OperationMainPage::setFrequencyLimitData, m_widgetPlot, &CustomPlotPage::setData);		//根据类型设置扫频页面坐标xy最大值
	connect(this, &OperationMainPage::clearData, m_widgetPlot, &CustomPlotPage::clearData);					//清理plot数据
	connect(this, &OperationMainPage::changeSettingPage, m_settingPage, &SettingPage::changeSettingPage);	//通过上方页面按钮切换设置页面的子页面
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
