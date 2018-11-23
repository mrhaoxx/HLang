#include "commandline.h"
#include "ui_commandline.h"
#include <QDebug>
#include "HBuiltin.h"
#include <functional>
commandline::commandline(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::commandline)
{
	ui->setupUi(this);
}

commandline::~commandline()
{
	delete ui;
}

void commandline::add(QString str)
{
	ui->textBrowser->append(str);
}

void commandline::on_lineEdit_returnPressed()
{
	QString _command = ui->lineEdit->text();
	if (_command == "reload_builtin")
		HMain->importclass("builtin", new HBuiltin);
	if (_command == "reload")
	{
		delete HMain;
		HMain = new HLang;
		HMain->importclass("builtin", new HBuiltin);
	}
	ui->textBrowser->setText(ui->textBrowser->document()->toPlainText() + _command);
	HLangHelper::exec(_command, HMain, this);
	ui->textBrowser->append(">>");
	ui->textBrowser->moveCursor(QTextCursor::End);
	ui->lineEdit->clear();
}