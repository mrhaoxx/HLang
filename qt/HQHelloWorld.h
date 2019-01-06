#pragma once
#include "HObject.h"
#include <QApplication>
HLANG_NAMESPACE_START
class HQHelloWorld : HObject
{
	HLANG_OBJECT(HQHelloWorld);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HQHelloWorld, "aboutQt", HLANG_ARGSPILT(""), &HQHelloWorld::aboutQt);
	HLANG_INIT_END
public:
	HPointer aboutQt(HArgs args);
};
HLANG_NAMESPACE_END