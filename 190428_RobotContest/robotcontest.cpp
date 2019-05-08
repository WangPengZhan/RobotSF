#include "robotcontest.h"

#pragma execution_character_set("utf-8")

RobotContest::RobotContest(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	//mySerialPort = new SerialPort();
	designUI();

	createDeductMarkWidget();

	signalsAndSlots();

	init();
}

void RobotContest::closeEvent(QCloseEvent * event)
{
	manageExcel.closeExcel();
}

void RobotContest::on_openSerialPort_PushButton_clicked()
{
	if (openSerialPort_PushButton->text() == "打开串口") {
		mySerialPort.setBaudRate(4);//9600
		mySerialPort.setDataBits(0);//8
		mySerialPort.setFlowControl(0);//none
		mySerialPort.setStopBits(0);//1
		mySerialPort.setParity(0);//none
		if (mySerialPort.openSerialPort(serialPort_ComboBox->currentIndex())) {
			openSerialPort_PushButton->setText("关闭串口");

		}
		else {
			QMessageBox::warning(this, tr("警告"), tr("串口打开失败！"), QMessageBox::Ok);
			mySerialPort.closeSerialPort();
		}
	}
	else {
		mySerialPort.closeSerialPort();
		openSerialPort_PushButton->setText(tr("打开串口"));
	}
}

void RobotContest::on_openExcel_PushButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("打开Excel文件"), QDir::currentPath(), tr("Excel文件(*xlsx)"));
	statusBar()->showMessage(tr("正在打开文件..."), 5000);
	if (manageExcel.openExcel(fileName)) {
		statusBar()->showMessage(fileName + tr("打开成功！"), 5000);
		openExcel_PushButton->setEnabled(false);

		teamNum_LineEdit->setText(manageExcel.readCellValue(currentRow, 1));
		teamName_LineEdit->setText(manageExcel.readCellValue(currentRow, 2));
		firstScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 3));
		secondScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 4));
		finalScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 5));
		facadeScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 6));
		lastOne_PushButton->setEnabled(true);
		nextOne_PushButton->setEnabled(true);
		startTime_PushButton->setEnabled(true);
		clearScore_PushButton->setEnabled(true);
		writeDeductTime_PushButton->setEnabled(true);
		verifyScore_PushButton->setEnabled(true);
	}
	else {
		statusBar()->showMessage(fileName + tr("打开失败！"), 5000);
	}
	
}

void RobotContest::on_newExcel_PushButton_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr(""), QDir::currentPath(), tr("Excel文件(*xlsx)"));
	manageExcel.newExcel(fileName);
}

void RobotContest::on_lastOne_PushButton_clicked()
{
	
	if (currentRow < 3) {
		lastOne_PushButton->setEnabled(false);
	}
	currentRow--;

	teamNum_LineEdit->setText(manageExcel.readCellValue(currentRow, 1));
	teamName_LineEdit->setText(manageExcel.readCellValue(currentRow, 2));
	firstScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 3));
	secondScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 4));
	finalScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 5));
	facadeScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 6));
}

void RobotContest::on_nextOne_PushButton_clicked()
{
	if (currentRow == 2) {
		lastOne_PushButton->setEnabled(true);
	}
	currentRow++;
	teamNum_LineEdit->setText(manageExcel.readCellValue(currentRow, 1));
	teamName_LineEdit->setText(manageExcel.readCellValue(currentRow, 2));
	firstScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 3));
	secondScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 4));
	finalScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 5));
	facadeScore_LineEdit->setText(manageExcel.readCellValue(currentRow, 6));
}

