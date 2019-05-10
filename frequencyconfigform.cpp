#include "frequencyconfigform.h"

FrequencyConfigForm::FrequencyConfigForm(QWidget *parent)
	: QDialog(parent)
	, m_currentRow(0)
	, m_formType(0)
	, m_pageIndex(0)
{
	setObjectName("dataForm");
	setWindowModality(Qt::WindowModal);
	resize(400, 300);
	setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	init();
	show();
}

FrequencyConfigForm::~FrequencyConfigForm()
{

}
bool FrequencyConfigForm::event(QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		if (ke->key() == Qt::Key_Escape)
		{
			emit closeFrom();
			return true;
		}
	}

	return QWidget::event(event);
}
void FrequencyConfigForm::init()
{
	m_layout = new QGridLayout(this);
	m_acceptButton = new QPushButton(this);
	m_acceptButton->setText(QString::fromLocal8Bit("确定"));
	m_closeButton = new QPushButton(this);
	m_closeButton->setText(QString::fromLocal8Bit("取消"));
	connect(m_acceptButton, &QPushButton::clicked, this, &FrequencyConfigForm::acceptData);//提交表单数据修改表格
	//关闭表单，并释放内存
	connect(m_acceptButton, &QPushButton::clicked, this, &FrequencyConfigForm::closeFrom);
	connect(m_closeButton, &QPushButton::clicked, this, &FrequencyConfigForm::closeFrom);

	//表单界面控件布局
	m_layout->addWidget(new QLabel(QString::fromLocal8Bit("台站名称："), this), 0, 0);
	m_stationCombox = new QComboBox(this);
	QListView *valueview = new QListView(m_stationCombox);
	m_stationCombox->setView(valueview);
	m_stationCombox->view()->window()->setWindowFlag(Qt::NoDropShadowWindowHint);
	m_stationCombox->setObjectName("dataForm");
	m_layout->addWidget(m_stationCombox, 0, 1);
	m_layout->addWidget(new QLabel(QString::fromLocal8Bit("频率类型："), this), 0, 2);
	m_typeCombox = new QComboBox(this);
	QListView *typeview = new QListView(m_typeCombox);
	m_typeCombox->setView(typeview);
	m_typeCombox->view()->window()->setWindowFlag(Qt::NoDropShadowWindowHint);
	m_typeCombox->setObjectName("dataForm");
	m_layout->addWidget(m_typeCombox, 0, 3);
	m_layout->addWidget(new QLabel(QString::fromLocal8Bit("频道值  ："), this), 1, 0);
	m_lineEdit = new QLineEdit(this);
	m_lineEdit->setObjectName("dataForm");
	m_layout->addWidget(m_lineEdit, 1, 1);
	m_layout->addWidget(new QLabel(QString::fromLocal8Bit("自动搜台："), this), 1, 2);
	m_autoBtn = new QPushButton(this);
	m_autoBtn->setObjectName("dataForm");
	m_layout->addWidget(m_autoBtn, 1, 3);
	m_layout->addWidget(m_acceptButton, 2, 1);
	m_layout->addWidget(m_closeButton, 2, 2);
	m_layout->setColumnMinimumWidth(0, 100);
	m_layout->setColumnMinimumWidth(1, 100);
	m_layout->setColumnMinimumWidth(2, 100);
	m_layout->setColumnMinimumWidth(3, 100);
	setLayout(m_layout);
}
void FrequencyConfigForm::closeFrequncyDialog()
{
	//emit closeFrom();
	//close();
}
//确定按钮提交表单
void FrequencyConfigForm::acceptData()
{

	//保存数据
	QStringList  data;
	data << QString::number(m_currentRow);
	data << QString::fromLocal8Bit("大蜀山发射台");
	data << m_lineEdit->text();
	data << m_typeCombox->currentText();
	if (m_formType==1)
	{
		emit addData(data);
	}
	else if(m_formType==2){
		emit modifyData(data);//修改该行数据
	}
}

//处理修改一行数据消息(qstringlist :行号|台站名|频率值|类型|状态|类型数值)
void FrequencyConfigForm::modifyOneData(const QModelIndex &index)
{
	//setWindowTitle(QString::fromLocal8Bit("修改频点配置"));
	//m_formType = 2;
	//m_currentRow = data.at(0).toInt();
	//qDebug() << "modify row :" << data.at(0);
	//m_stationCombox->setCurrentText(data.at(1));
	//m_lineEdit->setText(data.at(2));
	//m_typeCombox->setCurrentIndex(data.at(data.size() - 1).toInt());
	////setTypeList(typeList);
	//show();
}

//处理增加一行数据消息
void FrequencyConfigForm::addOneData(const QModelIndex &index)
{
	//setWindowTitle(QString::fromLocal8Bit("添加频点配置"));
	//m_formType = 1;
	//qDebug() << index.data(1)<< index.data(2)<< index.data(3);
	//m_currentRow = index.row();
	////setTypeList(typeList);
	//show();
}

/*
	index:一条数据
	rowcount:表格总行数
*/
void FrequencyConfigForm::processData(const FrequencyDataRecord &index, int rowcount)
{
	if (rowcount == index.row+1)
	{
		m_formType = 1;
	}
	else {
		m_formType = 2;
	}
	//获取当前行数据到表单中
	setWindowTitle(QString::fromLocal8Bit("频点配置"));
	m_currentRow = index.row;//获取当前行
	qDebug() << QString::fromLocal8Bit("行号：") << index.row;
	qDebug() << QString::fromLocal8Bit("台站名称：") << index.stationName;
	qDebug() << QString::fromLocal8Bit("类型值：") << index.type;
	qDebug() << QString::fromLocal8Bit("频率值：") << index.frequencyValue;
	qDebug() << QString::fromLocal8Bit("状态：") << index.status;
	m_lineEdit->setText(QString::number(index.frequencyValue));
	show();
}


void FrequencyConfigForm::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//设置表单中combox数据
void FrequencyConfigForm::setTypeList(int typeList)
{
	m_typeCombox->clear();
	if ((typeList&ModeType::DTBM_TYPE)!= ModeType::NULL_TYPE)
	{
		m_typeCombox->addItem(QString::fromLocal8Bit("数字电视"));
	}
	if ((typeList&ModeType::FM_TYPE)!=ModeType::NULL_TYPE)
	{
		m_typeCombox->addItem(QString::fromLocal8Bit("调频"));
	}
	if ((typeList&ModeType::AM_TYPE) != ModeType::NULL_TYPE)
	{
		m_typeCombox->addItem(QString::fromLocal8Bit("中波"));
	}
	if ((typeList&ModeType::SW_TYPE) != ModeType::NULL_TYPE)
	{
		m_typeCombox->addItem(QString::fromLocal8Bit("短波"));
	}
}