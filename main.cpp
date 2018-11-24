#include "HObject.h"
#include <QApplication>
#include <QMessageBox>
#include "HBuiltin.h"
#include <QDebug>
#include "Front/commandline.h"
HLang* HMain = new HLang;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	HMain->importclass("builtin", new HBuiltin);
	if (argc == 2)
	{
		HLangHelper::exec("f=new(\"function\")");
		HLangHelper::exec("f.loadfile(\"" + QString(argv[1]) + "\")");
		HLangHelper::exec("f.exec()");
	}
	else
	{
		commandline c;
		c.show();
	}
	return app.exec();
}