void RobotContest::on_verifyScore_PushButton_clicked()
{
	statusBar()->showMessage("开始写入成绩...", 5000);
	manageExcel.writeCellValue(currentRow, "C", firstScore_LineEdit->text());
	manageExcel.writeCellValue(currentRow, "D", secondScore_LineEdit->text());
	manageExcel.writeCellValue(currentRow, "E", finalScore_LineEdit->text());
	manageExcel.writeCellValue(currentRow, "F", facadeScore_LineEdit->text());
	float declineScoreOfFacade = 0;
	switch (facadeScore_LineEdit->text().toInt())
	{
	case 30:
		declineScoreOfFacade = 8.0;
		break;
	case 29:
		declineScoreOfFacade = 7.0;
		break;
	case 28:
		declineScoreOfFacade = 6.5;
		break;
	case 27:
		declineScoreOfFacade = 6.2;
		break;
	case 26:
		declineScoreOfFacade = 6.0;
		break;
	case 25:
		declineScoreOfFacade = 5.6;
		break;
	case 24:
		declineScoreOfFacade = 5.3;
		break;
	case 23:
		declineScoreOfFacade = 5.0;
		break;
	case 22:
		declineScoreOfFacade = 4.6;
		break;
	case 21:
		declineScoreOfFacade = 4.3;
		break;
	case 20:
		declineScoreOfFacade = 4.0;
		break;
	case 19:
		declineScoreOfFacade = 3.6;
		break;
	case 18:
		declineScoreOfFacade = 3.3;
		break;
	case 17:
		declineScoreOfFacade = 3.0;
		break;
	case 16:
		declineScoreOfFacade = 2.7;
		break;
	case 15:
		declineScoreOfFacade = 2.3;
		break;
	case 14:
		declineScoreOfFacade = 2.0;
		break;
	case 13:
		declineScoreOfFacade = 1.5;
		break;
	case 12:
		declineScoreOfFacade = 1.0;
		break;
	case 11:
		declineScoreOfFacade = 0.5;
		break;
	default:
		declineScoreOfFacade = 0.0;
		break;
	}
	manageExcel.writeCellValue(currentRow, "G", tr("%1").arg(declineScoreOfFacade));
	statusBar()->showMessage("写入成绩成功!", 5000);
}

void RobotContest::on_clearScore_PushButton_clicked()
{
	time_LCDNumber->display("00:00:000");
	//startTime_PushButton->setText(tr("开始计时"));
	//beginDateTime = CurrentDateTime;
	beginTime = CurrentTime;
	waitmsecs = 0;
	waitBegin = waitEnd;
	isClear = true;
	isOnce = false;
}

void RobotContest::on_startTime_PushBtton_clicked()
{
	if (startTime_PushButton->text() == tr("暂停")) {
		//waitBegin = QDateTime::currentDateTime();
		waitBegin = QTime::currentTime();
		timer.stop();
		startTime_PushButton->setText("继续");
		isClear = false;
	}
	else {
		if (isClear) {
			dealWithSerialPortDate("BBB");
		}
		else {
			//waitEnd = QDateTime::currentDateTime();
			waitEnd = QTime::currentTime();
			waitmsecs += waitBegin.msecsTo(waitEnd);
			timer.start(7);
			startTime_PushButton->setText(tr("暂停"));
		}
	}
}

void RobotContest::dealWithSerialPortDate(QByteArray data)
{
	if (data.contains("B")) {
		if (!isOnce) {
			startTime_PushButton->setEnabled(true);
			waitmsecs = 0;
			startTime_PushButton->setText(tr("暂停"));
			//beginDateTime = QDateTime::currentDateTime();
			beginTime = QTime::currentTime();
			timer.start(7);
			isOnce = true;
		}
	}
	else if(data.contains("E")){
		startTime_PushButton->setEnabled(false);
		timer.stop();
		isOnce = false;
		if (manageExcel.readCellValue(currentRow, "C").isEmpty()) {

			firstScore_LineEdit->setText(intToTimeString(totalmsecs));
		}
		else if (manageExcel.readCellValue(currentRow, "D").isEmpty()) {
			secondScore_LineEdit->setText(intToTimeString(totalmsecs));
		}
		if (timeStringToInt(firstScore_LineEdit->text()) > timeStringToInt(secondScore_LineEdit->text())) {
			finalScore_LineEdit->setText(secondScore_LineEdit->text());
		}
		else {
			finalScore_LineEdit->setText(firstScore_LineEdit->text());
		}
	}
}

