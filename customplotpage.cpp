#include "customplotpage.h"

CustomPlotPage::CustomPlotPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CustomPlotPage)
	, m_xValue(0)
	, m_yValue(0)
	, m_stepone(86)
{
	ui->setupUi(this);
	ui->gridLayout->setContentsMargins(0, 0, 0, 0);
	initPlot();
	time = new QTimer(this);
	connect(time, &QTimer::timeout, this, &CustomPlotPage::startTest);
	this->setMouseTracking(true);
}

CustomPlotPage::~CustomPlotPage()
{
	delete ui;
	delete time;
}
void CustomPlotPage::paintEvent(QPaintEvent *event)
{

}
void CustomPlotPage::mouseMoveEvent(QMouseEvent *event)
{

}

void CustomPlotPage::initPlot()
{
	ui->widget->axisRect()->setupFullAxesBox(true);
	ui->widget->xAxis->setRange(87, 108);
	ui->widget->yAxis->setRange(0,120);

	ui->widget->legend->setVisible(true);
	ui->widget->legend->setBrush(QColor(255,255,255,0));
	ui->widget->legend->setTextColor(QColor(225,225,225));
	ui->widget->legend->setBorderPen(QPen(Qt::NoPen));

	ui->widget->addGraph();
	ui->widget->graph(0)->setPen(QPen(Qt::green));
	ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
	ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
	ui->widget->graph(0)->setName(QString::fromLocal8Bit("场强值（单位：dBuv）"));
	ui->widget->addGraph();
	QPen blueDotPen;
	blueDotPen.setColor(QColor(Qt::red));
	blueDotPen.setStyle(Qt::DotLine);
	blueDotPen.setWidthF(2);
	ui->widget->graph(1)->setPen(blueDotPen);
	ui->widget->graph(1)->setName(QString::fromLocal8Bit("门限值"));
	ui->widget->yAxis->setLabel(QString::fromLocal8Bit("场强值（单位：dBuv）"));
	ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));
	ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
	ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));
	ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
	ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));
	ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));
	ui->widget->xAxis->setTickLabelColor(Qt::white);
	ui->widget->yAxis->setTickLabelColor(Qt::white);
	ui->widget->xAxis->setLabelColor(QColor(225, 225, 225));
	ui->widget->yAxis->setLabelColor(QColor(225,225,225));
	ui->widget->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
	ui->widget->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
	ui->widget->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
	ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
	ui->widget->xAxis->grid()->setSubGridVisible(true);
	ui->widget->yAxis->grid()->setSubGridVisible(true);
	ui->widget->xAxis->grid()->setZeroLinePen(Qt::NoPen);
	ui->widget->yAxis->grid()->setZeroLinePen(Qt::NoPen);
	ui->widget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
	ui->widget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
	//设置背景色
	QLinearGradient plotGradient;
	plotGradient.setStart(0, 0);
	plotGradient.setFinalStop(0, 350);
	plotGradient.setColorAt(0, QColor(80, 80, 80));
	plotGradient.setColorAt(1, QColor(50, 50, 50));
	ui->widget->setBackground(plotGradient);
	//设置数值文本
	textLabel = new QCPItemText(ui->widget);
	textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
	textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
	textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
	textLabel->setColor(QColor(Qt::white));
	textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
	textLabel->setPen(QPen(Qt::NoPen)); // show black border around text
	textLabel->setText(QString::fromLocal8Bit("场强值：N/A dBuv"));

	ui->widget->replot();
}

QCPRange CustomPlotPage::axisChanged(const double lower,const double upper,const QCPRange &newRange)
{
	QCPRange boundedRange = newRange;
	int lowerRangeBound = lower;
	int upperRangeBound = upper;

	if (boundedRange.size() > upperRangeBound - lowerRangeBound)
	{
		boundedRange = QCPRange(lowerRangeBound, upperRangeBound);
	}
	else
	{
		double oldSize = newRange.size();
		if (boundedRange.lower < lowerRangeBound)
		{
			boundedRange.lower = lowerRangeBound;
			boundedRange.upper = lowerRangeBound + oldSize;
		}
		if (boundedRange.upper > upperRangeBound)
		{
			boundedRange.lower = upperRangeBound - oldSize;
			boundedRange.upper = upperRangeBound;
		}
	}
	return boundedRange;
}

//test  定时模拟数据
void CustomPlotPage::startTest()
{
	if (m_xValue.size()>21)
	{
		m_xValue.clear();
		m_stepone = 86;
	}
	m_stepone++;
	m_xValue.append(m_stepone);
	m_yValue.append(qrand()%100+1);

	textLabel->setText(QString::fromLocal8Bit("场强值：%1 dBuv").arg(m_yValue.at(m_xValue.size()-1)));

	ui->widget->graph(0)->setData(m_xValue, m_yValue);
	ui->widget->replot();
}
void CustomPlotPage::rightStepOne(int limitValue)
{
	if (m_xValue.size()>21)
	{
		m_xValue.clear();
		m_stepone = 86;
	}
	m_stepone++;
	m_xValue.append(m_stepone);
	m_yValue.append(qrand() % 100 + 1);
	textLabel->setText(QString::fromLocal8Bit("场强值：%1 dBuv").arg(m_yValue.at(m_xValue.size() - 1)));
	ui->widget->graph(0)->setData(m_xValue, m_yValue);
	ui->widget->replot();
}
void CustomPlotPage::leftStepOne(int limitValue)
{
	if (m_xValue.size() == 0) return;
	m_stepone--;
	m_yValue.remove(m_xValue.size() - 1);
	m_xValue.remove(m_xValue.size() - 1);
	if (m_xValue.size()==0)
	{
		textLabel->setText(QString::fromLocal8Bit("场强值：N/A dBuv"));
	}
	else {
		textLabel->setText(QString::fromLocal8Bit("场强值：%1 dBuv").arg(m_yValue.at(m_xValue.size() - 1)));
	}
	ui->widget->graph(0)->setData(m_xValue, m_yValue);
	QVector<double> xData(500), yData(500);
	for (int i = 0; i < 500; i++)
	{
		xData[i] = i;
		yData[i] = limitValue;
	}
	ui->widget->graph(1)->setData(xData, yData);
	ui->widget->replot();
}
//开始测试，设置临界值
void CustomPlotPage::setData(const int index,const QVector<double> &x,const QVector<double> &y)
{
	 
	time->start(1000);
	ui->widget->graph(index)->setData(x, y);
	ui->widget->replot();
}
//暂停测试，清理界面控件
void CustomPlotPage::clearData()
{
	time->stop();
}
//根据当前类型值以及配置文件设置范围
void CustomPlotPage::setRangeByType(const int type)
{
	switch (type)
	{
	case ModeType::DTBM_TYPE:
		ui->widget->xAxis->setRange(0, 95);
		ui->widget->yAxis->setRange(0, 120);
		break;
	case ModeType::FM_TYPE:
		ui->widget->xAxis->setRange(87, 108);
		ui->widget->yAxis->setRange(0, 120);
		break;
	case ModeType::AM_TYPE:
		ui->widget->xAxis->setRange(0,1700);
		ui->widget->yAxis->setRange(0, 120);
		break;
	default:
		break;
	}
	ui->widget->replot();
}