#include "operationbuttonbar.h"

OperationButtonBar::OperationButtonBar(QWidget *parent)
	: QWidget(parent)
	, m_nButtonCount(0)
{
	this->setParent(parent);
	setObjectName("OperationButtonBar");
	setContentsMargins(0, 0, 0, 0);
	init();
}

OperationButtonBar::~OperationButtonBar()
{

}
void OperationButtonBar::init()
{
	m_pLayout = new QVBoxLayout(this);
	m_pBtnGroup = new QButtonGroup(this);
	m_pBtnGroup->setExclusive(true);

}


void OperationButtonBar::addOperatButtons(QStringList buttonsName)
{
	m_pLayout->addStretch();
	for (int num = 0; num < buttonsName.size(); num++)
	{
		QAbstractButton *pButton = new QPushButton(this);
		pButton->setObjectName("OperationBar");
		pButton->setText(buttonsName.at(num));
		pButton->setCheckable(true);
		m_pLayout->addWidget(pButton);
		m_pBtnGroup->addButton(pButton, num);
	}
	m_pBtnGroup->button(0)->setChecked(true);
	m_nButtonCount = buttonsName.size();
	m_pLayout->setContentsMargins(0,10,0,10);
	m_pLayout->addStretch();
	QPushButton *closeBtn = new QPushButton(this);
	closeBtn->setObjectName("prePage");
	connect(m_pBtnGroup, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), this, &OperationButtonBar::clicked);
	connect(closeBtn, &QPushButton::clicked, this, &OperationButtonBar::slotReturnBtn);
	m_pLayout->addWidget(closeBtn,0,Qt::AlignCenter);
}

void OperationButtonBar::setBtnlayout()
{
	setLayout(m_pLayout);
}
void OperationButtonBar::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void OperationButtonBar::slotReturnBtn()
{
	emit returnMainPage();
}