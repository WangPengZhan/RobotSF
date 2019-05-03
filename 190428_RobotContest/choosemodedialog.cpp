#pragma execution_character_set("utf-8")

#include "choosemodedialog.h"

ChooseModeDialog::ChooseModeDialog(QWidget *parent)
	: QDialog(parent)
{
	designUI();

	SignalsAndSlots();

	init();
}

ChooseModeDialog::~ChooseModeDialog()
{
}

int ChooseModeDialog::getMode()
{
	return mode;
}

void ChooseModeDialog::designUI()
{
	setWindowIcon(QIcon(":/bg.png"));
	//setWindowTitle(tr("Select Mode"));
	setWindowTitle(tr("选择模式"));
	setFont(QFont(tr("楷体"), 16));
	setMinimumSize(225, 86);

	preliminaryContest_RidioButton = new QRadioButton(tr("初赛"), this);
	preliminaryContest_RidioButton->setChecked(true);
	finals_RadioButton = new QRadioButton(tr("决赛"), this);

	verify_PushButton = new QPushButton(tr("配置"), this);
	
	main_GridLayout = new QGridLayout(this);
	main_GridLayout->addWidget(preliminaryContest_RidioButton, 0, 0);
	main_GridLayout->addWidget(finals_RadioButton, 1, 0);
	main_GridLayout->addWidget(verify_PushButton, 2, 0);
}

void ChooseModeDialog::SignalsAndSlots()
{
	connect(verify_PushButton, &QPushButton::clicked, this, &ChooseModeDialog::on_verify_PushButton_clicked);
}

void ChooseModeDialog::init()
{
	mode = -1;
	loadQSSFile(":/style");
}

void ChooseModeDialog::loadQSSFile(const QString style)
{
	QFile qss(style);
	qss.open(QIODevice::ReadOnly);
	setStyleSheet(qss.readAll());
	qss.close();
}

void ChooseModeDialog::on_verify_PushButton_clicked()
{
	QString modeName;
	if (finals_RadioButton->isChecked()) {
		mode = finals;
	}
	else {
		mode = prmkiminaryContest;
	}
	switch (mode)
	{
	case 0x00:
		modeName = "初赛";
		break;
	case 0x10:
		modeName = "决赛";
		break;
	default:
		QMessageBox::warning(this, tr("警告"), tr("你的选择未完成！"), QMessageBox::Ok);
		return;
		break;
	}
	int ret = QMessageBox::information(this, tr("通知"), tr("你确定选择%1？").arg(modeName), QMessageBox::Ok,
		QMessageBox::Discard, QMessageBox::Cancel);
	switch (ret)
	{
	case QMessageBox::Ok:
		accept();
		break;
	case QMessageBox::Discard:
		break;
	case QMessageBox::Cancel:
		close();
	default:
		break;
	}
}
