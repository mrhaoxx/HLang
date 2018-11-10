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
	QStringList backvaluelist = _command.split("=");
	QStringList list;
	if (backvaluelist.length() == 1)
		list = backvaluelist.at(0).split(" ");
	else
		list = backvaluelist.at(1).split(" ");
	if (list.length() > 1)
	{
		QString _class = list.at(0);
		QString _func = list.at(1);
		HOBJECTS __self;
		QStringList _args = list.mid(2);
		HOBJECTS __args = HOBJECTS(_args);
		if ((HMain->accessclass(_class)) != nullptr)
		{
			if (backvaluelist.length() < 2)
				HMain->accessclass(_class)->exec(_func, __self, __args);
			else
			{
				HMain->importclass(backvaluelist.at(0), HMain->accessclass(_class)->exec(_func, __self, __args));
				ui->textBrowser->append("to " + backvaluelist.at(0));
			}
			ui->textBrowser->append("");
		}
		else
			ui->textBrowser->append("Error");
	}
	ui->textBrowser->append(">>");
	ui->textBrowser->moveCursor(QTextCursor::End);
	ui->lineEdit->clear();
}