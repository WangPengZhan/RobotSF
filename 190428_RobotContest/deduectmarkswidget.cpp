#include "deduectmarkswidget.h"

#pragma execution_character_set("utf-8")

DeduectMarksWidget::DeduectMarksWidget(QWidget *parent)
	: QDialog(parent)
{
	designUI();
	signalsAndSlots();
	init();
}

DeduectMarksWidget::~DeduectMarksWidget()
{

}

void DeduectMarksWidget::setCurrentRow(int currentRow)
{
	this->currentRow = currentRow;
	readExcel();
}

void DeduectMarksWidget::setSecond(bool isSecond)
{
	this->isSecond = isSecond;
	remake_ComboBox->setCurrentIndex(isSecond);
}

void DeduectMarksWidget::setManageExcel(ManageExcel *manageExcel)
{
	this->manageExcel = manageExcel;
}

void DeduectMarksWidget::closeEvent()
{
	manageExcel->saveExcel();
}

void DeduectMarksWidget::on_quitWidget_PushButton_clicked()
{
	manageExcel->writeCellValue(currentRow + isSecond, 8, bend_LineEdit->text());
	manageExcel->writeCellValue(currentRow + isSecond, 9, obstacle_LineEdit->text());
	manageExcel->writeCellValue(currentRow + isSecond, 10, impact_LineEdit->text());
	manageExcel->writeCellValue(currentRow + isSecond, 11, interference_LineEdit->text());
	manageExcel->writeCellValue(currentRow + isSecond, 12, tr("%1").arg(isStop_ComboBox->currentIndex()));
	manageExcel->writeCellValue(currentRow + isSecond, 13, tr("%1").arg(isSlide_ComboBox->currentIndex()));
	manageExcel->writeCellValue(currentRow + isSecond, 14, totalDeductMarks_LineEdit->text());
	manageExcel->writeCellValue(currentRow + isSecond, 4, finalTime_LineEdit->text());
	if (timeStringToInt(manageExcel->readCellValue(currentRow, 4)) > 
		timeStringToInt(manageExcel->readCellValue(currentRow + isSecond, 4))) {
		manageExcel->writeCellValue(currentRow, 15, manageExcel->readCellValue(currentRow + 1, 4));
	}
	else {
		manageExcel->writeCellValue(currentRow, 15, manageExcel->readCellValue(currentRow, 4));
	}
	//manageExcel->writeCellValue(currentRow, 16, tr("%1").arg(remake_ComboBox->currentIndex()));
	close();
}

void DeduectMarksWidget::on_remake_ComboBox_CurrentIndexChanged()
{
	isSecond = remake_ComboBox->currentIndex();
	readExcel();
}

/*void DeduectMarksWidget::getParameter(ManageExcel * manageExcel, int currentRow)
{
	this->manageExcel = manageExcel;
	this->currentRow = currentRow;
}*/

void DeduectMarksWidget::on_calculate_PushButton_clicked()
{
	int bendsConuts = 0, obstaclesCounts = 0, impactsCount = 0, interferencesCount = 0;
	int isStop = 1, isSlide = 0;
	int totalDeductMarks;
	float facadeScore = 0.0, timeScore = 0.0;
	float finalTime;

	if (!bend_LineEdit->text().isEmpty()) {
		bendsConuts = bend_LineEdit->text().toInt();
	}
	if (!obstacle_LineEdit->text().isEmpty()) {
		obstaclesCounts = obstacle_LineEdit->text().toInt();
	}
	if (!interference_LineEdit->text().isEmpty()) {
		interferencesCount = interference_LineEdit->text().toInt();
	}
	if (!impact_LineEdit->text().isEmpty()) {
		impactsCount = impact_LineEdit->text().toInt();
	}
	isStop = isStop_ComboBox->currentIndex();
	isSlide = isSlide_ComboBox->currentIndex();
	//totalDeductMarks = 5 * bendsConuts + 10 * obstaclesCounts + 5 * impactsCount + 5 * interferencesCount +
		//5 * isStop + 10 * isSlide;
	totalDeductMarks = 10 * (isSlide + obstaclesCounts) + 5 * (impactsCount + interferencesCount + isStop + bendsConuts);
	totalDeductMarks_LineEdit->setText(tr("%1").arg(totalDeductMarks));

	if (!manageExcel->readCellValue(currentRow, 7).isEmpty()) {
		facadeScore = manageExcel->readCellValue(currentRow, 7).toFloat();
	}
	if (!manageExcel->readCellValue(currentRow, 5).isEmpty()) {
		timeScore = float(timeStringToInt(manageExcel->readCellValue(currentRow, 5))) / 1000;
	}

	finalTime = timeScore - facadeScore + totalDeductMarks;
	finalTime_LineEdit->setText(tr("%1").arg(finalTime));
}

