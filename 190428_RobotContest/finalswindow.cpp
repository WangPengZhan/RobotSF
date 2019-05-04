#pragma execution_character_set("utf-8")

#include "finalswindow.h"

FinalsWindow::FinalsWindow(QWidget *parent)
	: QMainWindow(parent)
{
	designUI();
	createVerifyTimeWidget();
	signalsAndSlots();
	init();
	VoiceDeal a;
	a.show();
}

FinalsWindow::~FinalsWindow()
{

}

void FinalsWindow::on_startTime_PushButton_clicked()
{
	if (startTime_PushButton->text() == tr("��ʼ����ʱ")) {
		startTime_PushButton->setText("����");
		beginTime = QTime::currentTime();
		isOnce = false;
	}
	if (startTime_PushButton->text() == tr("��ͣ")) {
		waitBegin = QTime::currentTime();
		timer.stop();
		startTime_PushButton->setText("����");
	}
	else {
		if(isOnce){
			waitEnd = QTime::currentTime();
			isOnce = true;
		}
		waitmsecs += waitBegin.msecsTo(waitEnd);
		timer.start(7);
		startTime_PushButton->setText(tr("��ͣ"));	
	}
}

void FinalsWindow::on_clearTime_PushButton_clicked()
{
	totalmsecs = minu * 60 * 1000 + sec * 1000 + msecs;
	time_LCDNumber->display(intToTimeString(totalmsecs));
	beginTime = currentTime;
	waitmsecs = 0;
	waitBegin = waitEnd;
	//startTime_PushButton->setText(tr("��ʼ����ʱ"));
}

void FinalsWindow::on_verifyTime_PushButton_clicked()
{
	verifyTime_Widget->show();
}

void FinalsWindow::on_timer_timeout()
{
	currentTime = QTime::currentTime();
	int passedMsecs = beginTime.msecsTo(currentTime);
	showmsecs = totalmsecs + waitmsecs - passedMsecs;
	if (showmsecs < 0) {
		timer.stop();
	}
	theResult = intToTimeString(showmsecs);
	time_LCDNumber->display(theResult);
}

void FinalsWindow::on_verify_PushButton_clicked()
{
	int ret = QMessageBox::information(this, tr("֪ͨ"), tr("��ȷ���������ʱ�䣿"), QMessageBox::Ok,
		QMessageBox::Discard, QMessageBox::Cancel);
	switch (ret)
	{
	case QMessageBox::Ok:
		minu = minu_SpinBox->value();
		sec = sec_SpinBox->value();
		msecs = msecs_SpinBox->value();
		on_clearTime_PushButton_clicked();
		break;
	case QMessageBox::Discard:
		break;
	case QMessageBox::Cancel:
		verifyTime_Widget->close();
	default:
		break;
	}
}

void FinalsWindow::signalsAndSlots()
{
	connect(quit_PushButton, &QPushButton::clicked, this, &FinalsWindow::close);
	connect(&timer, &QTimer::timeout, this, &FinalsWindow::on_timer_timeout);
	connect(startTime_PushButton, &QPushButton::clicked, this, &FinalsWindow::on_startTime_PushButton_clicked);
	connect(clearTime_PushButton, &QPushButton::clicked, this, &FinalsWindow::on_clearTime_PushButton_clicked);
	connect(verify_PushButton, &QPushButton::clicked, this, &FinalsWindow::on_verify_PushButton_clicked);
	connect(verifyTime_PushButton, &QPushButton::clicked, this, &FinalsWindow::on_verifyTime_PushButton_clicked);
}

void FinalsWindow::init()
{
	minu = 10, sec = 0, msecs = 0;
	totalmsecs = minu * 60 * 1000 + sec * 1000 + msecs;
	showmsecs = totalmsecs;
	waitmsecs = 0;
	waitEnd = QTime::currentTime();
	waitBegin = waitEnd;
	isOnce = true;
}

int FinalsWindow::timeStringToInt(QString timeString)
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

QString FinalsWindow::intToTimeString(int totalMescs)
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

