#include "customsprogressbar.h"

CustomSprogressBar::CustomSprogressBar(QWidget *parent)
	: QWidget(parent)
{
	//ÒôÖù
	setMaximumWidth(100);
	setMinimumWidth(100);
	m_VLayout = new QVBoxLayout(this);
	m_sprogressBar = new SprogressBar(this);
	m_name = new QLabel("Text",this);
	m_name->setObjectName("SprogressName");
	m_name->setAlignment(Qt::AlignHCenter);
	m_name->setFixedHeight(20);
	m_sprogressBar->setRange(0, 100);
	m_VLayout->addWidget(m_sprogressBar);
	m_VLayout->addWidget(m_name);
	m_VLayout->setContentsMargins(10,20,10,20);

	this->setLayout(m_VLayout);
}

CustomSprogressBar::~CustomSprogressBar()
{

}
void CustomSprogressBar::animationBuffer()
{
	
}
void CustomSprogressBar::setValue(int value)
{
	qDebug() << "value"<<value;
	m_sprogressBar->setValue(value);
}
void CustomSprogressBar::setNull()
{
	m_sprogressBar->setValue(0);
	update();
}

void CustomSprogressBar::setBarName(QString name)
{
	m_name->setText(name);
}