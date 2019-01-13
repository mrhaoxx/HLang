#pragma once
#include "HObject.h"
#include "QApplication"
HLANG_NAMESPACE_START
class HQHelloWorld : HObject
{
	HLANG_OBJECT(HQHelloWorld);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HQHelloWorld, "aboutQt", HLANG_ARGSPILT(""), &HQHelloWorld::aboutQt);
	HLANG_IMPORT_FUNCTION(HQHelloWorld, "info", HLANG_ARGSPILT("HString"), &HQHelloWorld::infobox);
	HLANG_INIT_END
public:
	HPointer aboutQt(HArgs args);
	HPointer infobox(HArgs args);
};
HLANG_NAMESPACE_END