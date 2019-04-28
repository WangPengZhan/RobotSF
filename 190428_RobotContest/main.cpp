#include "robotcontest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RobotContest w;
	w.show();
	return a.exec();
}
