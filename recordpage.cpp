#include "recordpage.h"

RecordPage::RecordPage(QWidget *parent)
	: QWidget(parent)
{
	m_hLayout = new QHBoxLayout(this);
	m_rightBar = new OperationButtonBar(this);
	QStringList buttonlist;
	buttonlist << QString::fromLocal8Bit("�鿴�ɼ���") << QString::fromLocal8Bit("ͳ��")<< QString::fromLocal8Bit("�鿴����");
	m_rightBar->addOperatButtons(buttonlist);
	connect(m_rightBar, &OperationButtonBar::returnMainPage, this, &RecordPage::changePage);
	m_hLayout->addStretch();
	m_hLayout->addWidget(m_rightBar);
	m_hLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_hLayout);
}

RecordPage::~RecordPage()
{

}
void RecordPage::changePage()
{
	emit returnNavigation(PageIndex::NAVIGATION);
}