void FinalsWindow::designUI()
{
	setWindowIcon(QIcon(":/bg.png"));
	setWindowTitle(tr("���������˴�������"));
	setFont(QFont(tr("����"), 16));

	title_Label = new QLabel(tr("�人�Ƽ���ѧ\n���������˴���-����"), this);
	title_Label->setAlignment(Qt::AlignCenter);
	title_Label->setFont(QFont("����", 56));
	time_LCDNumber = new QLCDNumber(this);
	time_LCDNumber->setDigitCount(9);
	time_LCDNumber->display(tr("10:00:000"));
	time_LCDNumber->setFont(QFont(tr(""), 48));
	tipsForTeams_Label = new QLabel(this);
	tipsForTeams_Label->setText(tr("������Э�Ỷӭ����"));
	tipsForTeams_Label->setFont(QFont("����", 48));
	tipsForTeams_Label->setAlignment(Qt::AlignCenter);
	startTime_PushButton = new QPushButton(tr("��ʼ����ʱ"), this);
	startTime_PushButton->setStatusTip(tr("��������ʱ"));
	clearTime_PushButton = new QPushButton(tr("���"), this);
	verifyTime_PushButton = new QPushButton(tr("����ʱ��"), this);
	quit_PushButton = new QPushButton(tr("�˳�"), this);
	sign_Label = new QLabel(tr("WUST ������Э��"), this);
	sign_Label->setAlignment(Qt::AlignRight);
	statusBar()->addWidget(sign_Label, Qt::AlignRight);

	center_Widget = new QWidget(this);
	setCentralWidget(center_Widget);
	main_GridLayout = new QGridLayout(center_Widget);
	main_GridLayout->addWidget(title_Label,0,0,1,6);
	main_GridLayout->addWidget(time_LCDNumber,1,0,1,6);
	main_GridLayout->addWidget(startTime_PushButton,2,0,1,1);
	main_GridLayout->addWidget(clearTime_PushButton,3,0,1,1);
	main_GridLayout->addWidget(verifyTime_PushButton,4,0,1,1);
	main_GridLayout->addWidget(quit_PushButton,5,0,1,1);
	main_GridLayout->addWidget(tipsForTeams_Label,2,1,4,5);
}

void FinalsWindow::createVerifyTimeWidget()
{
	minu_Label = new QLabel(tr("����"), this);
	minu_Label->setAlignment(Qt::AlignCenter);
	minu_SpinBox = new QSpinBox(this);
	minu_SpinBox->setValue(10);
	minu_SpinBox->setRange(0, 99);
	sec_Label = new QLabel(tr("��"), this);
	sec_SpinBox = new QSpinBox(this);
	sec_SpinBox->setValue(0);
	sec_SpinBox->setRange(0, 99);
	msecs_Label = new QLabel(tr("����"), this);
	msecs_SpinBox = new QSpinBox(this);
	msecs_SpinBox->setRange(0, 999);
	msecs_SpinBox->setValue(0);
	verify_PushButton = new QPushButton(tr("ȷ��"), this);

	verifyTime_Widget = new QWidget();
	verifyTime_GridLayout = new QGridLayout(verifyTime_Widget);
	verifyTime_GridLayout->addWidget(minu_Label,0,0,1,1);
	verifyTime_GridLayout->addWidget(minu_SpinBox,1,0,1,1);
	verifyTime_GridLayout->addWidget(sec_Label,0,1,1,1);
	verifyTime_GridLayout->addWidget(sec_SpinBox,1,1,1,1);
	verifyTime_GridLayout->addWidget(msecs_Label,0,2,1,1);
	verifyTime_GridLayout->addWidget(msecs_SpinBox,1,2,1,1);
	verifyTime_GridLayout->addWidget(verify_PushButton,2,2,1,1);
	//verifyTime_GridLayout->addWidget();

	verifyTime_Widget->setWindowTitle(tr("����ʱ������"));
	verifyTime_Widget->setWindowIcon(QIcon(":/bg.png"));
	verifyTime_Widget->setFont(QFont(tr("����"), 16));
	verifyTime_Widget->show();
}
