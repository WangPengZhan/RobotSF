#pragma once

#include <QWidget>
#include <QDialog>
#include <QGridLaYout>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QComboBox>
#include <QPushButton>
#include "manageexcel.h"

class DeduectMarksWidget : public QDialog
{
	Q_OBJECT

public:
	DeduectMarksWidget(QWidget *parent = nullptr);
	~DeduectMarksWidget();
	void setCurrentRow(int currentRow);
	void setSecond(bool isSencond);
	void setManageExcel(ManageExcel *manageExcel);
	void closeEvent();
	
private slots:
	void on_calculate_PushButton_clicked();
	void on_quitWidget_PushButton_clicked();
	void on_remake_ComboBox_CurrentIndexChanged();
	//void getParameter(ManageExcel *manageExcel, int currentRow);

private:
	void designUI();
	void signalsAndSlots();
	void init();
	void readExcel();
	int timeStringToInt(QString timeString);
	QString intToTimeString(int totalMescs);

private:
	ManageExcel *manageExcel = nullptr;
	int currentRow;
	bool isSecond;
	
	QWidget *deductMark_Widget;
	QGridLayout *deductMark_GridLayout;
	QLabel *teamNum1_Label;
	QLineEdit *teamNum1_LineEdit;
	QLabel *teamName1_Label;
	QLineEdit *teamName1_LineEdit;
	QLabel *bend_Label;
	QLineEdit *bend_LineEdit;
	QLabel *obstacle_Label;
	QLineEdit *obstacle_LineEdit;
	QLabel *impact_Label;
	QLineEdit *impact_LineEdit;
	QLabel *interference_Label;
	QLineEdit *interference_LineEdit;
	QLabel *isStop_Label;
	QComboBox *isStop_ComboBox;
	//QLineEdit *isStop_LineEdit;
	QLabel *isSlide_Label;
	QComboBox *isSlide_ComboBox;
	//QLineEdit *isSlide_LineEdit;

	QPushButton *calculate_PushButton;
	QPushButton *quitWidget_PushButton;
	QLabel *totalDeductMarks_Label;
	QLineEdit *totalDeductMarks_LineEdit;
	QLabel *finalTime_Label;
	QLineEdit *finalTime_LineEdit;
	QLabel *remake_Label;
	QComboBox *remake_ComboBox;
	QTextBrowser *tipsForStaff_TextBrowser;
};
