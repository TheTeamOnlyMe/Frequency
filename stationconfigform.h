#ifndef STATIONCONFIGFORM_H
#define STATIONCONFIGFORM_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
class StationConfigForm : public QDialog
{
	Q_OBJECT

public:
	StationConfigForm(QWidget *parent);
	~StationConfigForm();
	void setCurrentIndex(int pageIndex) { m_pageIndex = pageIndex; }
signals:
	void destroyForm(int pageIndex);
private slots:
	void closeForm();
private:
	QHBoxLayout *m_layout;
	QPushButton *m_acceptbutton;
	int m_pageIndex;
};

#endif // STATIONCONFIGFORM_H
