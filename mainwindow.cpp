#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	init();
	initView();
}

MainWindow::~MainWindow()
{

}
void MainWindow::init()
{
	setObjectName("MainPage");
	setWindowFlags(Qt::FramelessWindowHint);//运行后该窗体是无法进行移动和调整大小的
	//showFullScreen();
	resize(650, 500);
}
void MainWindow::initView()
{
	m_pVLayout = new QVBoxLayout(this);
	m_pCenterWidget = new CenterWidget(this);
	m_pStatus = new XCustomStatus(this);
	m_pVLayout->setSpacing(0);
	m_pVLayout->addWidget(m_pCenterWidget, 20);
	m_pVLayout->setSpacing(0);
	m_pVLayout->addWidget(m_pStatus, 1);
	m_pVLayout->setContentsMargins(0,0,0,0);
	setLayout(m_pVLayout);
}
void MainWindow::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}