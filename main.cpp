#include "HObject.h"
#include <QApplication>
#include <QMessageBox>
#include "HBuiltin.h"
#include <QDebug>
#include "Front/commandline.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	commandline *c;
	if (argc == 2)
	{
		HLang* HMain = new HLang(nullptr);
		HMain->importclass("builtin", new HBuiltin(HMain));
		QApplication::setQuitOnLastWindowClosed(false);
		HLangHelper::exec("f=new(\"function\")", HMain);
		HLangHelper::exec("f.loadfile(\"" + QString(argv[1]) + "\")", HMain);
		HLangHelper::exec("f.exec()", HMain);
	}
	else
	{
		c = new commandline;
		c->show();
	}
	return app.exec();
}