#ifndef MAPPAGE_H
#define MAPPAGE_H

#include <QWidget>
#include <QTextStream>
//#include <QWebView>
#include <QFile>

class MapPage : public QWidget
{
	Q_OBJECT

public:
	MapPage(QWidget *parent);
	~MapPage();
public slots:
	void startTest(bool bpause);
private:

	
};

#endif // MAPPAGE_H
