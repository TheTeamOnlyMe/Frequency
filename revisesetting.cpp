#include "revisesetting.h"
#include <qpushbutton.h>

ReviseSetting::ReviseSetting(QWidget *parent)
	: QWidget(parent)
	, count(1)
{
	setObjectName("settingPage");
	m_layout = new QGridLayout(this);
	QLabel *title = new QLabel(QString::fromLocal8Bit("У��ֵ����"), this);
	title->setObjectName("Title");
	m_layout->addWidget(title, 0, 0);
	addSetOption(QString::fromLocal8Bit("��Ƶ����:"));
	addSetOption(QString::fromLocal8Bit("��������:"));
	addSetOption(QString::fromLocal8Bit("�̲�����:"));
	addSetOption(QString::fromLocal8Bit("DTMB����:"));
	setLayout(m_layout);
}

ReviseSetting::~ReviseSetting()
{

}
void ReviseSetting::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ReviseSetting::addSetOption(QString name)
{
	count++;
	QLabel *label = new QLabel(name, this);
	label->setAlignment(Qt::AlignCenter);
	QPushButton *settingBtn = new QPushButton(this);
	settingBtn->setObjectName("onOffBtn");
	settingBtn->setCheckable(true);
	QLabel *valueLabel = new QLabel(QString::fromLocal8Bit("������ֵ:"), this);
	valueLabel->setAlignment(Qt::AlignCenter);
	QLineEdit *lineEidt = new QLineEdit(this);
	QPushButton *submitBtn = new QPushButton(this);
	submitBtn->setObjectName("submitBtn");
	lineEidt->setEnabled(false);
	submitBtn->setEnabled(false);
	connect(settingBtn, &QPushButton::clicked, lineEidt, &QLineEdit::setEnabled);
	connect(settingBtn, &QPushButton::clicked, submitBtn, &QPushButton::setEnabled);
	m_layout->addWidget(label, count, 0);
	m_layout->addWidget(settingBtn, count, 1);
	m_layout->addWidget(valueLabel, count+1, 0);
	m_layout->addWidget(lineEidt, count+1, 1);
	m_layout->addWidget(submitBtn, count+1, 2);
	count++;
}
void ReviseSetting::widgetStatus()
{

}