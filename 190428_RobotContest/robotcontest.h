#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QLCDNumber>
#include <QCombobox>
#include <QGridLayout>
#include <QLineEdit>
#include <QDialog>
#include <QCloseEvent>
#include <QStatusBar>
#include <QMessageBox>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QTextBrowser>
//#include "ui_robotcontest.h"
#include "manageexcel.h"
#include "serialport.h"
#include "deduectmarkswidget.h"

class RobotContest : public QMainWindow
{
	Q_OBJECT

public:
	RobotContest(QWidget *parent = Q_NULLPTR);
	~RobotContest();
	void closeEvent(QCloseEvent *event);

private slots:
	void on_searchSerialPort_PushButton_clicked();
	void on_openSerialPort_PushButton_clicked();
	void on_openExcel_PushButton_clicked();
	void on_newExcel_PushButton_clicked();
	void on_lastOne_PushButton_clicked();
	void on_nextOne_PushButton_clicked();
	void on_verifyScore_PushButton_clicked();
	void on_clearScore_PushButton_clicked();
	void on_startTime_PushBtton_clicked();
	void dealWithSerialPortDate(QByteArray data);
	void on_update_timeOver();
	void on_teamName_LineEdit_textChanged();
	void on_saveTimer_timeout();
	void on_writeDeductTime_PushButton_clicked();

private:
	void designUI();
	void signalsAndSlots();
	void init();
	void loadQSSFile(const QString style);
	int timeStringToInt(QString timeString);
	QString intToTimeString(int totalMescs);
	float facadeScoreToTime();
	
private:
	ManageExcel *manageExcel = nullptr;
	SerialPort mySerialPort;

	int currentRow;
	QTimer timer, saveTimer;
	//QDateTime beginDateTime;
	//QDateTime CurrentDateTime;
	QTime beginTime;
	QTime CurrentTime;
	int msecs, sec, minu;
	int totalmsecs;
	int waitmsecs;
	//QDateTime waitBegin;
	//QDateTime waitEnd;
	QTime waitBegin;
	QTime waitEnd;
	bool isClear;
	bool isOnce;
	bool isSecond;
	QString theResult;

	DeduectMarksWidget widget;
	
	//Ö÷½çÃæ
	QLabel *title_Label;
	QLCDNumber *time_LCDNumber;

	QComboBox *serialPort_ComboBox;
	QPushButton *searchSerialPort_PushButton;
	QPushButton *openSerialPort_PushButton;
	QPushButton *openExcel_PushButton;
	QPushButton *newExcel_PushButton;
	QPushButton *writeDeductTime_PushButton;
	//QTextBrowser *tipsForteam_TextBrowser;
	QLabel *tipsForTeams_Label;
	
	QLabel *teamNum_Label;
	QLineEdit *teamNum_LineEdit;
	QLabel *teamName_Label;
	QLineEdit *teamName_LineEdit;
	QLabel *firstScore_Label;
	QLineEdit *firstScore_LineEdit;
	QLabel *secondScore_Label;
	QLineEdit *secondScore_LineEdit;
	QLabel *facadeScore_Label;
	QLineEdit *facadeScore_LineEdit;
	QLabel *finalScore_Label;
	QLineEdit *finalScore_LineEdit;

	QPushButton *lastOne_PushButton;
	QPushButton *nextOne_PushButton;
	QPushButton *verifyScore_PushButton;
	QPushButton *startTime_PushButton;
	QPushButton *clearScore_PushButton;
	QPushButton *quit_PushButton;
	
	QLabel *sign_Label;
	QWidget *center;
	QGridLayout *main_GridLayout;
	//Ui::RobotContestClass ui;
};
