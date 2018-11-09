#include "commandline.h"
#include "ui_commandline.h"
#include <QDebug>
#include "HBuiltin.h"
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

void commandline::on_lineEdit_returnPressed()
{
	HString _command = ui->lineEdit->text();
	if (_command == "reload_builtin")
		HMain->import("builtin", new HBuiltin);
	if (_command == "reload")
	{
		delete HMain;
		HMain = new HLang;
		HMain->import("builtin", new HBuiltin);
	}
	ui->textBrowser->setText(ui->textBrowser->document()->toPlainText() + _command);
	QStringList list = _command.split(" ");
	if (list.length() > 1)
	{
		QString _class = list.at(0);
		QString _func = list.at(1);
		HOBJECTS __self;
		QStringList _args = list.mid(2);
		HOBJECTS __args = HOBJECTS(_args);
		if ((HMain->accessclass(_class)) != nullptr)
		{
			ui->textBrowser->append(HMain->accessclass(_class)->exec(_func, __self, __args).toString());
			ui->textBrowser->append("");
		}
		else
			ui->textBrowser->append("Error");
	}
	ui->textBrowser->append(">>");
	ui->textBrowser->moveCursor(QTextCursor::End);
	ui->lineEdit->clear();
}