void RobotContest::on_update_timeOver()
{
	//CurrentDateTime = QDateTime::currentDateTime();
	//totalmsecs = beginDateTime.msecsTo(CurrentDateTime);
	CurrentTime = QTime::currentTime();
	totalmsecs = beginTime.msecsTo(CurrentTime);
	totalmsecs -= waitmsecs;
	if (totalmsecs > 3600000) {
		totalmsecs = totalmsecs - 3600000;
	}
	int t_mescs = totalmsecs % 1000;
	int t_sec = (totalmsecs / 1000) % 60;
	int t_minu = (totalmsecs / 1000 / 60);

	theResult = tr("%1:%2:%3").arg(t_minu, 2, 10, QChar('0')).arg(t_sec, 2, 10, QChar('0')).arg(t_mescs, 3, 10, QChar('0'));
	time_LCDNumber->display(theResult);
}

void RobotContest::on_teamName_LineEdit_textChanged()
{
	QString nextTeamName = manageExcel.readCellValue(currentRow + 1, "B");
	if (!nextTeamName.isEmpty()) {
		tipsForTeams_Label->setText(tr("%1正在比赛\n请%2做好准备！").arg(teamName_LineEdit->text()).arg(nextTeamName));
	}
	else {
		tipsForTeams_Label->setText(tr("%1正在比赛\n").arg(teamName_LineEdit->text()));
	}
}

void RobotContest::on_saveTimer_timeout()
{
	manageExcel.saveExcel();
}

void RobotContest::on_writeDeductTime_PushButton_clicked()
{
	teamNum1_LineEdit->setText(manageExcel.readCellValue(currentRow, 1));
	teamName1_LineEdit->setText(manageExcel.readCellValue(currentRow, 2));
	bend_LineEdit->setText(manageExcel.readCellValue(currentRow, 8));
	obstacle_LineEdit->setText(manageExcel.readCellValue(currentRow, 9));
	impact_LineEdit->setText(manageExcel.readCellValue(currentRow, 10));
	interference_LineEdit->setText(manageExcel.readCellValue(currentRow, 11));
	if (manageExcel.readCellValue(currentRow, 12) == "0") {
		isStop_ComboBox->setCurrentIndex(1);
	}
	if (manageExcel.readCellValue(currentRow, 13) == "1") {
		isSlide_ComboBox->setCurrentIndex(1);
	}
	totalDeductMarks_LineEdit->setText(manageExcel.readCellValue(currentRow, 14));
	finalTime_LineEdit->setText(manageExcel.readCellValue(currentRow, 15));
	if (manageExcel.readCellValue(currentRow, 11) == "1") {
		remake_ComboBox->setCurrentIndex(1);
	}
	//isStop_LineEdit->setText(manageExcel.readCellValue(currentRow, 12));
	//isSlide_LineEdit->setText(manageExcel.readCellValue(currentRow, 13));
	deductMark_Widget->show();
}

void RobotContest::on_calculate_PushButton_clicked()
{
	int bendsConuts = 0, obstaclesCounts = 0, impactsCount = 0, interferencesCount = 0;
	int isStop = 1, isSlide = 0;
	int totalDeductMarks;
	float facadeScore = 0.0, betterScore = 0.0;
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
	totalDeductMarks = 10 * (isSlide + obstaclesCounts) + 5 * (impactsCount + interferencesCount + isStop +  bendsConuts); 
	totalDeductMarks_LineEdit->setText(tr("%1").arg(totalDeductMarks));

	if (!manageExcel.readCellValue(currentRow, 7).isEmpty()) {
		facadeScore = manageExcel.readCellValue(currentRow, 7).toFloat();
	}
	if (!manageExcel.readCellValue(currentRow, 5).isEmpty()) {
		betterScore = float(timeStringToInt(manageExcel.readCellValue(currentRow, 5))) / 1000;
	}
	
	finalTime = betterScore - facadeScore + totalDeductMarks;
	finalTime_LineEdit->setText(tr("%1").arg(finalTime));
}

