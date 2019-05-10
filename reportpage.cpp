#include "reportpage.h"

ReportPage::ReportPage(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("reportVLayout");
	m_hLayout = new QHBoxLayout(this);
	m_rightBar = new OperationButtonBar(this);
	QStringList buttonlist;
	buttonlist << QString::fromLocal8Bit("导出数据") << QString::fromLocal8Bit("生成报告");
	m_rightBar->addOperatButtons(buttonlist);
	m_hLayout->addStretch();
	m_hLayout->addWidget(m_rightBar);
	//m_hLayout->setStretchFactor(m_rightBar,1);
	connect(m_rightBar, &OperationButtonBar::returnMainPage, this, &ReportPage::changePage);
	m_hLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_hLayout);

}

ReportPage::~ReportPage()
{

}
void ReportPage::changePage()
{
	emit returnNavigation(PageIndex::NAVIGATION);
}
void ReportPage::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
