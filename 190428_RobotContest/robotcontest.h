#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_robotcontest.h"

class RobotContest : public QMainWindow
{
	Q_OBJECT

public:
	RobotContest(QWidget *parent = Q_NULLPTR);

private:
	Ui::RobotContestClass ui;
};
