#ifndef DATAVALUEWIDGET_H
#define DATAVALUEWIDGET_H

#include <QWidget>
#include <qgridlayout.h>
#include <qlabel.h>
#include <QTimer>
#include "qlableexpand.h"
#include "DataBaseTool.h"
class RealTimeData : public QWidget
{
	Q_OBJECT

public:
	RealTimeData(QWidget *parent, int modetype);
	~RealTimeData();
	void setValue(QStringList valuelist);
private:
	void initLabel();
	void setDataName();
public slots:
	void start();
	void startTest(bool bstart);
	void setType(int type);//当前测试类型
private:
	QGridLayout *m_layout;
	int m_type;

	QLableExpand* m_labfrequency; //频率值
	QLableExpand* m_labfieldstrengthvalueA; //场强值v
	QLableExpand* m_labfieldstrengthvalueB; //场强值A
	QLableExpand* m_labcnr; //载噪比
	//QLableExpand* m_labsnr; //信噪比
	QLableExpand* m_labfrequencyoffset; //频偏(调幅度)
	QLableExpand* m_labtestmode; //测试模式
	QLableExpand* m_labsavedata; //是否保存数据
	QLableExpand* m_labsatellite; //卫星

	QLableExpand* m_labcarrierwaveM; //载波(DTMB专有)
	QLableExpand* m_labstarbitmap; //星位图(DTMB专有)
	QLableExpand* m_labfec; //前向纠错(DTMB专有)
	QLableExpand* m_labgi; //保护间隔(DTMB专有)
	QLableExpand* m_labti; //交织深度(DTMB专有)
	QLableExpand* m_labber; //比特误码率(DTMB专有)
	QLableExpand* m_labmer; //调制误码率(DTMB专有)

	QTimer *timer;

};

#endif // DATAVALUEWIDGET_H
