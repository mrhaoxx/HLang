#include "HQHelloWorld.h"
#include "HVoid.h"

HPointer HLang::HQHelloWorld::aboutQt(HArgs args)
{
	QApplication::aboutQt();
	return HVoid::__new__(HArgs());
}