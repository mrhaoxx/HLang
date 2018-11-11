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
	HCommand *c = HLangHelper::processcommand(ui->lineEdit->text());
	if (c->_self == nullptr)
		c->_self = new QString();
	if (c->_class == nullptr)
		c->_class = new QString();
	if (c->_func == nullptr)
		c->_func = new QString();
	if (c->_args == nullptr)
		c->_args = new QStringList();
	if ((HMain->accessclass(*(c->_class))) != nullptr)
	{
		if (c->_backvalue_name == nullptr)
			HMain->accessclass(*(c->_class))->exec(*(c->_func), *(c->_self), *(c->_args));
		else
		{
			HMain->importclass(*(c->_backvalue_name), HMain->accessclass(*(c->_class))->exec(*(c->_func), *(c->_self), *(c->_args)));
		}
	}
	else
		ui->textBrowser->append("Error");
	ui->textBrowser->append(">>");
	ui->textBrowser->moveCursor(QTextCursor::End);
	ui->lineEdit->clear();
}