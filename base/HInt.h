#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HInt :
	public HLang::HObject
{
	HLANG_OBJECT(HInt);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HInt, equals, HLANG_ARGSPILT("HInt"), &HLang::HInt::equals);
	HLANG_IMPORT_FUNCTION(HInt, set, HLANG_ARGSPILT("HInt"), &HLang::HInt::set);
	HLANG_IMPORT_FUNCTION(HInt, greater, HLANG_ARGSPILT("HInt"), &HLang::HInt::greater);
	HLANG_IMPORT_FUNCTION(HInt, less, HLANG_ARGSPILT("HInt"), &HLang::HInt::less);
	HLANG_IMPORT_FUNCTION(HInt, hw, HLANG_ARGSPILT("HInt"), &HLang::HInt::hw);
	HLANG_IMPORT_FUNCTION(HInt, init, HLANG_ARGSPILT("HInt"), &HLang::HInt::init_int);
	HLANG_INIT_END
public:
	HLANG_EXPORT int value();
	HLANG_EXPORT HInt* setvalue(int i = 0);
	HPointer equals(HArgs args);
	HPointer greater(HArgs args);
	HPointer less(HArgs args);
	HPointer init_int(HArgs args);
	HPointer set(HArgs args);
	HPointer hw(HArgs args);
private:
	int data;
};
HLANG_NAMESPACE_END