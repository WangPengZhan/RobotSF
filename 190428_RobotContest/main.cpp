#include "robotcontest.h"
#include "choosemodedialog.h"
#include "finalswindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChooseModeDialog c;
	c.show();
	if (c.exec() == c.Accepted) {
		if (c.getMode() == 0x00) {
			RobotContest w;
			w.show();
			return a.exec();
		}
		else if (c.getMode() == 0x10) {
			FinalsWindow f;
			f.show();
			return a.exec();
		}
	}
	else {
		return 0;
	}
	
}
