#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QStatusBar>
#include <QGridLayout>
#include <QWidget>
#include <QTimer>
#include <QTime>

class FinalsWindow : public QMainWindow
{
	Q_OBJECT

public:
	FinalsWindow(QWidget *parent = nullptr);
	~FinalsWindow();
private slots:
	void on_startTime_PushButton_clicked();
	void on_clearTime_PushButton_clicked();
	void on_verifyTime_PushBUtton_clickef();
	void on_timer_timeout();
private:
	void designUI();
	void signalsAndSlots();
	void init();
	int timeStringToInt(QString timeString);
	QString intToTimeString(int totalMescs);
private:
	QTime beginTime;
	QTime currentTime;
	QTime waitBegin;
	QTime waitEnd;
	int waitmsecs,showmsecs;
	int totalmsecs;
	QString theResult;
	QTimer timer;

	QLabel *title_Label;
	QLCDNumber *time_LCDNumber;
	QPushButton *startTime_PushButton;
	QPushButton *clearTime_PushButton;
	QLabel *tipsForTeams_Label;
	QPushButton *verifyTime_PushButton;
	QPushButton *quit_PushButton;
	
	QLabel *sign_Label;
	QWidget *center_Widget;
	QGridLayout *main_GridLayout;
};
