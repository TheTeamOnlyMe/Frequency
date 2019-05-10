#include "cyclepatternconbox.h"

CyclePatternConbox::CyclePatternConbox(QWidget *parent)
	: QWidget(parent)
	, m_currentType(0)
{
	setObjectName("CustomCombox");
	m_layout = new QHBoxLayout(this);
	m_label = new QLabel("dBuv",this);
	m_combox = new QComboBox(this);
	QListView *view = new QListView(m_combox);
	m_combox->setView(view);
	m_combox->view()->window()->setWindowFlag(Qt::NoDropShadowWindowHint);
	connect(m_combox, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &CyclePatternConbox::changeDataType);
	m_layout->addWidget(m_combox);
	m_layout->addStretch();
	m_layout->addWidget(m_label);
	m_layout->setContentsMargins(20, 0, 20, 0);
	setLayout(m_layout);
	initData();
}

CyclePatternConbox::~CyclePatternConbox()
{

}
void CyclePatternConbox::clear()
{
	m_currentType = 0;
}
int CyclePatternConbox::getCurrentType()
{
	return m_currentType;
}
void CyclePatternConbox::changeDataType(int index)
{
	if (m_vtShowData.size() <= 0) return;
	emit changeType(m_vtShowData.at(index).typeID);
	m_currentType = m_vtShowData.at(index).typeID;
}
/////////////////////////////////////Debug Test/////////////////////////////////////////////////
void CyclePatternConbox::initData()
{
	TestData data;
	m_vtAllData.clear();
	for (int i = 0; i < 3; i++)
	{
		data.typeID = ModeType::DTBM_TYPE;
		data.typeName = QString::fromLocal8Bit("数字电视：");
		data.value = qrand()%1000+1;
		m_vtAllData.append(data);
	}
	for (int i = 0; i < 4; i++)
	{
		data.typeID = ModeType::FM_TYPE;
		data.typeName = QString::fromLocal8Bit("调频：");
		data.value = qrand() % 1000 + 1;
		m_vtAllData.append(data);
	}
	for (int i = 0; i < 4; i++)
	{
		data.typeID = ModeType::AM_TYPE;
		data.typeName = QString::fromLocal8Bit("中波：");
		data.value = qrand() % 1000 + 1;
		m_vtAllData.append(data);
	}
	for (int i = 0; i < 4; i++)
	{
		data.typeID = ModeType::SW_TYPE;
		data.typeName = QString::fromLocal8Bit("短波：");
		data.value = qrand() % 1000 + 1;
		m_vtAllData.append(data);
	}
}
//////////////////////////////////////////////////////////////////////////////////////

void CyclePatternConbox::setData(QStringList slist)
{

}

void CyclePatternConbox::setType(int type)
{
	m_vtShowData.clear();
	m_combox->clear();
	addData(type, ModeType::DTBM_TYPE);
	addData(type, ModeType::FM_TYPE);
	addData(type, ModeType::AM_TYPE);
	addData(type, ModeType::SW_TYPE);
}

void CyclePatternConbox::addData(int typeList ,int modeType)
{
	QString list;
	if ((typeList&modeType) != 0)
	{
		for (int i = 0; i < m_vtAllData.size(); i++)
		{
			if (m_vtAllData.at(i).typeID == modeType) {
				m_vtShowData.append(m_vtAllData.at(i));
				list= QString("%1 %2").arg(m_vtAllData.at(i).typeName).arg(m_vtAllData.at(i).value);
				m_combox->addItem(list);
			}
		}
	}
}

void CyclePatternConbox::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}