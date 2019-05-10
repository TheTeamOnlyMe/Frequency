#include "cyclesetting.h"

CycleSetting::CycleSetting(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("settingPage");
	m_layout = new QGridLayout(this);
	QLabel *title = new QLabel(QString::fromLocal8Bit("循环设置"), this);
	title->setObjectName("Title");
	QLabel *cycleTest = new QLabel(QString::fromLocal8Bit("循环测试:"), this);
	cycleTest->setAlignment(Qt::AlignCenter);
	QLabel *intervalTime = new QLabel(QString::fromLocal8Bit("间隔时间:"), this);
	intervalTime->setAlignment(Qt::AlignCenter);
	QPushButton *test = new QPushButton(this);
	test->setObjectName("cycleBtn");
	QLineEdit *lineEdit = new QLineEdit(this);
	QPushButton *submit = new QPushButton(this);
	submit->setObjectName("submitBtn");
	test->setCheckable(true);
	lineEdit->setEnabled(false);
	submit->setEnabled(false);
	connect(test, &QPushButton::clicked, lineEdit, &QLineEdit::setEnabled);
	connect(test, &QPushButton::clicked, submit, &QPushButton::setEnabled);
	m_layout->addWidget(title, 0, 0);
	m_layout->addWidget(cycleTest, 1, 0);
	m_layout->addWidget(intervalTime, 2, 0);
	m_layout->addWidget(test, 1, 1);
	m_layout->addWidget(lineEdit, 2, 1);
	m_layout->addWidget(submit, 2, 2);
	m_layout->setContentsMargins(10,0,10,20);
	setLayout(m_layout);

}

CycleSetting::~CycleSetting()
{

}
void CycleSetting::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}