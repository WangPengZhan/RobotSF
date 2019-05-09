#include "robotcontest.h"

#pragma execution_character_set("utf-8")

RobotContest::RobotContest(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	//mySerialPort = new SerialPort();
	designUI();

	signalsAndSlots();

	init();

	loadQSSFile(":/style.qss");
}

RobotContest::~RobotContest()
{
	delete manageExcel;
	delete center;
}

void RobotContest::closeEvent(QCloseEvent * event)
{
	manageExcel->closeExcel();
}

void RobotContest::on_openSerialPort_PushButton_clicked()
{
	if (openSerialPort_PushButton->text() == "�򿪴���") {
		mySerialPort.setBaudRate(4);//9600
		mySerialPort.setDataBits(0);//8
		mySerialPort.setFlowControl(0);//none
		mySerialPort.setStopBits(0);//1
		mySerialPort.setParity(0);//none
		if (mySerialPort.openSerialPort(serialPort_ComboBox->currentIndex())) {
			openSerialPort_PushButton->setText("�رմ���");
		}
		else {
			QMessageBox::warning(this, tr("����"), tr("���ڴ�ʧ�ܣ�"), QMessageBox::Ok);
			mySerialPort.closeSerialPort();
		}
	}
	else {
		mySerialPort.closeSerialPort();
		openSerialPort_PushButton->setText(tr("�򿪴���"));
	}
}

void RobotContest::on_openExcel_PushButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("��Excel�ļ�"), QDir::currentPath(), tr("Excel�ļ�(*xlsx)"));
	statusBar()->showMessage(tr("���ڴ��ļ�..."), 5000);
	if (manageExcel->openExcel(fileName)) {
		statusBar()->showMessage(fileName + tr("�򿪳ɹ���"), 5000);
		openExcel_PushButton->setEnabled(false);

		teamNum_LineEdit->setText(manageExcel->readCellValue(currentRow, 1));
		teamName_LineEdit->setText(manageExcel->readCellValue(currentRow, 2));
		firstScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 5));
		secondScore_LineEdit->setText(manageExcel->readCellValue(currentRow + 1, 5));
		finalScore_LineEdit->setText(manageExcel->readCellValue(currentRow + 1, 15));
		facadeScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 6));
		lastOne_PushButton->setEnabled(true);
		nextOne_PushButton->setEnabled(true);
		startTime_PushButton->setEnabled(true);
		clearScore_PushButton->setEnabled(true);
		writeDeductTime_PushButton->setEnabled(true);
		verifyScore_PushButton->setEnabled(true);
		//saveTimer.start(120000);
	}
	else {
		statusBar()->showMessage(fileName + tr("��ʧ�ܣ�"), 5000);
	}
}

void RobotContest::on_newExcel_PushButton_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr(""), QDir::currentPath(), tr("Excel�ļ�(*xlsx)"));
	manageExcel->newExcel(fileName);
}

void RobotContest::on_lastOne_PushButton_clicked()
{
	if (currentRow < 5) {
		lastOne_PushButton->setEnabled(false);
	}
	currentRow -= 2;

	teamNum_LineEdit->setText(manageExcel->readCellValue(currentRow, 1));
	teamName_LineEdit->setText(manageExcel->readCellValue(currentRow, 2));
	firstScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 3));
	secondScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 4));
	finalScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 5));
	facadeScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 6));
}

void RobotContest::on_nextOne_PushButton_clicked()
{
	if (currentRow == 2) {
		lastOne_PushButton->setEnabled(true);
	}
	currentRow += 2;
	teamNum_LineEdit->setText(manageExcel->readCellValue(currentRow, 1));
	teamName_LineEdit->setText(manageExcel->readCellValue(currentRow, 2));
	firstScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 3));
	secondScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 4));
	finalScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 5));
	facadeScore_LineEdit->setText(manageExcel->readCellValue(currentRow, 6));
}

void RobotContest::on_verifyScore_PushButton_clicked()
{
	statusBar()->showMessage("��ʼд��ɼ�...", 5000);
	if (manageExcel->readCellValue(currentRow, "C").isEmpty()) {
		manageExcel->writeCellValue(currentRow, "C", "��һ�γɼ�");
	}
	if (manageExcel->readCellValue(currentRow + 1, "C").isEmpty()) {
		manageExcel->writeCellValue(currentRow + 1, "C", "�ڶ��γɼ�");
	}

	manageExcel->writeCellValue(currentRow, "E", firstScore_LineEdit->text());
	manageExcel->writeCellValue(currentRow + 1, "E", secondScore_LineEdit->text());
	//manageExcel->writeCellValue(currentRow, "E", finalScore_LineEdit->text());
	manageExcel->writeCellValue(currentRow , "F", facadeScore_LineEdit->text());
	manageExcel->writeCellValue(currentRow, "G", tr("%1").arg(facadeScoreToTime()));
	manageExcel->writeCellValue(currentRow + 1, "F", facadeScore_LineEdit->text());
	manageExcel->writeCellValue(currentRow + 1, "G", tr("%1").arg(facadeScoreToTime()));

	statusBar()->showMessage("д��ɼ��ɹ�!", 5000);
}

