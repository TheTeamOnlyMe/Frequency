#include "navigationpage.h"
NavigationPage::NavigationPage(QWidget *parent)
	: QWidget(parent)
	,m_selectedBtn(0xF)
{
	this->setParent(parent);
	init();
	initButton();
	signalConnect();
}

NavigationPage::~NavigationPage()
{

}
void NavigationPage::init()
{
	m_btnStyleGroup = new QButtonGroup(this);
	m_btnPageGroup = new QButtonGroup(this);

	m_pMainLayout = new QGridLayout(this);
	m_pHStyle = new QHBoxLayout();
	m_pPageBtnLayout = new QGridLayout();
	m_pCloseBtnLayout = new QHBoxLayout(this);




}
void NavigationPage::initButton()
{
	QStringList buttonText;
	buttonText << QString::fromLocal8Bit("���ֵ���") << QString::fromLocal8Bit(" ��  Ƶ ") << QString::fromLocal8Bit(" ��  �� ") << QString::fromLocal8Bit(" ��  �� ");
	m_pHStyle = new QHBoxLayout(this);
	m_btnStyleGroup->setExclusive(false);// ���û���
	for (int i = 0; i < 4; i++) {
		QAbstractButton *pButton = new QPushButton(this);
		pButton->setCheckable(true);
		pButton->setText(buttonText.at(i));
		pButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_pHStyle->addWidget(pButton);
		m_btnStyleGroup->addButton(pButton, 1 << i);
		if(i<3)
			m_pHStyle->addSpacing(25);
	}

	QPushButton *btnTestPage = new QPushButton(QString::fromLocal8Bit("���߲���"), this);
	btnTestPage->setObjectName("TextBtn");
	m_btnPageGroup->addButton(btnTestPage, PageIndex::TESTMODE);
	btnTestPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QPushButton *btnReport = new QPushButton(QString::fromLocal8Bit("��������"), this);
	btnReport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_btnPageGroup->addButton(btnReport, PageIndex::REPORT);

	QPushButton *btnRecord = new QPushButton(QString::fromLocal8Bit("��ʷ��¼"), this);
	btnRecord->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_btnPageGroup->addButton(btnRecord, PageIndex::RECORD);
	m_pPageBtnLayout->addWidget(btnTestPage, 0, 0, 1, 2);
	m_pPageBtnLayout->addWidget(btnReport, 1, 0, 1, 1);
	m_pPageBtnLayout->addWidget(btnRecord, 1, 1, 1, 1);
	m_pPageBtnLayout->setSpacing(25);

	QLabel *label = new QLabel(this);
	label->setObjectName("introduce");
	label->adjustSize();
	label->setWordWrap(true);
	label->setAlignment(Qt::AlignCenter);
	label->setText(QString::fromLocal8Bit("<html><head/> <body>"
		"<p style = 'line-height:22px;font-size:12px;text-indent:26px;'>"
		"����ʽ��ǿ�ǣ��ɶԵ�������Ƶ�㲥��ģ����Ӻ����ֵ����źŵĳ�ǿ������ȡ����ƶȼ���Ƶ�źŷ�ֵ���в��ԣ��������ֲ���֧��DTMB�������ֵ����źŵ��ŵ�������������ܣ���Ƶ֧��MPEG2��MPEG4��H.264��AVS��AVS+��ʽ�ĸ���ͱ�����룬�ܹ����������ƶ����Ժ����ڶ�����Ե����󣬷ǳ��ʺ��ڹ㲥���ӷ���̨�Լ����߳�ǿ��������ʹ�á�"
		"</p></body></html>"));
	label->setMargin(20);

	m_pCloseBtnLayout->addStretch();
	QPushButton *btnClose = new QPushButton(this);
	btnClose->setObjectName("ESC");
	connect(btnClose, &QPushButton::clicked, this->parentWidget(), &QWidget::close);
	m_pCloseBtnLayout->addWidget(btnClose);

	m_pMainLayout->addItem(m_pCloseBtnLayout, 0, 0, 1, 4);
	m_pMainLayout->addItem(m_pHStyle, 1, 0, 3, 4);
	m_pMainLayout->addWidget(label, 4, 0, 7, 2);
	m_pMainLayout->addItem(m_pPageBtnLayout, 4, 2, 7, 2);
	m_pMainLayout->setContentsMargins(20, 10, 20, 20);
	m_pMainLayout->setSpacing(20);
	setLayout(m_pMainLayout);
}

void NavigationPage::initBtnSize()
{

}

void NavigationPage::signalConnect()
{
	connect(m_btnPageGroup, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), this, &NavigationPage::changeToTestPage);
	connect(m_btnStyleGroup, static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked), this, &NavigationPage::buttonJudge);
}
void NavigationPage::changeToTestPage(int pageIndex)
{
	if(pageIndex == PageIndex::TESTMODE)
		emit modeType(m_selectedBtn);
	emit changePage(pageIndex);//��ҳ���л������Խ��棬��ʷ��¼���棬�������ɽ��棩
}

void NavigationPage::buttonJudge(int btnValue) {
	qDebug() << "btnValue " << btnValue;
	if ((m_selectedBtn&btnValue) == ModeType::NULL_TYPE) {
		m_selectedBtn |= btnValue;
	}
	else {
		m_selectedBtn &= ~btnValue;
	}
}

void NavigationPage::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

