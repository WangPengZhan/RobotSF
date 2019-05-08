#pragma once

#include <QObject>
#include <QAxObject>
#include <QDebug>
#include <QFile>
#include <QDir>

class ManageExcel : public QObject
{
	Q_OBJECT

public:
	ManageExcel();
	~ManageExcel();
	bool openExcel(const QString fileName);
	bool newExcel(const QString fileName);
	void closeExcel();
	void saveExcel();
	const bool isOpened();
	const QString readCellValue(int row, int column);
	const QString readCellValue(int row, QString column);
	void writeCellValue(int row, int column, const QString value);
	void writeCellValue(int row, QString colunm, const QString value);

private:
	QAxObject *excel = nullptr;
	QAxObject *work_books = nullptr;
	QAxObject *work_book = nullptr;
	QAxObject *work_sheets = nullptr;
	QAxObject *work_sheet = nullptr;
	bool isOpen;
};
