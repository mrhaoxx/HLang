#include "HObject.h"
#include <QApplication>
#include <QMessageBox>
#include "HBuiltin.h"
#include <QDebug>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	if (argc == 2)
	{
		HLang* HMain = new HLang(nullptr);
		HMain->importclass("builtin", new HBuiltin(HMain));
	}
	return app.exec();
}