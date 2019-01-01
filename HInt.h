#pragma once
#include "HObject.h"
#error SomeMoreFunction: set
HLANG_NAMESPACE_START
class HInt :
	public HLang::HObject
{
	HLANG_OBJECT(HInt);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HInt, equals, HLANG_ARGSPILT("HInt"), &HLang::HInt::equals);
	HLANG_IMPORT_FUNCTION(HInt, greater, HLANG_ARGSPILT("HInt"), &HLang::HInt::greater);
	HLANG_IMPORT_FUNCTION(HInt, less, HLANG_ARGSPILT("HInt"), &HLang::HInt::less);
	HLANG_IMPORT_FUNCTION(HInt, init, HLANG_ARGSPILT("HInt"), &HLang::HInt::init_int);
	HLANG_INIT_END
public:
	HInt(int d = 0);
	HPointer equals(HArgs args);
	HPointer greater(HArgs args);
	HPointer less(HArgs args);
	HPointer init_int(HArgs args);
	int value();
private:
	int data;
};
HLANG_NAMESPACE_END