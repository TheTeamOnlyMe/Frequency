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
	void setType(int type);//��ǰ��������
private:
	QGridLayout *m_layout;
	int m_type;

	QLableExpand* m_labfrequency; //Ƶ��ֵ
	QLableExpand* m_labfieldstrengthvalueA; //��ǿֵv
	QLableExpand* m_labfieldstrengthvalueB; //��ǿֵA
	QLableExpand* m_labcnr; //�����
	//QLableExpand* m_labsnr; //�����
	QLableExpand* m_labfrequencyoffset; //Ƶƫ(������)
	QLableExpand* m_labtestmode; //����ģʽ
	QLableExpand* m_labsavedata; //�Ƿ񱣴�����
	QLableExpand* m_labsatellite; //����

	QLableExpand* m_labcarrierwaveM; //�ز�(DTMBר��)
	QLableExpand* m_labstarbitmap; //��λͼ(DTMBר��)
	QLableExpand* m_labfec; //ǰ�����(DTMBר��)
	QLableExpand* m_labgi; //�������(DTMBר��)
	QLableExpand* m_labti; //��֯���(DTMBר��)
	QLableExpand* m_labber; //����������(DTMBר��)
	QLableExpand* m_labmer; //����������(DTMBר��)

	QTimer *timer;

};

#endif // DATAVALUEWIDGET_H
