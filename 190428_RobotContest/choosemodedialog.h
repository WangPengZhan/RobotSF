#pragma once

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFile>

class ChooseModeDialog : public QDialog
{
	Q_OBJECT

public:
	ChooseModeDialog(QWidget *parent = nullptr);
	~ChooseModeDialog();
	int getMode();

private:
	void designUI();
	void SignalsAndSlots();
	void init();
	void loadQSSFile(const QString style);

private slots:
	void on_verify_PushButton_clicked();
private:
	QRadioButton  *preliminaryContest_RidioButton, *finals_RadioButton;
	QPushButton *verify_PushButton;
	//QLabel *version_Label;
	QGridLayout *main_GridLayout;

	int mode;
	const int prmkiminaryContest = 0x00;
	const int finals = 0x10;
};
