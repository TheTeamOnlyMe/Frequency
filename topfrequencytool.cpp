#include "topfrequencytool.h"

TopFrequencyTool::TopFrequencyTool(QWidget *parent)
	: QWidget(parent)
	, m_valuelist{0}
{
	setObjectName("TopBar");
	m_layout = new QHBoxLayout(this);
	m_startBtn = new QPushButton(this);
	m_startBtn->setObjectName("start");
	m_startBtn->setCheckable(true);
	m_stepLeftBtn = new QPushButton( this);
	m_stepLeftBtn->setObjectName("Left");
	m_stepLeftBtn->setEnabled(true);
	m_stepRightBtn = new QPushButton( this);
	m_stepRightBtn->setObjectName("Right");
	m_stepRightBtn->setEnabled(true);
	m_screenshotBtn = new QPushButton( this);
	m_screenshotBtn->setObjectName("screenshot");
	m_combox = new QComboBox(this);
	QListView *view = new QListView(m_combox);
	m_combox->setView(view);
	m_combox->view()->window()->setWindowFlag(Qt::NoDropShadowWindowHint);
	m_label = new QLabel(QString::fromLocal8Bit("门限值："),this);
	m_label->setAlignment(Qt::AlignCenter);
	m_lineEdit = new QLineEdit(this);
	m_lineEdit->setText("30");
	m_layout->addWidget(m_combox,2);
	m_layout->addWidget(m_label,1);
	m_layout->addWidget(m_lineEdit,1);
	m_layout->addStretch(1);
	m_layout->addWidget(m_startBtn,1);
	m_layout->addSpacing(10);
	m_layout->addWidget(m_stepLeftBtn,1);
	m_layout->addSpacing(10);
	m_layout->addWidget(m_stepRightBtn,1);
	m_layout->addSpacing(10);
	m_layout->addWidget(m_screenshotBtn,1);
	m_layout->addSpacing(10);
	connect(m_startBtn, &QPushButton::clicked, this, &TopFrequencyTool::startFrequency);
	connect(m_stepLeftBtn, &QPushButton::clicked, this, &TopFrequencyTool::moveLeftClicked);
	connect(m_stepRightBtn, &QPushButton::clicked, this, &TopFrequencyTool::moveRightClicked);
	setLayout(m_layout);
}

TopFrequencyTool::~TopFrequencyTool()
{

}
void TopFrequencyTool::moveLeftClicked()
{
	emit moveLeft(m_lineEdit->text().toDouble());
}
void TopFrequencyTool::moveRightClicked()
{
	emit moveRight(m_lineEdit->text().toDouble());
}
void TopFrequencyTool::startFrequency()
{
	if (m_startBtn->isChecked())
	{
		emit startLimitData(m_lineEdit->text().toDouble());
		m_combox->setEnabled(false);
		m_lineEdit->setEnabled(false);
		m_stepRightBtn->setEnabled(false);
		m_stepLeftBtn->setEnabled(false);
	}
	else {
		emit clearData();
		m_combox->setEnabled(true);
		m_lineEdit->setEnabled(true);
		m_stepRightBtn->setEnabled(true);
		m_stepLeftBtn->setEnabled(true);
	}
}
void TopFrequencyTool::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void TopFrequencyTool::setType(int type)
{
	m_combox->clear();
	int count = 0;
	if ((type&ModeType::DTBM_TYPE) != ModeType::NULL_TYPE) {
		m_valuelist[count++] = ModeType::DTBM_TYPE;
		m_combox->addItem(QString::fromLocal8Bit("数字电视"));
	}
	if ((type&ModeType::FM_TYPE) != ModeType::NULL_TYPE) {
		m_valuelist[count++] = ModeType::FM_TYPE;
		m_combox->addItem(QString::fromLocal8Bit("调频"));
	}
	if ((type&ModeType::AM_TYPE) != ModeType::NULL_TYPE)
	{
		m_valuelist[count++] = ModeType::AM_TYPE;
		m_combox->addItem(QString::fromLocal8Bit("中波"));
	}
	connect(m_combox, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &TopFrequencyTool::changeValueData);
}
void TopFrequencyTool::setValue(QString value)
{
	m_lineEdit->setText(value);
}
void TopFrequencyTool::changeValueData(int index)
{
	emit changeType(m_valuelist[index]);
}