void RobotContest::on_quitWidget_PushButton_clicked()
{
	manageExcel.writeCellValue(currentRow, 8, bend_LineEdit->text());
	manageExcel.writeCellValue(currentRow, 9, obstacle_LineEdit->text());
	manageExcel.writeCellValue(currentRow, 10, impact_LineEdit->text());
	manageExcel.writeCellValue(currentRow, 11, interference_LineEdit->text());
	manageExcel.writeCellValue(currentRow, 12, tr("%1").arg(isStop_ComboBox->currentIndex()));
	manageExcel.writeCellValue(currentRow, 13, tr("%1").arg(isSlide_ComboBox->currentIndex()));
	manageExcel.writeCellValue(currentRow, 14, totalDeductMarks_LineEdit->text());
	manageExcel.writeCellValue(currentRow, 15, finalTime_LineEdit->text());
	manageExcel.writeCellValue(currentRow, 16, tr("%1").arg(remake_ComboBox->currentIndex()));
	deductMark_Widget->close();
}

void RobotContest::designUI()
{
	setWindowTitle(tr("武汉科技大学 第五届机器人大赛"));
	setFont(QFont(tr("楷体"), 12));
	setWindowIcon(QIcon(":/hh.png"));
	//setStyleSheet("border-image:url(:/bg.png)");
	//QPalette palette;
	//palette.setColor(QPalette::Background,QColor(255, 255, 255));
	title_Label = new QLabel(tr("武汉科技大学\n第五届机器人大赛"), this);
	title_Label->setAlignment(Qt::AlignCenter);
	title_Label->setFont(QFont("楷体",56));
	//title_Label->setPalette(palette);
	title_Label->setFrameStyle(1);

	//palette.setColor(QPalette::Background, QColor(255, 255, 255));
	time_LCDNumber = new QLCDNumber(this);
	time_LCDNumber->setMinimumHeight(100);
	time_LCDNumber->setDigitCount(9);
	time_LCDNumber->display(tr("00:00:000"));
	time_LCDNumber->setFont(QFont(tr("楷体"),48));
	//time_LCDNumber->setPalette(palette);

	serialPort_ComboBox = new QComboBox(this);
	searchSerialPort_PushButton = new QPushButton(tr("搜索串口"), this);
	searchSerialPort_PushButton->setStatusTip(tr("搜索系统串口"));
	openSerialPort_PushButton = new QPushButton(tr("打开串口"), this);
	openSerialPort_PushButton->setStatusTip(tr("打开当前串口"));
	openSerialPort_PushButton->setCheckable(true);
	openSerialPort_PushButton->setEnabled(false);
	openExcel_PushButton = new QPushButton(tr("加载文件"), this);
	openExcel_PushButton->setStatusTip(tr("加载比赛的Excel文件"));
	newExcel_PushButton = new QPushButton(tr("新建Excel"), this);
	newExcel_PushButton->setStatusTip(tr("新建一个Excel文件"));
	writeDeductTime_PushButton = new QPushButton(tr("录入加罚成绩"), this);
	writeDeductTime_PushButton->setEnabled(false);
	//writeDeductTime_PushButton->setEnabled(false);

	//tipsForteam_TextBrowser = new QTextBrowser(this);
	//tipsForteam_TextBrowser->setEnabled(false);
	//tipsForteam_TextBrowser->setText(tr("某某队正在比赛\n请某某队做好准备！"));
	//tipsForteam_TextBrowser->setFont(QFont("楷体",48));

	tipsForTeams_Label = new QLabel(this);
	tipsForTeams_Label->setText(tr("机器人协会\n欢迎您！"));
	tipsForTeams_Label->setFont(QFont("楷体", 48));
	tipsForTeams_Label->setAlignment(Qt::AlignCenter);

	teamNum_Label = new QLabel(tr("参赛序号"), this);
	teamNum_Label->setAlignment(Qt::AlignCenter);
	teamNum_LineEdit = new QLineEdit(this);
	teamNum_LineEdit->setAlignment(Qt::AlignCenter);
	teamNum_LineEdit->setEnabled(false);
	teamName_Label = new QLabel(tr("队长姓名"), this);
	teamName_Label->setAlignment(Qt::AlignCenter);
	teamName_LineEdit = new QLineEdit(this);
	teamName_LineEdit->setAlignment(Qt::AlignCenter);
	teamName_LineEdit->setEnabled(false);
	firstScore_Label = new QLabel(tr("第一次成绩"), this);
	firstScore_Label->setAlignment(Qt::AlignCenter);
	firstScore_LineEdit = new QLineEdit(this);
	firstScore_LineEdit->setAlignment(Qt::AlignCenter);
	secondScore_Label = new QLabel(tr("第二次成绩"), this);
	secondScore_Label->setAlignment(Qt::AlignCenter);
	secondScore_LineEdit = new QLineEdit(this);
	secondScore_LineEdit->setAlignment(Qt::AlignCenter);
	finalScore_Label = new QLabel(tr("最佳成绩"), this);
	finalScore_Label->setAlignment(Qt::AlignCenter);
	finalScore_LineEdit = new QLineEdit(this);
	finalScore_LineEdit->setAlignment(Qt::AlignCenter);
	facadeScore_Label = new QLabel(tr("外观分"), this);
	facadeScore_Label->setAlignment(Qt::AlignCenter);
	facadeScore_LineEdit = new QLineEdit(this);
	facadeScore_LineEdit->setAlignment(Qt::AlignCenter);

	lastOne_PushButton = new QPushButton(tr("上一个"), this);
	lastOne_PushButton->setStatusTip(tr("上一支队伍"));
	lastOne_PushButton->setEnabled(false);
	nextOne_PushButton = new QPushButton(tr("下一个"), this);
	nextOne_PushButton->setStatusTip(tr("下一支队伍"));
	nextOne_PushButton->setEnabled(false);
	verifyScore_PushButton = new QPushButton(tr("写入成绩"), this);
	verifyScore_PushButton->setStatusTip(tr("写入现有成绩"));
	verifyScore_PushButton->setEnabled(false);
	startTime_PushButton = new QPushButton(tr("开始计时"), this);
	startTime_PushButton->setStatusTip(tr("启动计时器计时"));
	startTime_PushButton->setEnabled(false);
	startTime_PushButton->setCheckable(true);
	clearScore_PushButton = new QPushButton(tr("清除"), this);
	clearScore_PushButton->setStatusTip(tr("清除复位，开始下一次计时"));
	clearScore_PushButton->setEnabled(false);
	quit_PushButton = new QPushButton(tr("退出"), this);
	sign_Label = new QLabel(tr("WUST 机器人协会"), this);
	sign_Label->setAlignment(Qt::AlignRight);
	statusBar()->addWidget(sign_Label, Qt::AlignRight);


	center = new QWidget(this);
	center->setAutoFillBackground(true);
	
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(180, 193, 255));
	
	palette.setBrush(QPalette::Background, QBrush(QPixmap(":/bg.png")));
	center->setPalette(palette);
	//center->setStyleSheet("border-image: \*url();");
	setCentralWidget(center);
	main_GridLayout = new QGridLayout(center);

	main_GridLayout->addWidget(title_Label,0,0,1,6);
	main_GridLayout->addWidget(time_LCDNumber,1,0,1,6);
	main_GridLayout->addWidget(serialPort_ComboBox,2,0,1,2);
	main_GridLayout->addWidget(searchSerialPort_PushButton,3,0,1,1);
	main_GridLayout->addWidget(openSerialPort_PushButton,3,1,1,1);
	main_GridLayout->addWidget(openExcel_PushButton,4,0,1,1);
	main_GridLayout->addWidget(newExcel_PushButton,4,1,1,1);
	main_GridLayout->addWidget(writeDeductTime_PushButton,5,0,1,1);
	//main_GridLayout->addWidget(tipsForteam_TextBrowser,2,2,3,4);
	main_GridLayout->addWidget(tipsForTeams_Label,2,2,4,4);
	main_GridLayout->addWidget(teamNum_Label,6,0,1,1);
	main_GridLayout->addWidget(teamNum_LineEdit,7,0,1,1);
	main_GridLayout->addWidget(teamName_Label,6,1,1,1);
	main_GridLayout->addWidget(teamName_LineEdit,7,1,1,1);
	main_GridLayout->addWidget(firstScore_Label,6,2,1,1);
	main_GridLayout->addWidget(firstScore_LineEdit,7,2,1,1);
	main_GridLayout->addWidget(secondScore_Label,6,3,1,1);
	main_GridLayout->addWidget(secondScore_LineEdit,7,3,1,1);
	main_GridLayout->addWidget(finalScore_Label,6,4,1,1);
	main_GridLayout->addWidget(finalScore_LineEdit,7,4,1,1);
	main_GridLayout->addWidget(facadeScore_Label,6,5,1,1);
	main_GridLayout->addWidget(facadeScore_LineEdit,7,5,1,1);
	main_GridLayout->addWidget(lastOne_PushButton,8,0,1,1);
	main_GridLayout->addWidget(nextOne_PushButton,8,1,1,1);
	main_GridLayout->addWidget(verifyScore_PushButton,8,2,1,1);
	main_GridLayout->addWidget(startTime_PushButton,8,3,1,1);
	main_GridLayout->addWidget(clearScore_PushButton,8,4,1,1);
	main_GridLayout->addWidget(quit_PushButton,8,5,1,1);
}

