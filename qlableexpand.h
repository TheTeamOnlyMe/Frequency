#ifndef QLABLEEXPAND_H
#define QLABLEEXPAND_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>

class QLableExpand : public QWidget
{
	Q_OBJECT

public:
	QLableExpand(QWidget *parent,QString sname,bool b_showorhide = true);
	~QLableExpand();
	void SetValue(QString svalue);
	void SetName(QString sname);
	void SetNull();
	QString GetValue();
	QLabel* lab_name;
	QLabel* lab_value;

private:
	
};

#endif // QLABLEEXPAND_H
