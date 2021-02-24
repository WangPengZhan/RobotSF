#pragma execution_character_set("utf-8")

#include "voicedeal.h"

VoiceDeal::VoiceDeal(QWidget *parent)
	: QWidget(parent)
{
	designUI();
	signalsAndSlots();
	init();
}

VoiceDeal::~VoiceDeal()
{
}

void VoiceDeal::speak()
{
	speech->say(voiceText_PlainTextEdit->toPlainText());
}

void VoiceDeal::speak(QString& voiceText)
{
	speech->say(voiceText);
}

void VoiceDeal::stop()
{
	speech->stop();
}

void VoiceDeal::setRate(int rate)
{
	speech->setRate(rate);
}

void VoiceDeal::setPitch(int pitch)
{
	speech->setPitch(pitch);
}

void VoiceDeal::setVolume(int volume)
{
	speech->setVolume(volume);
}

void VoiceDeal::on_speech_PushButton_clicked()
{
	speak();
}

void VoiceDeal::on_TextToSpeech_stateChanged(QTextToSpeech::State state)
{
	if (state == QTextToSpeech::Speaking) {
		statusBar->showMessage("Speech started...");
	}
	else if (state == QTextToSpeech::Ready)
		statusBar->showMessage("Speech stopped...", 2000);
	else if (state == QTextToSpeech::Paused)
		statusBar->showMessage("Speech paused...");
	else
		statusBar->showMessage("Speech error!");
}

void VoiceDeal::on_engine_ComboBox_currentIndexChanged(int index)
{
	QString engineName = engine_ComboBox->currentText();
	delete speech;
	if (engineName == "default") {
		speech = new QTextToSpeech(this);
	}
	else
		speech = new QTextToSpeech(engineName, this);

	disconnect(language_ComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&VoiceDeal::on_language_ComboBox_currentIndexChanged);
	language_ComboBox->clear();

	QVector<QLocale> locales = speech->availableLocales();
	QLocale current = speech->locale();
	foreach(const QLocale &locale, locales) {
		QString name(QString("%1 (%2)")
			.arg(QLocale::languageToString(locale.language()))
			.arg(QLocale::countryToString(locale.country())));
		QVariant localeVariant(locale);
		language_ComboBox->addItem(name, localeVariant);
		if (locale.name() == current.name())
			current = locale;
	}
	setRate(rate_Slider->value());
	setPitch(pitch_Slider->value());
	setVolume(volume_Slider->value());
	connect(stop_PushButton, &QPushButton::clicked, speech, &QTextToSpeech::stop);
	connect(pause_PushButton, &QPushButton::clicked, speech, &QTextToSpeech::pause);
	connect(resume_PushButton, &QPushButton::clicked, speech, &QTextToSpeech::resume);

	connect(speech, &QTextToSpeech::stateChanged, this, &VoiceDeal::on_TextToSpeech_stateChanged);
	connect(speech, &QTextToSpeech::localeChanged, this, &VoiceDeal::on_TextToSpeech_localeChanged);

	connect(language_ComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&VoiceDeal::on_language_ComboBox_currentIndexChanged);
	//on_TextToSpeech_stateChanged();
}

void VoiceDeal::on_language_ComboBox_currentIndexChanged(int language)
{
	QLocale locale = language_ComboBox->itemData(language).toLocale();
	speech->setLocale(locale);
}

void VoiceDeal::on_voice_ComboBox_currentIndexChanged(int index)
{
	speech->setVoice(voices.at(index));
}

void VoiceDeal::on_startRecord_PushButton_clicked()
{
	if (startRecord_PushButton->text() == tr("开始录音")) {
		ioputFile.open(QIODevice::WriteOnly);
		audio_Input->start(&ioputFile);
		startRecord_PushButton->setText(tr("停止录音"));
	}
	else {
		audio_Input->stop();
		ioputFile.close();
		startRecord_PushButton->setText(tr("开始录音"));
	}
}

void VoiceDeal::on_play_PushButton_clicked()
{
	ioputFile.open(QIODevice::ReadOnly);
	audio_Output->start(&ioputFile);
}

void VoiceDeal::on_Audio_stateChange(QAudio::State state)
{
	if (state == QAudio::IdleState) {
		audio_Output->stop();
		ioputFile.close();
	}
}

void VoiceDeal::on_TextToSpeech_localeChanged(const QLocale & locale)
{
	QVariant localeVariant(locale);
	language_ComboBox->setCurrentIndex(language_ComboBox->findData(localeVariant));

	disconnect(voice_ComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&VoiceDeal::on_voice_ComboBox_currentIndexChanged);
	voice_ComboBox->clear();

	voices = speech->availableVoices();
	QVoice currentVoice = speech->voice();
	foreach(const QVoice &voice, voices) {
		voice_ComboBox->addItem(QString("%1 - %2 - %3").arg(voice.name())
			.arg(QVoice::genderName(voice.gender()))
			.arg(QVoice::ageName(voice.age())));
		if (voice.name() == currentVoice.name())
			voice_ComboBox->setCurrentIndex(voice_ComboBox->count() - 1);
	}
	connect(voice_ComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&VoiceDeal::on_voice_ComboBox_currentIndexChanged);
}