void DeduectMarksWidget::designUI()
{
	setWindowTitle(tr("加罚时间录入"));
	setFont(QFont("楷体", 16));
	setWindowIcon(QIcon(":/bg.png"));
	setWindowModality(Qt::ApplicationModal);

	teamNum1_Label = new QLabel(tr("参赛序号"), this);
	teamNum1_Label->setAlignment(Qt::AlignCenter);
	teamNum1_LineEdit = new QLineEdit(this);
	teamNum1_LineEdit->setAlignment(Qt::AlignCenter);
	teamNum1_LineEdit->setEnabled(false);
	teamName1_Label = new QLabel(tr("队长姓名"), this);
	teamName1_Label->setAlignment(Qt::AlignCenter);
	teamName1_LineEdit = new QLineEdit(this);
	teamName1_LineEdit->setAlignment(Qt::AlignCenter);
	teamName1_LineEdit->setEnabled(false);
	bend_Label = new QLabel(tr("未绕弯道个数"), this);
	bend_Label->setAlignment(Qt::AlignCenter);
	bend_LineEdit = new QLineEdit(this);
	obstacle_Label = new QLabel(tr("未绕指定障碍个数"));
	obstacle_Label->setAlignment(Qt::AlignCenter);
	obstacle_LineEdit = new QLineEdit(this);
	impact_Label = new QLabel(tr("碰撞次数"), this);
	impact_Label->setAlignment(Qt::AlignCenter);
	impact_LineEdit = new QLineEdit(this);
	interference_Label = new QLabel(tr("人员干涉次数"), this);
	interference_Label->setAlignment(Qt::AlignCenter);
	interference_LineEdit = new QLineEdit(this);

	isStop_Label = new QLabel(tr("是否自动停下"), this);
	isStop_Label->setAlignment(Qt::AlignCenter);
	isStop_ComboBox = new QComboBox(this);
	isStop_ComboBox->addItem(tr("是"), 0);
	isStop_ComboBox->addItem(tr("否"), 1);
	isStop_ComboBox->setCurrentIndex(1);
	//isStop_LineEdit = new QLineEdit(this);
	isSlide_Label = new QLabel(tr("是否下滑"), this);
	isSlide_Label->setAlignment(Qt::AlignCenter);
	isSlide_ComboBox = new QComboBox(this);
	isSlide_ComboBox->addItem(tr("否"));
	isSlide_ComboBox->addItem(tr("是"));
	//isSlide_LineEdit = new QLineEdit(this);

	calculate_PushButton = new QPushButton(tr("计算"), this);
	quitWidget_PushButton = new QPushButton(tr("退出并保存录入"), this);
	totalDeductMarks_Label = new QLabel(tr("加罚总时间"), this);
	totalDeductMarks_Label->setAlignment(Qt::AlignCenter);
	totalDeductMarks_LineEdit = new QLineEdit(this);
	totalDeductMarks_LineEdit->setEnabled(false);
	finalTime_Label = new QLabel(tr("最终成绩"), this);
	finalTime_Label->setAlignment(Qt::AlignCenter);
	finalTime_LineEdit = new QLineEdit(this);
	finalTime_LineEdit->setEnabled(false);
	remake_Label = new QLabel(tr("比赛次数"), this);
	remake_Label->setAlignment(Qt::AlignCenter);
	remake_ComboBox = new QComboBox(this);
	remake_ComboBox->addItem(tr("1"));
	remake_ComboBox->addItem(tr("2"));

	deductMark_GridLayout = new QGridLayout(this);
	deductMark_GridLayout->addWidget(teamNum1_Label, 0, 0, 1, 1);
	deductMark_GridLayout->addWidget(teamNum1_LineEdit, 0, 1, 1, 1);
	deductMark_GridLayout->addWidget(teamName1_Label, 1, 0, 1, 1);
	deductMark_GridLayout->addWidget(teamName1_LineEdit, 1, 1, 1, 1);
	deductMark_GridLayout->addWidget(bend_Label, 2, 0, 1, 1);
	deductMark_GridLayout->addWidget(bend_LineEdit, 2, 1, 1, 1);
	deductMark_GridLayout->addWidget(obstacle_Label, 3, 0, 1, 1);
	deductMark_GridLayout->addWidget(obstacle_LineEdit, 3, 1, 1, 1);
	deductMark_GridLayout->addWidget(impact_Label, 4, 0, 1, 1);
	deductMark_GridLayout->addWidget(impact_LineEdit, 4, 1, 1, 1);
	deductMark_GridLayout->addWidget(interference_Label, 5, 0, 1, 1);
	deductMark_GridLayout->addWidget(interference_LineEdit, 5, 1, 1, 1);

	deductMark_GridLayout->addWidget(isStop_Label, 6, 0, 1, 1);
	deductMark_GridLayout->addWidget(isStop_ComboBox, 6, 1, 1, 1);
	//deductMark_GridLayout->addWidget(isStop_LineEdit,6,1,1,1);
	deductMark_GridLayout->addWidget(isSlide_Label, 7, 0, 1, 1);
	//deductMark_GridLayout->addWidget(isSlide_LineEdit,7,1,1,1);
	deductMark_GridLayout->addWidget(isSlide_ComboBox, 7, 1, 1, 1);

	deductMark_GridLayout->addWidget(calculate_PushButton, 8, 0, 1, 1);
	deductMark_GridLayout->addWidget(quitWidget_PushButton, 8, 1, 1, 1);
	deductMark_GridLayout->addWidget(totalDeductMarks_Label, 9, 0, 1, 1);
	deductMark_GridLayout->addWidget(totalDeductMarks_LineEdit, 10, 0, 1, 1);
	deductMark_GridLayout->addWidget(finalTime_Label, 9, 1, 1, 1);
	deductMark_GridLayout->addWidget(finalTime_LineEdit, 10, 1, 1, 1);
	deductMark_GridLayout->addWidget(remake_Label, 11, 0, 1, 1);
	deductMark_GridLayout->addWidget(remake_ComboBox, 11, 1, 1, 1);

	
	//deductMark_Widget->show();
}

