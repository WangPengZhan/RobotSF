#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTextToSpeech>
#include <QLoggingCategory>
#include <QSlider>
#include <QGridLayout>
#include <QStatusBar>
#include <QAudioInput>
#include <QAudioOutput>
#include <iostream>

class VoiceDeal : public QWidget
{
	Q_OBJECT

public:
	VoiceDeal(QWidget *parent = nullptr);
	~VoiceDeal();
	void speak();
	void speak(QString voiceText);
	void stop();
	void setRate(int rate);
	void setPitch(int pitch);
	void setVolume(int volume);
	
	

public slots:
	void on_speech_PushButton_clicked();
	void on_TextToSpeech_stateChanged(QTextToSpeech::State state);
	void on_engine_ComboBox_currentIndexChanged(int index);
	void on_language_ComboBox_currentIndexChanged(int language);
	void on_voice_ComboBox_currentIndexChanged(int index);
	void on_TextToSpeech_localeChanged(const QLocale &locale);
	void on_startRecord_PushButton_clicked();
	void on_play_PushButton_clicked();
	void on_Audio_stateChange(QAudio::State state);
private:
	void designUI();
	void signalsAndSlots();
	void init();

private:
	QFile ioputFile;
	QAudioInput *audio_Input;
	QAudioOutput *audio_Output;
	QAudioFormat *audio_Format;
	QAudioDeviceInfo audio_Info;

	QPushButton *startRecord_PushButton;
	QPushButton *play_PushButton;

	QTextToSpeech *speech = nullptr;
	QVector<QVoice> voices;

	QPlainTextEdit *voiceText_PlainTextEdit;
	QLabel *volume_Label;
	QSlider *volume_Slider;
	QLabel *rate_Label;
	QSlider *rate_Slider;
	QLabel *pitch_Label;
	QSlider *pitch_Slider;
	QLabel *engine_Label;
	QComboBox *engine_ComboBox;
	QLabel *language_Label;
	QComboBox *language_ComboBox;
	QLabel *voice_Label;
	QComboBox *voice_ComboBox;
	QPushButton *speak_PushButton;
	QPushButton *pause_PushButton;
	QPushButton *resume_PushButton;
	QPushButton *stop_PushButton;
	QStatusBar *statusBar;

	QGridLayout *main_GridLayout;

};
