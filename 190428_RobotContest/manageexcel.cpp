#include "manageexcel.h"

ManageExcel::ManageExcel()
{
	isOpen = false;
}

ManageExcel::~ManageExcel()
{
}

bool ManageExcel::openExcel(QString fileName)
{
	if (!fileName.isEmpty()) {
		isOpen = true;
		excel = new QAxObject(this);
		excel->setControl("Excel.Application");                  //连接Excel控件
		excel->dynamicCall("SetVisible(bool Visible", "true");   //不显示窗体
		excel->setProperty("DisplayAlerts", false);              //不显示任何警告信息

		work_books = excel->querySubObject("WorkBooks");         //获取工作簿集合
		work_books->dynamicCall("Open(const QString&)", fileName);
		work_book = excel->querySubObject("ActiveWorkBook");     //获取当前工作簿
		if (work_book) {
			work_sheets = work_book->querySubObject("WorkSheets"); //获取工作表集合
			work_sheet = work_sheets->querySubObject("Item(int)", 1);//获取工作表1(Sheet1)
			return true;
		}
		else {
			return false;
		}
	}
	else {
		isOpen = false;
		return false;
	}
}

bool ManageExcel::newExcel(QString fileName)
{
	QFile file(fileName);
	if(!file.exists()){
		isOpen = true;
		excel = new QAxObject(this);
		excel->setControl("Excel.Application");
		excel->dynamicCall("setVisible(bool Visible)", "true");
		excel->setProperty("DisplayAlerts", false);

		work_books = excel->querySubObject("WorkBooks");
		work_books->dynamicCall("Add");
		work_book = excel->querySubObject("ActiveWorkBook");
		work_book->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));
		if (work_book) {
			work_sheets = work_book->querySubObject("WorkSheets"); //获取工作表集合
			work_sheet = work_sheets->querySubObject("Item(int)", 1);//获取工作表1(Sheet1)
			//qDebug() << work_sheet->property("Name").toString();//Debug->获取当前工作表名称
			return true;
		}
		else {
			return false;
		}
	}
	else {
		isOpen = false;
		return false;
	}
}

void ManageExcel::closeExcel()
{
	if (isOpen) {
		work_book->dynamicCall("Save()");
		work_book->dynamicCall("Close(Boolean)", false);
		excel->dynamicCall("Quit(void)");
	}
}

const bool ManageExcel::isOpened()
{
	return isOpen;
}

QString ManageExcel::readCellValue(int row, int column)
{
	QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", row, column);
	QVariant cell_value = cell->dynamicCall("Value2()");
	return cell_value.toString();
}

QString ManageExcel::readCellValue(int row, QString column)
{
	QAxObject *cell = work_sheet->querySubObject("Range(QVariant,QVariant)", QString(column + tr("%1").arg(row)));
	QVariant cell_value = cell->dynamicCall("Value2()");
	return cell_value.toString();
}

void ManageExcel::writeCellValue(int row, int column, const QString value)
{
	QAxObject *cell = work_sheet->querySubObject("Cells(int, int)", row, column);
	cell->dynamicCall("SetValue(const QVariant&)", value);
}

void ManageExcel::writeCellValue(int row, QString column, const QString value)
{
	QAxObject *cell = work_sheet->querySubObject("Range(QVariant QVariant)", QString(column + tr("%1").arg(row)));
	cell->dynamicCall("SetValue(const QVariant&)", value);
}
