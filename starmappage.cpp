#include "starmappage.h"

StarMapPage::StarMapPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CustomPlotPage)
{
	ui->setupUi(this);
	ui->gridLayout->setContentsMargins(0, 0, 0, 0);
	initPlot();

}

StarMapPage::~StarMapPage()
{

}

void StarMapPage::initPlot()
{
	ui->widget->yAxis->setRange(-128.00, 128.00);
	ui->widget->xAxis->setRange(-128.00, 128.00);
	ui->widget->yAxis->setLabel(QString::fromLocal8Bit("¶à¾¶·ÖÎö"));
	//////////
	ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));
	ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
	ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));
	ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
	ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));
	ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));
	ui->widget->xAxis->setTickLabelColor(Qt::white);
	ui->widget->yAxis->setTickLabelColor(Qt::white);
	ui->widget->xAxis->setLabelColor(QColor(225, 225, 225));
	ui->widget->yAxis->setLabelColor(QColor(225, 225, 225));
	ui->widget->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
	ui->widget->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
	ui->widget->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
	ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
	ui->widget->xAxis->grid()->setSubGridVisible(true);
	ui->widget->yAxis->grid()->setSubGridVisible(true);
	ui->widget->xAxis->grid()->setZeroLinePen(QPen(Qt::white, 1));
	ui->widget->yAxis->grid()->setZeroLinePen(QPen(Qt::white, 1));
	ui->widget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
	ui->widget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
	QLinearGradient plotGradient;
	plotGradient.setStart(0, 0);
	plotGradient.setFinalStop(0, 350);
	plotGradient.setColorAt(0, QColor(80, 80, 80));
	plotGradient.setColorAt(1, QColor(50, 50, 50));
	ui->widget->setBackground(plotGradient);
	ui->widget->replot();
}
void StarMapPage::startTest(bool bpause)
{

}
