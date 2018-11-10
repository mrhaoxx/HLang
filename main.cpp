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
	commandline c;
	c.show();
	return a.exec();
}