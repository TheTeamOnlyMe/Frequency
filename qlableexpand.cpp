#include "qlableexpand.h"

QLableExpand::QLableExpand( QWidget *parent,QString sname,bool b_showorhide )
	: QWidget(parent)
{
	QHBoxLayout * layout =new QHBoxLayout(this);
	lab_name =new QLabel(sname,this);

	lab_value =new QLabel("N/A",this);

	layout->addWidget(lab_name);
	layout->addStretch(); 
	layout->addWidget(lab_value);
	lab_name->setObjectName("labtest");
	lab_value->setObjectName("labtest");
	layout->setContentsMargins(0,0,0,0);
	lab_name->setFixedHeight(20);
	lab_value->setFixedHeight(20);
	this->setLayout(layout);
	if (b_showorhide)
	   this->show();
	else this->hide();
	
	
}


QLableExpand::~QLableExpand()
{}

void QLableExpand::SetValue( QString svalue )
{
	if (lab_value !=NULL)
		lab_value->setText(svalue);
}

void QLableExpand::SetName( QString sname )
{
	if (lab_name !=NULL)
		lab_name->setText(sname);
}

QString QLableExpand::GetValue()
{
	if (lab_value !=NULL)
	 return	lab_value->text().trimmed();
	else return NULL;
}

void QLableExpand::SetNull()
{
	if (lab_value !=NULL)
		lab_value->setText("N/A");
}	