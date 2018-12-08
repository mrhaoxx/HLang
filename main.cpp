#include <QApplication>
#include "HBuiltin.h"
#include <iostream>
#include <QDebug>
bool *iscolorful = new bool(true);
bool *isdebug = new bool(true);
bool *moremsg = new bool(false);
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	HLang* HMain = new HLang(nullptr);
	HMain->importclass("builtin", new HBuiltin(HMain));
	if (argc == 2) {
		qDebug() << "The Model isn't ready";
		return 0;
	}
	else
	{
		while (true)
		{
			std::string in;
			QString a;
			while (in != "run") {
				a.append(QString::fromStdString(in));
				std::cin >> in;
			}
			try {
				HCodes m(HMain);
				m.fromString(HArgs({ new HString(a) }));
				m.run(HArgs());
			}
			catch (HError &e) {
				HFunction::CoutMsg(e);
			}
		}
	}
	return app.exec();
}