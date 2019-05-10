#include "mappage.h"

MapPage::MapPage(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("MapPage");
	QFile file("D:/test.html");
	file.open(QIODevice::ReadOnly);
	QTextStream out(&file);
	QString output_file = out.readAll();
	//m_pWebView->setHtml(output_file);

}

MapPage::~MapPage()
{

}
void MapPage::startTest(bool bpause)
{

}
