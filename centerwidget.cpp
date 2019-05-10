#include "centerwidget.h"
CenterWidget::CenterWidget(QWidget *parent)
	: QWidget(parent)
	, m_nselectedMode(0)
{
	this->setParent(parent);
	m_pageNavigation = new NavigationPage(this->parentWidget());
	m_pageTestMode = new TestModePage(this);
	m_pageReport = new ReportPage(this);
	m_pageRecord = new RecordPage(this);

	m_animationStackedWidget = new XAnimationStackedWidget();
	m_animationStackedWidget->insertWidget(0,m_pageNavigation);
	m_animationStackedWidget->insertWidget(1,m_pageTestMode);
	m_animationStackedWidget->insertWidget(2,m_pageReport);
	m_animationStackedWidget->insertWidget(3,m_pageRecord);
	m_animationStackedWidget->setCurrentWidget(m_pageNavigation);
	connection();
	m_pStackLayout = new QStackedLayout(this);
	m_pStackLayout->addWidget(m_animationStackedWidget);
	setLayout(m_pStackLayout);
}

CenterWidget::~CenterWidget()
{
	if (m_animationStackedWidget)
	{
		delete m_animationStackedWidget;
		m_animationStackedWidget = NULL;
	}
}
void CenterWidget::connection()
{
	connect(m_pageNavigation, &NavigationPage::changePage, this, &CenterWidget::changePage);
	connect(m_pageNavigation, &NavigationPage::modeType, this, &CenterWidget::selectedMode);
	connect(this, &CenterWidget::changePageStacked, m_animationStackedWidget, &XAnimationStackedWidget::next);
	connect(m_pageTestMode, &TestModePage::returnNavigation, m_animationStackedWidget, &XAnimationStackedWidget::forward);
	connect(m_pageReport, &ReportPage::returnNavigation, m_animationStackedWidget, &XAnimationStackedWidget::forward);
	connect(m_pageRecord, &RecordPage::returnNavigation, m_animationStackedWidget, &XAnimationStackedWidget::forward);
	connect(this, &CenterWidget::setTypeList, m_pageTestMode, &TestModePage::setTypeList);

}

void CenterWidget::changePage(int pageIndex)
{
	if (pageIndex == PageIndex::TESTMODE && (m_nselectedMode & ModeType::INVALID_TYPE) == 0)
		return;
	emit changePageStacked(pageIndex);
}
void CenterWidget::selectedMode(int modeType)
{
	m_nselectedMode = modeType;
	emit setTypeList(modeType);
}
