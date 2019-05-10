#include "SprogressBar.h"

SprogressBar::SprogressBar(QWidget *parent,QString sname )
{
	this->setParent(parent);
	nstart =0;
	nend =100;
	ncurrent =0;
	nportion =20;
	n_used_show =0;
	flot_num =0;
	SettingBackground();
	this->sname = sname;
	setAttribute(Qt::WA_StyledBackground);
	//nlable->show();

	//更新音频定时器
	/*m_timer = new QTimer( this ); 
	m_timer_flow = new QTimer(this);
	m_timer_flow->start(200);
	connect( m_timer, SIGNAL(timeout()),this, SLOT(slt_voice_updata()) ); 
	m_timer->start(1000);
	connect( m_timer_flow, SIGNAL(timeout()),this, SLOT(slt_voice_updata()) ); */
	//音量进度条显示颜色

	linearGradient.setStart(0,0);
	linearGradient.setColorAt(0,QColor(60,0,0,255));
	linearGradient.setColorAt(0.40,QColor(45,45,0,255));
	linearGradient.setColorAt(0.50,QColor(45,45,0,255));
	linearGradient.setColorAt(0.60,QColor(0,30,0,255));
	linearGradient.setColorAt(1,QColor(0,30,0,255));//将直线开始点设为0，终点设为1，然后分段设置颜色
	pen_text = QPen(QColor(255,255,255),2);
	pen_rect = QPen(QColor(0,0,0),1);
	pen_name = QPen(QColor(255,255,255),2);
	this->show();


}

SprogressBar::~SprogressBar()
{

}
void SprogressBar::setRange(int start,int end)
{
	nstart = start;
	nend = end;
}
void SprogressBar ::setValue(int value)
{
	qDebug() << "value:" << value;
	if (value>100) ncurrent =100;
	else ncurrent = value;
	this->voice_updata();
}
void SprogressBar::paintEvent(QPaintEvent * event)
{


	QPainter painter_line(this);

	linearGradient.setFinalStop(this->width(),this->height());

	painter_line.setBrush(linearGradient);
	int nheight = this->size().height();
	int nrang = nend - nstart;
	if (flot_num<3)
	{
		flot_num++;
		painter_line.drawRect(0,0,this->width(),(nheight*(float(nend - (5 -flot_num)*n_used_show/5)/ nrang))-5);
	}else
	{
		flot_num =0;
		painter_line.drawRect(0,0,this->width(),(nheight*(float(nend - n_used_show)/ nrang))-5);//绘制矩形，线性渐变线正好在矩形的水平中心线上
	}
	//画背景覆盖线
	QPainter painter(this);

	painter.setPen(pen_rect);
	painter.drawRect(this->rect());
	painter.drawRect(1,1,this->width()-2,this->height()-2);
	for (int x=0;x<this->height();x=x+12)
	{
		painter.drawLine(0,x,this->width(),x);
		painter.drawLine(0,x+1,this->width(),x+1);
	}
	//显示数字
	QPainter n_painter(this);
	memset(voice,0,10);
	if (ncurrent ==0)
	{
		_itoa(n_used_show,voice,10);
	}else
		_itoa(ncurrent,voice,10);

	n_painter.setPen(pen_text);

	n_painter.drawText(QRect(0,7,this->width(),15),Qt::AlignCenter,QString::fromLocal8Bit(voice));


	QPainter n_paintername(this);
	if (!sname.isEmpty())
	{
		n_paintername.setPen(pen_name);
		n_paintername.drawText(QRect(0,(nheight*(float(nend - 0)/ nrang))-25,this->width(),15),Qt::AlignCenter,sname);

	}
	//显示浮动条 nrang默认赋值100范围
	//nend-n_used_show 最大值减去当前显示的值，即起始位置为白条的左上方，
	painter_line.fillRect(QRect(2,(nheight*(float(nend - n_used_show)/ nrang))-5 ,this->width()-4,5),QColor(250,250,250));

}

QString SprogressBar::calcValue(int nValue,int nTotal)
{
	QString strStyle = "";
	int value1 = nTotal * 0.20 + 0.5;
	QString nvt = QString::number(this->height());
	QString str1;
	QString str2;
	float scale1 = (float)value1 / (float)nTotal;
	float scale2 = scale1 + 0.2;
	str1 = str1.setNum(scale1,'f',6);
	str2 = str2.setNum(scale2,'f',6);
	QString str3;
	QString str4;
	float scale3 = 2.0 * scale1 +0.20;
	float scale4 = scale3 + 0.2;
	str3 = str3.setNum(scale3,'f',6);
	str4 = str4.setNum(scale4,'f',6);
	strStyle = QString("qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, \
					   stop:0 rgba(255, 0, 0, 255), stop:%1 rgba(255, 255, 0, 255), \
					   stop:%2 rgba(255, 255, 0, 255), stop:%3 rgba(0, 255, 0, 255) \
					   stop:%4 rgba(0, 255, 0, 255), stop:1 rgba(0, 255, 0, 255))")
					   .arg("0.5")//红-黄
					   .arg("0.6")//黄开始
					   .arg("0.8")//绿开始
					   .arg("1.0");//全红
	return strStyle;
}
void SprogressBar::voice_updata(int ntype)
{
	if(ntype == 1)
	{
		if (flot_num==3)
		{
			n_used_show = ncurrent;
			ncurrent =0;
		}
	}
	else{
		ncurrent =0;
		n_used_show=0;
		flot_num =5;
	}
	this->repaint(0,0,this->width(),this->height());
}
void SprogressBar::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton)
	{
		emit signal_clicked();
	}
}
void SprogressBar::SettingBackground()
{
	setStyleSheet(QString("border-image:0; background-color:%1;}").arg(calcValue(100,nend)));
}
void SprogressBar::start()
{

}