#ifndef _SPROGRESSBAR
#define _SPROGRESSBAR
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>
class SprogressBar : public QWidget
{
	Q_OBJECT
public:
	SprogressBar(QWidget *parent,QString sname = 0);
	~SprogressBar();
	void setValue(int value);
	void setRange(int start,int end);
	void SettingBackground();

private:

	int nportion;//���߻��ַ���
	QRgb  nbackcolor;
	int nstart;//��Сֵ
	int nend;//���ֵ
	int ncurrent;//��ǰֵ
	int n_used_show;
	char voice[10];
	QLinearGradient linearGradient;
	QPen pen_text;
	QPen pen_rect;
	QPen pen_name;
	bool IsFlot;
	int flot_num;
	QString sname;
protected:
	//void resizeEvent ( QResizeEvent * event );
	void paintEvent(QPaintEvent *);
	QString calcValue(int nValue,int nTotal);
	void mousePressEvent(QMouseEvent *event);
public:
	void voice_updata(int ntype =1);
signals:
	void signal_clicked();
private slots:
	void start();
};
#endif