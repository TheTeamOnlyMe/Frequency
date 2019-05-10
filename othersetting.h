#ifndef OTHERSETTING_H
#define OTHERSETTING_H

#include <QWidget>
#include <qgridlayout.h>
#include "DataBaseTool.h"
#include "revisesetting.h"
#include "cyclesetting.h"
#include "datasavesetting.h"
class OtherSetting : public QWidget
{
	Q_OBJECT

public:
	OtherSetting(QWidget *parent);
	~OtherSetting();
private:
	void paintEvent(QPaintEvent *event);
signals:
	void currentChanged(int index);

private:
	QGridLayout *m_layout;
	ReviseSetting *m_reviseSet;
	CycleSetting *m_cycleSet;
	DataSaveSetting *m_dataSaveSet;
};

#endif // OTHERSETTING_H
