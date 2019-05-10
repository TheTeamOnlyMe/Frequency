#include "toptesttool.h"

TopTestTool::TopTestTool(QWidget *parent)
	: QWidget(parent)
	, m_bStartTest(false)
	, m_bSelectSigle(false)
{
	//测试模块工具栏
	setObjectName("TopBar");
	m_mainLayout = new QHBoxLayout(this);
	m_modeChangeBtn = new QPushButton(this);
	m_modeChangeBtn->setText(QString::fromLocal8Bit("单点模式"));
	initLeftButton();
	initCombox();

	m_startControlBtn = new QPushButton(this);
	m_startControlBtn->setObjectName("TestStart");
	m_startControlBtn->setCheckable(true);
	m_mainLayout->addStretch();
	m_mainLayout->addItem(m_stackLayout);
	m_mainLayout->addWidget(m_modeChangeBtn);
	m_mainLayout->addStretch();
	m_mainLayout->addWidget(m_startControlBtn);

	m_mainLayout->setContentsMargins(8, 8, 20,8);
	setLayout(m_mainLayout);

	connect(this, &TopTestTool::setTypeList, m_customCombox, &SinglePatternCombox::setType);			//修改当前测试类型（DTMB/FM/AM/SW）
	connect(this, &TopTestTool::setTypeList, m_cycliCombox, &CyclePatternConbox::setType);			//修改当前测试类型（DTMB/FM/AM/SW）
	connect(m_customCombox, &SinglePatternCombox::changeType, this, &TopTestTool::setBarCell);	//根据单点模式的Combox值切换工具栏按钮状态
	connect(m_cycliCombox, &CyclePatternConbox::changeType, this, &TopTestTool::setBarCell);	//根据单点模式的Combox值切换工具栏按钮状态
	connect(m_modeChangeBtn, &QPushButton::clicked, this, &TopTestTool::changeMode);				//单点模式、循环模式切换按钮
	connect(m_startControlBtn, &QPushButton::clicked,this, &TopTestTool::changeCombox);			//开始暂停控制按钮
	m_startControlBtn->setChecked(false);
}

TopTestTool::~TopTestTool()
{

}
/*
	开始时，设置控件数值无法修改
	模式切换按钮、类型数值combox控件
*/
void TopTestTool::changeCombox(bool bstart)
{
	emit startTest(!bstart);
	emit startPainLimitLine(!bstart);
	m_modeChangeBtn->setEnabled(!bstart);

}
/*初始化控件*/
void TopTestTool::initCombox()
{
	m_customCombox = new SinglePatternCombox(this);
	m_cycliCombox = new CyclePatternConbox(this);
	m_stackLayout = new QStackedLayout(this);

	m_stackLayout->setObjectName("toptesttool");
	m_stackLayout->setContentsMargins(0, 0, 0, 0);
	m_stackLayout->addWidget(m_customCombox);
	m_stackLayout->addWidget(m_cycliCombox);
	connect(this, &TopTestTool::startPainLimitLine, m_customCombox, &SinglePatternCombox::setEnabled);
	connect(this, &TopTestTool::startPainLimitLine, m_cycliCombox, &CyclePatternConbox::setEnabled);
	m_stackLayout->setCurrentIndex(0);
}
void TopTestTool::stopTest()
{
	//m_customCombox->clear();
	//m_cycliCombox->clear();
	emit startTest(true);
	emit startPainLimitLine(true);
	m_modeChangeBtn->setEnabled(true);
	m_startControlBtn->setChecked(false);
}

void TopTestTool::changeMode()
{
	if (m_bSelectSigle) {
		setBarCell(m_customCombox->getCurrentType());
		m_modeChangeBtn->setText(QString::fromLocal8Bit("单点模式"));
		m_stackLayout->setCurrentIndex(0);
		m_bSelectSigle = false;
	}
	else {
		setBarCell(m_cycliCombox->getCurrentType());
		m_bSelectSigle = true;
		m_modeChangeBtn->setText(QString::fromLocal8Bit("循环模式"));
		m_stackLayout->setCurrentIndex(1);
	}
}
void TopTestTool::initLeftButton() {
	m_leftBtnGroup = new QButtonGroup(this);
	setLeftBtn("TESTDATABUTTON", LeftBtnNum::TESTDATABUTTON);
	setLeftBtn("MAPBUTTON", LeftBtnNum::MAPBUTTON);
	setLeftBtn("MULTIPATHBTN", LeftBtnNum::MULTIPATHBTN);
	setLeftBtn("STARMAPBTN", LeftBtnNum::STARMAPBTN);
	connect(m_leftBtnGroup, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), this, &TopTestTool::changeTestPage);
	m_leftBtnGroup->button(LeftBtnNum::TESTDATABUTTON)->setChecked(true);
}

void TopTestTool::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void TopTestTool::setLeftBtn(QString btnName,int btnNum)
{
	QAbstractButton *button = new QPushButton(this);
	button->setCheckable(true);
	button->setObjectName(btnName);
	m_mainLayout->addWidget(button);
	m_mainLayout->addSpacing(10);
	m_leftBtnGroup->addButton(button, btnNum);
}
/*
	根据频率类型显示对应元素
	数字电视模式下：显示多径分析、星座图
*/
void TopTestTool::setBarCell(int modeType)
{
	emit setType(modeType);
	if (modeType==ModeType::DTBM_TYPE) {
		m_leftBtnGroup->button(LeftBtnNum::STARMAPBTN)->setEnabled(true);
		m_leftBtnGroup->button(LeftBtnNum::MULTIPATHBTN)->setEnabled(true);
	}
	else {
		m_leftBtnGroup->button(LeftBtnNum::STARMAPBTN)->setEnabled(false);
		m_leftBtnGroup->button(LeftBtnNum::MULTIPATHBTN)->setEnabled(false);
	}
}
