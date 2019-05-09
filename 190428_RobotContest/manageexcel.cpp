#include "manageexcel.h"

ManageExcel::ManageExcel()
{
	isOpen = false;
}

ManageExcel::~ManageExcel()
{
	delete work_sheet;
	delete work_sheets;
	delete work_book;
	delete work_books;
	delete excel;
}

bool ManageExcel::openExcel(const QString fileName)
{
	if (!fileName.isEmpty()) {
		delete excel;
		excel = new QAxObject(this);
		excel->setControl("Excel.Application");                  //����Excel�ؼ�
		excel->dynamicCall("SetVisible(bool Visible", "false");   //����ʾ����
		excel->setProperty("DisplayAlerts", false);              //����ʾ�κξ�����Ϣ

		delete work_books;
		delete work_book;
		work_books = excel->querySubObject("WorkBooks");         //��ȡ����������
		work_books->dynamicCall("Open(const QString&)", fileName);
		work_book = excel->querySubObject("ActiveWorkBook");     //��ȡ��ǰ������
		if (work_book) {
			delete work_sheets;
			delete work_sheet;
			work_sheets = work_book->querySubObject("WorkSheets"); //��ȡ��������
			work_sheet = work_sheets->querySubObject("Item(int)", 1);//��ȡ������1(Sheet1)
			isOpen = true;
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

bool ManageExcel::newExcel(const QString fileName)
{
	QFile file(fileName);
	if(!file.exists()){
		delete excel;
		excel = new QAxObject(this);
		excel->setControl("Excel.Application");
		excel->dynamicCall("setVisible(bool Visible)", "false");
		excel->setProperty("DisplayAlerts", false);

		delete work_books;
		delete work_book;
		work_books = excel->querySubObject("WorkBooks");
		work_books->dynamicCall("Add");
		work_book = excel->querySubObject("ActiveWorkBook");
		work_book->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));
		if (work_book) {
			delete work_sheets;
			delete work_sheet;
			work_sheets = work_book->querySubObject("WorkSheets"); 
			work_sheet = work_sheets->querySubObject("Item(int)", 1);
			//qDebug() << work_sheet->property("Name").toString();//Debug->��ȡ��ǰ����������
			isOpen = true;
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

void ManageExcel::saveExcel()
{
	if (isOpen) {
		work_book->dynamicCall("Save()");
	}
}

const bool ManageExcel::isOpened()
{
	return isOpen;
}

const QString ManageExcel::readCellValue(int row, int column) 
{
	QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", row, column);
	QVariant cell_value = cell->dynamicCall("Value2()");
	return cell_value.toString();
}

const QString ManageExcel::readCellValue(int row, QString column)
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
