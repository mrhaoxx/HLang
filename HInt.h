#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HInt :
	public HLang::HObject
{
	HLANG_OBJECT(HInt);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HInt, equals, &HLang::HInt::equals);
	HLANG_IMPORT_FUNCTION(HInt, greater, &HLang::HInt::greater);
	HLANG_IMPORT_FUNCTION(HInt, less, &HLang::HInt::less);
	HLANG_INIT_END
public:
	HInt(int d = 0);
	HPointer equals(HArgs args);
	HPointer greater(HArgs args);
	HPointer less(HArgs args);
	int value();
private:
	int data;
};
HLANG_NAMESPACE_END