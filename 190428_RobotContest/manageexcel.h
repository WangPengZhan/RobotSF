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
	bool openExcel(QString fileName);
	bool newExcel(QString fileName);
	void closeExcel();
	const bool isOpened();
	QString readCellValue(int row, int column);
	QString readCellValue(int row, QString column);
	void writeCellValue(int row, int column, const QString value);
	void writeCellValue(int row, QString colunm, const QString value);

private:
	QAxObject *excel;
	QAxObject *work_books;
	QAxObject *work_book;
	QAxObject *work_sheets;
	QAxObject *work_sheet;
	bool isOpen;


};
