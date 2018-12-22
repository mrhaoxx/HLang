#include <QApplication>
#include "HBuiltin.h"
#include <iostream>
#include <QDebug>
bool *iscolorful = new bool(true);
bool *isdebug = new bool(true);
bool *moremsg = new bool(true);
QString *indent = new QString("");
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	if (argc == 2) {
		qDebug() << "The Model isn't ready";
		return 0;
	}
	else
	{
		while (true)
		{
			std::string in;
			getline(std::cin, in);
			RT_DEBUG << "\033c";
			QString a;
			while (in != "run") {
				a.append(QString::fromStdString(in));
				getline(std::cin, in);
			}
			RT_DEBUG << "\033c" << YELLOWCOLOR << "Running" << ColorClear;
			HClass *m = new HClass;
			HPointer p(m);
			try {
				m->setupthis();
				m->fromString(HArgs({ HPointer(new HString(a)) })).clear();
				m->run(HArgs({ HPointer(new HString("main")) }));
			}
			catch (HError &e) {
				HFunction::CoutMsg(e);
			}
			p.clear();
			RT_DEBUG << YELLOWCOLOR << "End" << ColorClear;
		}
	}
	return app.exec();
}