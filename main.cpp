#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QFile>
#ifdef Q_WS_WIN
#include <windows.h>
#endif
#include "mainwindow.h"
#include "systemconfig.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile file(":/qss/style.qss");
	if (file.open(QFile::ReadOnly)) {
		a.setStyleSheet(QString::fromLatin1(file.readAll()));
		file.close();
	}

	MainWindow w;
	w.show();
	return a.exec();
}
