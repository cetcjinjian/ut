#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include <QFile>
#include <QString>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	QFile file(".\\stylesheet.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	a.setStyleSheet(styleSheet);

	w.show();
	return a.exec();
}
