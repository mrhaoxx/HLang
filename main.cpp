#include "HObject.h"
#include "commandline.h"
#include <QApplication>
#include <QMessageBox>
#include "HBuiltin.h"
#include <QDebug>
HLang* HMain = new HLang;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HMain->importclass("builtin", new HBuiltin);
	commandline *cui = new commandline;
	cui->show();
	//HLangHelper::exec("f=new(\"function\")");
	//HLangHelper::exec("f.loadfile(\"c:\\hl\\test\")");
	//HLangHelper::exec("f.exec()");
	return a.exec();
}