void RobotContest::createDeductMarkWidget()
{
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
	isStop_ComboBox->addItem(tr("是"),0);
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
	remake_Label = new QLabel(tr("特殊情况"), this);
	remake_Label->setAlignment(Qt::AlignCenter);
	remake_ComboBox = new QComboBox(this);
	remake_ComboBox->addItem(tr("否"));
	remake_ComboBox->addItem(tr("是"));

	deductMark_Widget = new QWidget();
	deductMark_Widget->setFont(QFont(tr("楷体"), 12));
	deductMark_Widget->setWindowTitle(tr("加罚时间录入界面"));

	deductMark_GridLayout = new QGridLayout(deductMark_Widget);
	deductMark_GridLayout->addWidget(teamNum1_Label,0,0,1,1);
	deductMark_GridLayout->addWidget(teamNum1_LineEdit,0,1,1,1);
	deductMark_GridLayout->addWidget(teamName1_Label,1,0,1,1);
	deductMark_GridLayout->addWidget(teamName1_LineEdit,1,1,1,1);
	deductMark_GridLayout->addWidget(bend_Label,2,0,1,1);
	deductMark_GridLayout->addWidget(bend_LineEdit,2,1,1,1);
	deductMark_GridLayout->addWidget(obstacle_Label,3,0,1,1);
	deductMark_GridLayout->addWidget(obstacle_LineEdit,3,1,1,1);
	deductMark_GridLayout->addWidget(impact_Label,4,0,1,1);
	deductMark_GridLayout->addWidget(impact_LineEdit,4,1,1,1);
	deductMark_GridLayout->addWidget(interference_Label,5,0,1,1);
	deductMark_GridLayout->addWidget(interference_LineEdit,5,1,1,1);

	deductMark_GridLayout->addWidget(isStop_Label,6,0,1,1);
	deductMark_GridLayout->addWidget(isStop_ComboBox,6,1,1,1);
	//deductMark_GridLayout->addWidget(isStop_LineEdit,6,1,1,1);
	deductMark_GridLayout->addWidget(isSlide_Label,7,0,1,1);
	//deductMark_GridLayout->addWidget(isSlide_LineEdit,7,1,1,1);
	deductMark_GridLayout->addWidget(isSlide_ComboBox,7,1,1,1);

	deductMark_GridLayout->addWidget(calculate_PushButton,8,0,1,1);
	deductMark_GridLayout->addWidget(quitWidget_PushButton,8,1,1,1);
	deductMark_GridLayout->addWidget(totalDeductMarks_Label,9,0,1,1);
	deductMark_GridLayout->addWidget(totalDeductMarks_LineEdit,10,0,1,1);
	deductMark_GridLayout->addWidget(finalTime_Label,9,1,1,1);
	deductMark_GridLayout->addWidget(finalTime_LineEdit,10,1,1,1);
	deductMark_GridLayout->addWidget(remake_Label,11,0,1,1);
	deductMark_GridLayout->addWidget(remake_ComboBox,11,1,1,1);
	//deductMark_Widget->show();
}

