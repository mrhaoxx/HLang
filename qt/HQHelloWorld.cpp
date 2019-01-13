#include "HQHelloWorld.h"
#include "HVoid.h"
#include "QMessageBox"
#include "HString.h"

HPointer HLang::HQHelloWorld::aboutQt(HArgs args)
{
	QApplication::aboutQt();
	return HVoid::__new__(HArgs());
}

HPointer HLang::HQHelloWorld::infobox(HArgs args)
{
	QMessageBox::information(nullptr, "test", QString::fromStdString(args[0]->to<HString>()->toStdString()), QMessageBox::Ok);
	return HVoid::__new__(HArgs());
}