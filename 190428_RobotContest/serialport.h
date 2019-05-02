#pragma once

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPort : public QObject
{
	Q_OBJECT

public:
	SerialPort(QObject *parent = nullptr);
	~SerialPort();
	const QStringList searchSerialPort();
	bool openSerialPort(uint8_t serialPortNameIndex);
	void closeSerialPort();
	bool isOpened();
	void sendData(QByteArray data);
	void setBaudRate(uint8_t baudRateIndex);
	void setDataBits(uint8_t dataBitsIndex);
	void setStopBits(uint8_t stopBitsIndex);
	void setParity(uint8_t parityIndex);
	void setFlowControl(uint8_t flowControlIndex);

signals:
	void serialPassData(QByteArray data);
public slots:
	void readAllDatas();
	
private:
	QSerialPort serial;
	QString serialPortName;
	static QStringList serialPortNames;
	bool isOpen;
};