void DeduectMarksWidget::signalsAndSlots()
{
	connect(calculate_PushButton, &QPushButton::clicked, this, &DeduectMarksWidget::on_calculate_PushButton_clicked);
	connect(quitWidget_PushButton, &QPushButton::clicked, this, &DeduectMarksWidget::on_quitWidget_PushButton_clicked);
	connect(remake_ComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&DeduectMarksWidget::on_remake_ComboBox_CurrentIndexChanged);
}

void DeduectMarksWidget::init()
{
	currentRow = 0;
	isSecond = false;
}

void DeduectMarksWidget::readExcel()
{
	teamNum1_LineEdit->setText(manageExcel->readCellValue(currentRow, 1));
	teamName1_LineEdit->setText(manageExcel->readCellValue(currentRow, 2));
	bend_LineEdit->setText(manageExcel->readCellValue(currentRow + isSecond, 8));
	obstacle_LineEdit->setText(manageExcel->readCellValue(currentRow + isSecond, 9));
	impact_LineEdit->setText(manageExcel->readCellValue(currentRow + isSecond, 10));
	interference_LineEdit->setText(manageExcel->readCellValue(currentRow + isSecond, 11));
	if (manageExcel->readCellValue(currentRow + isSecond, 12) == "0") {
		isStop_ComboBox->setCurrentIndex(1);
	}
	if (manageExcel->readCellValue(currentRow + isSecond, 13) == "1") {
		isSlide_ComboBox->setCurrentIndex(1);
	}
	totalDeductMarks_LineEdit->setText(manageExcel->readCellValue(currentRow + isSecond, 14));
	finalTime_LineEdit->setText(manageExcel->readCellValue(currentRow + isSecond, 15));
	if (manageExcel->readCellValue(currentRow + isSecond, 11) == "1") {
		remake_ComboBox->setCurrentIndex(1);
	}
	//isStop_LineEdit->setText(manageExcel.readCellValue(currentRow, 12));
	//isSlide_LineEdit->setText(manageExcel.readCellValue(currentRow, 13));
}

int DeduectMarksWidget::timeStringToInt(QString timeString)
{
	int t_minu = 0;
	int t_sec = 0;
	int t_mesc = 0;
	int totalMescs = 0;

	t_minu = timeString.mid(0, 2).toInt();
	t_sec = timeString.mid(3, 2).toInt();
	t_mesc = timeString.mid(6, 3).toInt();

	totalMescs = t_minu * 60 * 1000 + t_sec * 1000 + t_mesc;
	return totalMescs;
	
}

QString DeduectMarksWidget::intToTimeString(int totalMescs)
{
	QString result;
	if (totalMescs > 3600000) {
		totalMescs = totalMescs - 3600000;
	}

	int t_mescs = totalMescs % 1000;
	int t_sec = (totalMescs / 1000) % 60;
	int t_minu = (totalMescs / (1000 * 60));

	result = tr("%1:%2:%3").arg(t_minu, 2, 10, QChar('0')).arg(t_sec, 2, 10, QChar('0')).arg(t_mescs, 3, 10, QChar('0'));
	return result;
}