void RobotContest::signalsAndSlots()
{
	connect(searchSerialPort_PushButton, &QPushButton::clicked, this, &RobotContest::on_searchSerialPort_PushButton_clicked);
	connect(&mySerialPort, &SerialPort::serialPassData, this, &RobotContest::dealWithSerialPortDate);
	connect(openExcel_PushButton, &QPushButton::clicked, this, &RobotContest::on_openExcel_PushButton_clicked);
	connect(openSerialPort_PushButton, &QPushButton::clicked, this, &RobotContest::on_openSerialPort_PushButton_clicked);
	connect(newExcel_PushButton, &QPushButton::clicked, this, &RobotContest::on_newExcel_PushButton_clicked);
	connect(lastOne_PushButton, &QPushButton::clicked, this, &RobotContest::on_lastOne_PushButton_clicked);
	connect(nextOne_PushButton, &QPushButton::clicked, this, &RobotContest::on_nextOne_PushButton_clicked);
	connect(verifyScore_PushButton, &QPushButton::clicked, this, &RobotContest::on_verifyScore_PushButton_clicked);
	connect(startTime_PushButton, &QPushButton::clicked, this, &RobotContest::on_startTime_PushBtton_clicked);
	connect(clearScore_PushButton, &QPushButton::clicked, this, &RobotContest::on_clearScore_PushButton_clicked);

	connect(&saveTimer, &QTimer::timeout, this, &RobotContest::on_saveTimer_timeout);
	connect(&timer, &QTimer::timeout, this, &RobotContest::on_update_timeOver);
	connect(quit_PushButton, &QPushButton::clicked, this, &RobotContest::close);
	connect(teamName_LineEdit, &QLineEdit::textChanged, this, &RobotContest::on_teamName_LineEdit_textChanged);
	connect(writeDeductTime_PushButton, &QPushButton::clicked, this, &RobotContest::on_writeDeductTime_PushButton_clicked);

	connect(calculate_PushButton, &QPushButton::clicked, this, &RobotContest::on_calculate_PushButton_clicked);
	connect(quitWidget_PushButton, &QPushButton::clicked, this, &RobotContest::on_quitWidget_PushButton_clicked);
}