void VoiceDeal::designUI()
{
	setWindowTitle(tr("语音设置界面"));
	setWindowIcon(QIcon(":/hh.png"));
	setFont(QFont("楷体", 16));

	voiceText_PlainTextEdit = new QPlainTextEdit(this);
	volume_Label = new QLabel(tr("音量"), this);
	volume_Label->setAlignment(Qt::AlignCenter);
	volume_Slider = new QSlider(this);
	volume_Slider->setOrientation(Qt::Horizontal);
	rate_Label = new QLabel(tr("语速"), this);
	rate_Label->setAlignment(Qt::AlignCenter);
	rate_Slider = new QSlider(this);
	rate_Slider->setOrientation(Qt::Horizontal);
	pitch_Label = new QLabel(tr("音调"), this);
	pitch_Label->setAlignment(Qt::AlignCenter);
	pitch_Slider = new QSlider(this);
	pitch_Slider ->setOrientation(Qt::Horizontal);

	engine_Label = new QLabel(tr("设施"), this);
	engine_Label->setAlignment(Qt::AlignCenter);
	engine_ComboBox = new QComboBox(this);
	language_Label = new QLabel(tr("语言"), this);
	language_Label->setAlignment(Qt::AlignCenter);
	language_ComboBox = new QComboBox(this);
	voice_Label = new QLabel(tr("语言来源"), this);
	voice_Label->setAlignment(Qt::AlignCenter);
	voice_Label->setAlignment(Qt::AlignCenter);
	voice_ComboBox = new QComboBox(this);

	speak_PushButton = new QPushButton(tr("播放"), this);
	pause_PushButton = new QPushButton(tr("暂停"), this);
	resume_PushButton = new QPushButton(tr("重新开始"), this);
	stop_PushButton = new QPushButton(tr("停止并退出"), this);
	statusBar = new QStatusBar(this);

	startRecord_PushButton = new QPushButton(tr("开始录音"), this);
	play_PushButton = new QPushButton(tr("播放录音文件"), this);
	

	main_GridLayout = new QGridLayout(this);
	main_GridLayout->addWidget(voiceText_PlainTextEdit,0,0,1,4);
	main_GridLayout->addWidget(volume_Label,1,0,1,1);
	main_GridLayout->addWidget(volume_Slider,1,1,1,3);
	main_GridLayout->addWidget(rate_Label,2,0,1,1);
	main_GridLayout->addWidget(rate_Slider,2,1,1,3);
	main_GridLayout->addWidget(pitch_Label,3,0,1,1);
	main_GridLayout->addWidget(pitch_Slider,3,1,1,3);
	main_GridLayout->addWidget(engine_Label,4,0,1,1);
	main_GridLayout->addWidget(engine_ComboBox,4,1,1,3);
	main_GridLayout->addWidget(language_Label,5,0,1,1);
	main_GridLayout->addWidget(language_ComboBox,5,1,1,3);
	main_GridLayout->addWidget(voice_Label,6,0,1,1);
	main_GridLayout->addWidget(voice_ComboBox,6,1,1,3);
	main_GridLayout->addWidget(speak_PushButton,7,0,1,1);
	main_GridLayout->addWidget(pause_PushButton,7,1,1,1);
	main_GridLayout->addWidget(resume_PushButton,7,2,1,1);
	main_GridLayout->addWidget(stop_PushButton,7,3,1,1);
	main_GridLayout->addWidget(statusBar,8,0,1,4);
	main_GridLayout->addWidget(startRecord_PushButton,9,0,1,1);
	main_GridLayout->addWidget(play_PushButton,9,1,1,1);
	show();
}

void VoiceDeal::signalsAndSlots()
{
	connect(speak_PushButton, &QPushButton::clicked, this, &VoiceDeal::on_speech_PushButton_clicked);
	connect(pitch_Slider, &QSlider::valueChanged, this, &VoiceDeal::setPitch);
	connect(rate_Slider, &QSlider::valueChanged, this, &VoiceDeal::setRate);
	connect(volume_Slider, &QSlider::valueChanged, this, &VoiceDeal::setVolume);
	connect(engine_ComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&VoiceDeal::on_engine_ComboBox_currentIndexChanged);
	connect(engine_ComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
		&VoiceDeal::on_engine_ComboBox_currentIndexChanged);
	//connect(audio_Output, &QAudioOutput::stateChanged, this, &VoiceDeal::on_Audio_stateChange);
	connect(startRecord_PushButton, &QPushButton::clicked, this, &VoiceDeal::on_startRecord_PushButton_clicked);
	connect(play_PushButton, &QPushButton::clicked, this, &VoiceDeal::on_play_PushButton_clicked);

}

void VoiceDeal::init()
{
	QLoggingCategory::setFilterRules(QStringLiteral("qt.speech.tts=true \n qt.speech.tts.*=true"));
	engine_ComboBox->addItem("default");
	foreach(QString engine, QTextToSpeech::availableEngines())
		engine_ComboBox->addItem(engine);
	engine_ComboBox->setCurrentIndex(0);
	on_engine_ComboBox_currentIndexChanged(0);

	audio_Format = new QAudioFormat();
	audio_Format->setChannelCount(1);
	audio_Format->setCodec("audio/pcm");
	audio_Format->setSampleRate(8000);
	audio_Format->setByteOrder(QAudioFormat::LittleEndian);
	audio_Format->setSampleType(QAudioFormat::UnSignedInt);
	audio_Info = QAudioDeviceInfo::defaultInputDevice();
	if (!audio_Info.isFormatSupported(*audio_Format)) {
		*audio_Format = audio_Info.nearestFormat(*audio_Format);
	}
	audio_Input = new QAudioInput(*audio_Format, this);
	audio_Output = new QAudioOutput(*audio_Format, this);
}