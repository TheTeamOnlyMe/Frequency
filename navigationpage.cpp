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
	buttonText << QString::fromLocal8Bit("数字电视") << QString::fromLocal8Bit(" 调  频 ") << QString::fromLocal8Bit(" 中  波 ") << QString::fromLocal8Bit(" 短  波 ");
	m_pHStyle = new QHBoxLayout(this);
	m_btnStyleGroup->setExclusive(false);// 设置互斥
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

	QPushButton *btnTestPage = new QPushButton(QString::fromLocal8Bit("在线测试"), this);
	btnTestPage->setObjectName("TextBtn");
	m_btnPageGroup->addButton(btnTestPage, PageIndex::TESTMODE);
	btnTestPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QPushButton *btnReport = new QPushButton(QString::fromLocal8Bit("报告生成"), this);
	btnReport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_btnPageGroup->addButton(btnReport, PageIndex::REPORT);

	QPushButton *btnRecord = new QPushButton(QString::fromLocal8Bit("历史记录"), this);
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
		"多制式场强仪，可对调幅、调频广播、模拟电视和数字电视信号的场强、载噪比、调制度及音频信号幅值进行测试；其中数字部分支持DTMB地面数字电视信号的信道分析及解调功能，视频支持MPEG2、MPEG4、H.264、AVS、AVS+格式的高清和标清解码，能够满足室外移动测试和室内定点测试的需求，非常适合于广播电视发射台以及无线场强监测等领域使用。"
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
	emit changePage(pageIndex);//主页面切换（测试界面，历史记录界面，报告生成界面）
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