void RobotContest::init()
{
	currentRow = 2;
	//mySerialPort = new SerialPort();
	msecs = 0;
	sec = 0;
	minu = 0;
	totalmsecs = 0;
	isClear = true;
	isOnce = false;
	//beginDateTime = QDateTime::currentDateTime();
}

int RobotContest::timeStringToInt(QString timeString)
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

QString RobotContest::intToTimeString(int totalMescs)
{
	QString result;
	if (totalMescs > 3600000) {
		totalMescs = totalMescs - 3600000;
	}

	int t_mescs = totalMescs % 1000;
	int t_sec = (totalMescs / 1000) % 60;
	int t_minu = (totalMescs / 1000 / 60);

	result = tr("%1:%2:%3").arg(t_minu, 2, 10, QChar('0')).arg(t_sec, 2, 10, QChar('0')).arg(t_mescs, 3, 10, QChar('0'));
	return result;
}

int RobotContest::facadeScoreToTime(QString score)
{
	return 0;
}

void RobotContest::on_searchSerialPort_PushButton_clicked()
{
	serialPort_ComboBox->clear();
	serialPort_ComboBox->addItems(mySerialPort.searchSerialPort());
	if (serialPort_ComboBox->currentText() != tr("没有串口，请重新连接串口！")) {
		openSerialPort_PushButton->setEnabled(true);
	}
}