#include "serialport.h"

#pragma execution_character_set("utf-8")

QStringList SerialPort::serialPortNames = {};

SerialPort::SerialPort(QObject *parent)
	: QObject(parent)
{

}

SerialPort::~SerialPort()
{
}

bool SerialPort::openSerialPort(uint8_t serialPortNameIndex)
{
	/*serialPortName = serialPortNames.at(serialPortNameIndex);
	serial.setPortName(serialPortName);
	if (!serial.open(QIODevice::ReadWrite)) {
		serial.close();
		if (!serial.open(QIODevice::ReadWrite)) {
			isOpen = false;
		}
		else {
			isOpen = true;
			connect(&serial, SIGNAL(readyRead()), this, SLOT(readAllDatas()));
		}
	}
	else {
		isOpen = true;
	}

	return isOpen;*/
	serialPortName = serialPortNames.at(serialPortNameIndex);
	serial.setPortName(serialPortName);//设置串口号 
	isOpen = serial.open(QIODevice::ReadWrite);//打开串口
	if (isOpen)
	{
		connect(&serial, SIGNAL(readyRead()), this, SLOT(readAllDatas()));
	}
	else serial.close();
	return isOpen;
}

void SerialPort::closeSerialPort()
{
	serial.close();
}

bool SerialPort::isOpened()
{
	return isOpen;
}

void SerialPort::sendData(QByteArray data)
{
	serial.write(data);
}

void SerialPort::setBaudRate(uint8_t baudRateIndex)
{
	switch (baudRateIndex)
	{
	case 0:
		serial.setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
		break;
	case 1:
		serial.setBaudRate(QSerialPort::Baud57600, QSerialPort::AllDirections);
		break;
	case 2:
		serial.setBaudRate(QSerialPort::Baud38400, QSerialPort::AllDirections);
		break;
	case 3:
		serial.setBaudRate(QSerialPort::Baud19200, QSerialPort::AllDirections);
		break;
	case 4:
		serial.setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
		break;
	case 5:
		serial.setBaudRate(QSerialPort::Baud4800, QSerialPort::AllDirections);
		break;
	default:
		break;
	}
}

void SerialPort::setDataBits(uint8_t dataBitsIndex)
{
	switch (dataBitsIndex)
	{
	case 0:
		serial.setDataBits(QSerialPort::Data8);
		break;
	case 1:
		serial.setDataBits(QSerialPort::Data7);
		break;
	case 2:
		serial.setDataBits(QSerialPort::Data6);
		break;
	case 3:
		serial.setDataBits(QSerialPort::Data5);
		break;
	default:
		break;
	}
}

void SerialPort::setStopBits(uint8_t stopBitsIndex)
{
	switch (stopBitsIndex)
	{
	case 0:
		serial.setStopBits(QSerialPort::OneStop);
		break;
	case 1:
		serial.setStopBits(QSerialPort::OneAndHalfStop);
		break;
	case 2:
		serial.setStopBits(QSerialPort::TwoStop);
		break;
	default:
		break;
	}
}

void SerialPort::setParity(uint8_t parityIndex)
{
	switch (parityIndex)
	{
	case 0:
		serial.setParity(QSerialPort::NoParity);
		break;
	case 1:
		serial.setParity(QSerialPort::OddParity);
		break;
	case 2:
		serial.setParity(QSerialPort::EvenParity);
		break;
	default:
		break;
	}
}

void SerialPort::setFlowControl(uint8_t flowControlIndex)
{
	switch (flowControlIndex)
	{
	case 0:
		serial.setFlowControl(QSerialPort::NoFlowControl);
		break;
	case 1:
		serial.setFlowControl(QSerialPort::HardwareControl);
		break;
	case 2:
		serial.setFlowControl(QSerialPort::SoftwareControl);
		break;
	default:
		break;
	}
}

const QStringList SerialPort::searchSerialPort() 
{
	serialPortNames.clear();
	foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		serialPortNames << info.portName();
	}
	if (serialPortNames.isEmpty()) {
		serialPortNames.append(tr("没有串口，请重新连接串口！"));
	}
	return serialPortNames;
}

void SerialPort::readAllDatas() 
{
	QByteArray data;
	data = serial.readAll();
	if (!data.isEmpty()) {
		emit serialPassData(data);
	}
}
