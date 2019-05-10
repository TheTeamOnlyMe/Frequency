#include "stationconfigform.h"

StationConfigForm::StationConfigForm(QWidget *parent)
	: QDialog(parent)
	, m_pageIndex(0)
{
	m_layout = new QHBoxLayout(this);
	m_acceptbutton = new QPushButton(this);
	connect(m_acceptbutton, &QPushButton::clicked, this, &StationConfigForm::closeForm);
	m_layout->addWidget(m_acceptbutton);
	setLayout(m_layout);
}

StationConfigForm::~StationConfigForm()
{

}
void StationConfigForm::closeForm()
{
	emit destroyForm(m_pageIndex);
	close();
}
