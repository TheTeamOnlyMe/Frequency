#include "singlepatterncombox.h"
#include <qdialog.h>
SinglePatternCombox::SinglePatternCombox(QWidget *parent)
	: QWidget(parent)
	, m_typelist{0}
	, m_currentType(0)
{
	setObjectName("SinglePatternCombox");
	initLayout();
}

SinglePatternCombox::~SinglePatternCombox()
{

}
int SinglePatternCombox::getCurrentType()
{
	return m_currentType;
}
void SinglePatternCombox::clear()
{
	m_valueCombox->clear();
	m_typeCombox->clear();
}
void SinglePatternCombox::initLayout()
{
	m_layout = new QHBoxLayout(this);
	initCombox();
	m_label = new QLabel("dBuv", this);
	m_layout->addWidget(m_typeCombox);
	m_layout->addWidget(m_valueCombox);
	m_layout->addWidget(m_label);
	m_layout->setContentsMargins(20,0, 20, 0);
	setLayout(m_layout);
}
void SinglePatternCombox::initCombox()
{
	m_typeCombox = new QComboBox(this);
	QListView *dataview = new QListView(m_typeCombox);
	m_typeCombox->setView(dataview);
	m_typeCombox->view()->window()->setWindowFlag(Qt::NoDropShadowWindowHint);
	connect(m_typeCombox, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged),this, &SinglePatternCombox::changeDataType);
	m_valueCombox = new QComboBox(this);
	QListView *valueview = new QListView(m_valueCombox);
	m_valueCombox->setView(valueview);
	m_valueCombox->view()->window()->setWindowFlag(Qt::NoDropShadowWindowHint);
	connect(m_typeCombox, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &SinglePatternCombox::changeValueData);
	m_valueCombox->setEditable(true);
	m_valueCombox->setMaxVisibleItems(4);
}

void SinglePatternCombox::sendDataSlot()
{

}
void SinglePatternCombox::changeValueData(int index)
{
	QStringList list;
	m_valueCombox->clear();
	switch (m_typelist[index])
	{
	case NULL_TYPE:
		break;
	case DTBM_TYPE:
		list << "1111" << "222222" << "3333" << "44444"<<"2222"<<"333";
		m_valueCombox->addItems(list);
		break;
	case FM_TYPE:
		list << "555555" << "66666" << "7777" << "88888";
		m_valueCombox->addItems(list);
		break;
	case AM_TYPE:
		list << "999999" << "123123" << "345345" << "567567";
		m_valueCombox->addItems(list);
		break;
	case SW_TYPE:
		list << "000000000" << "3453453" << "26465" << "5436356";
		m_valueCombox->addItems(list);
		break;
	case INVALID_TYPE:
		break;
	default:
		break;
	}
}
void SinglePatternCombox::changeDataType(int index)
{
	emit changeType(m_typelist[index]);
	m_currentType = m_typelist[index];
}

void SinglePatternCombox::setType(int type)
{
	int count = 0;
	m_typeCombox->clear();
	memset(m_typelist, 0, sizeof(m_typelist));
	if ((type&ModeType::DTBM_TYPE)!=0)
	{
		m_typelist[count++] = ModeType::DTBM_TYPE;
		m_typeCombox->addItem(QString::fromLocal8Bit("数字电视"));
	}
	if ((type&ModeType::FM_TYPE) != 0)
	{
		m_typelist[count++] = ModeType::FM_TYPE;
		m_typeCombox->addItem(QString::fromLocal8Bit("调频"));
	}
	if ((type&ModeType::AM_TYPE) != 0)
	{
		m_typelist[count++] = ModeType::AM_TYPE;
		m_typeCombox->addItem(QString::fromLocal8Bit("中波"));
	}
	if ((type&ModeType::SW_TYPE) != 0)
	{
		m_typelist[count++] = ModeType::SW_TYPE;
		m_typeCombox->addItem(QString::fromLocal8Bit("短波"));
	}
}
void SinglePatternCombox::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
