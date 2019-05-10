#include "toptesttool.h"

TopTestTool::TopTestTool(QWidget *parent)
	: QWidget(parent)
	, m_bStartTest(false)
	, m_bSelectSigle(false)
{
	//����ģ�鹤����
	setObjectName("TopBar");
	m_mainLayout = new QHBoxLayout(this);
	m_modeChangeBtn = new QPushButton(this);
	m_modeChangeBtn->setText(QString::fromLocal8Bit("����ģʽ"));
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

	connect(this, &TopTestTool::setTypeList, m_customCombox, &SinglePatternCombox::setType);			//�޸ĵ�ǰ�������ͣ�DTMB/FM/AM/SW��
	connect(this, &TopTestTool::setTypeList, m_cycliCombox, &CyclePatternConbox::setType);			//�޸ĵ�ǰ�������ͣ�DTMB/FM/AM/SW��
	connect(m_customCombox, &SinglePatternCombox::changeType, this, &TopTestTool::setBarCell);	//���ݵ���ģʽ��Comboxֵ�л���������ť״̬
	connect(m_cycliCombox, &CyclePatternConbox::changeType, this, &TopTestTool::setBarCell);	//���ݵ���ģʽ��Comboxֵ�л���������ť״̬
	connect(m_modeChangeBtn, &QPushButton::clicked, this, &TopTestTool::changeMode);				//����ģʽ��ѭ��ģʽ�л���ť
	connect(m_startControlBtn, &QPushButton::clicked,this, &TopTestTool::changeCombox);			//��ʼ��ͣ���ư�ť
	m_startControlBtn->setChecked(false);
}

TopTestTool::~TopTestTool()
{

}
/*
	��ʼʱ�����ÿؼ���ֵ�޷��޸�
	ģʽ�л���ť��������ֵcombox�ؼ�
*/
void TopTestTool::changeCombox(bool bstart)
{
	emit startTest(!bstart);
	emit startPainLimitLine(!bstart);
	m_modeChangeBtn->setEnabled(!bstart);

}
/*��ʼ���ؼ�*/
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
		m_modeChangeBtn->setText(QString::fromLocal8Bit("����ģʽ"));
		m_stackLayout->setCurrentIndex(0);
		m_bSelectSigle = false;
	}
	else {
		setBarCell(m_cycliCombox->getCurrentType());
		m_bSelectSigle = true;
		m_modeChangeBtn->setText(QString::fromLocal8Bit("ѭ��ģʽ"));
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
	����Ƶ��������ʾ��ӦԪ��
	���ֵ���ģʽ�£���ʾ�ྶ����������ͼ
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
