#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <qstackedwidget.h>
#include <qstackedlayout.h>
#include <qlabel.h>
#include "navigationpage.h"
#include "testmodepage.h"
#include "recordpage.h"
#include "reportpage.h"
#include "DataBaseTool.h"
#include "xanimationstackedwidget.h"
class CenterWidget : public QWidget
{
	Q_OBJECT

public:
	CenterWidget(QWidget *parent);
	~CenterWidget();
signals:
	void setTypeList(int modeType);
	void changePageStacked(int pageIndex);
public slots:
	void selectedMode(int modeType);
	void changePage(int pageIndex);
private:
	void connection();
private:
	QStackedLayout *m_pStackLayout;
	QLabel *m_groupBox;

	NavigationPage *m_pageNavigation;
	TestModePage *m_pageTestMode;
	RecordPage *m_pageRecord;
	ReportPage *m_pageReport;
	int m_nselectedMode;
	XAnimationStackedWidget *m_animationStackedWidget;
};

#endif // CENTERWIDGET_H