void RobotContest::on_clearScore_PushButton_clicked()
{
	time_LCDNumber->display("00:00:000");
	//startTime_PushButton->setText(tr("��ʼ��ʱ"));
	//beginDateTime = CurrentDateTime;
	beginTime = CurrentTime;
	waitmsecs = 0;
	waitBegin = waitEnd;
	isClear = true;
	isOnce = false;
}

void RobotContest::on_startTime_PushBtton_clicked()
{
	if (startTime_PushButton->text() == tr("��ͣ")) {
		//waitBegin = QDateTime::currentDateTime();
		waitBegin = QTime::currentTime();
		timer.stop();
		startTime_PushButton->setText("����");
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
			startTime_PushButton->setText(tr("��ͣ"));
		}
	}
}

void RobotContest::dealWithSerialPortDate(QByteArray data)
{
	if (data.contains("B")) {
		if (!isOnce) {
			startTime_PushButton->setEnabled(true);
			waitmsecs = 0;
			startTime_PushButton->setText(tr("��ͣ"));
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
		if (manageExcel->readCellValue(currentRow, "E").isEmpty()) {
			isSecond = false;
			firstScore_LineEdit->setText(intToTimeString(totalmsecs));
		}
		else if (manageExcel->readCellValue(currentRow + 1, "E").isEmpty()) {
			isSecond = true;
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
	theResult = intToTimeString(totalmsecs);
	time_LCDNumber->display(theResult);
}

void RobotContest::on_teamName_LineEdit_textChanged()
{
	QString nextTeamName = manageExcel->readCellValue(currentRow + 2, "B");
	if (!nextTeamName.isEmpty()) {
		tipsForTeams_Label->setText(tr("%1���ڱ���\n��%2����׼����").arg(teamName_LineEdit->text()).arg(nextTeamName));
	}
	else {
		tipsForTeams_Label->setText(tr("%1���ڱ���\n").arg(teamName_LineEdit->text()));
	}
}

void RobotContest::on_saveTimer_timeout()
{
	manageExcel->saveExcel();
}

void RobotContest::on_writeDeductTime_PushButton_clicked()
{
	widget.setSecond(isSecond);
	widget.setCurrentRow(currentRow);
	widget.show();
}

void RobotContest::designUI()
{
	setWindowTitle(tr("�人�Ƽ���ѧ ���������˴���"));
	setFont(QFont(tr("����"), 12));
	setWindowIcon(QIcon(":/hh.png"));
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(153, 178, 255));
	setPalette(palette);
	title_Label = new QLabel(tr("�人�Ƽ���ѧ\n���������˴���"), this);
	title_Label->setAlignment(Qt::AlignCenter);
	title_Label->setFont(QFont("����",56));
	//title_Label->setPalette(palette);
	title_Label->setFrameStyle(1);

	//palette.setColor(QPalette::Background, QColor(255, 255, 255));
	time_LCDNumber = new QLCDNumber(this);
	time_LCDNumber->setMinimumHeight(100);
	time_LCDNumber->setDigitCount(9);
	time_LCDNumber->display(tr("00:00:000"));
	time_LCDNumber->setFont(QFont(tr("����"),48));
	//time_LCDNumber->setPalette(palette);

	serialPort_ComboBox = new QComboBox(this);
	searchSerialPort_PushButton = new QPushButton(tr("��������"), this);
	searchSerialPort_PushButton->setStatusTip(tr("����ϵͳ����"));
	openSerialPort_PushButton = new QPushButton(tr("�򿪴���"), this);
	openSerialPort_PushButton->setStatusTip(tr("�򿪵�ǰ����"));
	openSerialPort_PushButton->setCheckable(true);
	openSerialPort_PushButton->setEnabled(false);
	openExcel_PushButton = new QPushButton(tr("�����ļ�"), this);
	openExcel_PushButton->setStatusTip(tr("���ر�����Excel�ļ�"));
	newExcel_PushButton = new QPushButton(tr("�½�Excel"), this);
	newExcel_PushButton->setStatusTip(tr("�½�һ��Excel�ļ�"));
	writeDeductTime_PushButton = new QPushButton(tr("¼��ӷ��ɼ�"), this);
	writeDeductTime_PushButton->setEnabled(false);
	//writeDeductTime_PushButton->setEnabled(false);

	//tipsForteam_TextBrowser = new QTextBrowser(this);
	//tipsForteam_TextBrowser->setEnabled(false);
	//tipsForteam_TextBrowser->setText(tr("ĳĳ�����ڱ���\n��ĳĳ������׼����"));
	//tipsForteam_TextBrowser->setFont(QFont("����",48));

	tipsForTeams_Label = new QLabel(this);
	tipsForTeams_Label->setText(tr("������Э��\n��ӭ����"));
	tipsForTeams_Label->setFont(QFont("����", 48));
	tipsForTeams_Label->setAlignment(Qt::AlignCenter);

	teamNum_Label = new QLabel(tr("�������"), this);
	teamNum_Label->setAlignment(Qt::AlignCenter);
	teamNum_LineEdit = new QLineEdit(this);
	teamNum_LineEdit->setAlignment(Qt::AlignCenter);
	teamNum_LineEdit->setEnabled(false);
	teamName_Label = new QLabel(tr("��������"), this);
	teamName_Label->setAlignment(Qt::AlignCenter);
	teamName_LineEdit = new QLineEdit(this);
	teamName_LineEdit->setAlignment(Qt::AlignCenter);
	teamName_LineEdit->setEnabled(false);
	firstScore_Label = new QLabel(tr("��һ�γɼ�"), this);
	firstScore_Label->setAlignment(Qt::AlignCenter);
	firstScore_LineEdit = new QLineEdit(this);
	firstScore_LineEdit->setAlignment(Qt::AlignCenter);
	secondScore_Label = new QLabel(tr("�ڶ��γɼ�"), this);
	secondScore_Label->setAlignment(Qt::AlignCenter);
	secondScore_LineEdit = new QLineEdit(this);
	secondScore_LineEdit->setAlignment(Qt::AlignCenter);
	finalScore_Label = new QLabel(tr("��ѳɼ�"), this);
	finalScore_Label->setAlignment(Qt::AlignCenter);
	finalScore_LineEdit = new QLineEdit(this);
	finalScore_LineEdit->setAlignment(Qt::AlignCenter);
	facadeScore_Label = new QLabel(tr("��۷�"), this);
	facadeScore_Label->setAlignment(Qt::AlignCenter);
	facadeScore_LineEdit = new QLineEdit(this);
	facadeScore_LineEdit->setAlignment(Qt::AlignCenter);

	lastOne_PushButton = new QPushButton(tr("��һ��"), this);
	lastOne_PushButton->setStatusTip(tr("��һ֧����"));
	lastOne_PushButton->setEnabled(false);
	nextOne_PushButton = new QPushButton(tr("��һ��"), this);
	nextOne_PushButton->setStatusTip(tr("��һ֧����"));
	nextOne_PushButton->setEnabled(false);
	verifyScore_PushButton = new QPushButton(tr("д��ɼ�"), this);
	verifyScore_PushButton->setStatusTip(tr("д�����гɼ�"));
	verifyScore_PushButton->setEnabled(false);
	startTime_PushButton = new QPushButton(tr("��ʼ��ʱ"), this);
	startTime_PushButton->setStatusTip(tr("������ʱ����ʱ"));
	startTime_PushButton->setEnabled(false);
	startTime_PushButton->setCheckable(true);
	clearScore_PushButton = new QPushButton(tr("���"), this);
	clearScore_PushButton->setStatusTip(tr("�����λ����ʼ��һ�μ�ʱ"));
	clearScore_PushButton->setEnabled(false);
	quit_PushButton = new QPushButton(tr("�˳�"), this);
	sign_Label = new QLabel(tr("WUST ������Э��"), this);
	sign_Label->setAlignment(Qt::AlignRight);
	statusBar()->addWidget(sign_Label, Qt::AlignRight);


	center = new QWidget(this);
	center->setAutoFillBackground(true);
	//palette.setBrush(QPalette::Background, QBrush(QPixmap(":/bg.png")));
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
}

void RobotContest::init()
{
	manageExcel = new ManageExcel();
	widget.setManageExcel(manageExcel);
	currentRow = 2;
	//mySerialPort = new SerialPort();
	msecs = 0;
	sec = 0;
	minu = 0;
	totalmsecs = 0;
	isClear = true;
	isOnce = false;
	isSecond = false;
	//beginDateTime = QDateTime::currentDateTime();
}

void RobotContest::loadQSSFile(const QString style)
{
	QFile qss(style);
	qss.open(QIODevice::ReadOnly);
	setStyleSheet(qss.readAll());
	qss.close();
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
	int t_minu = (totalMescs / (1000 * 60));

	result = tr("%1:%2:%3").arg(t_minu, 2, 10, QChar('0')).arg(t_sec, 2, 10, QChar('0')).arg(t_mescs, 3, 10, QChar('0'));
	return result;
}

 float RobotContest::facadeScoreToTime()
{
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
	return declineScoreOfFacade;
}

void RobotContest::on_searchSerialPort_PushButton_clicked()
{
	serialPort_ComboBox->clear();
	serialPort_ComboBox->addItems(mySerialPort.searchSerialPort());
	if (serialPort_ComboBox->currentText() != tr("û�д��ڣ����������Ӵ��ڣ�")) {
		openSerialPort_PushButton->setEnabled(true);
	}
}