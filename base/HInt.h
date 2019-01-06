#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HInt :
	public HLang::HObject
{
	HLANG_OBJECT(HInt);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HInt, "equals", HLANG_ARGSPILT("HInt"), &HLang::HInt::equals);
	HLANG_IMPORT_FUNCTION(HInt, "set", HLANG_ARGSPILT("HInt"), &HLang::HInt::set);
	HLANG_IMPORT_FUNCTION(HInt, "greater", HLANG_ARGSPILT("HInt"), &HLang::HInt::greater);
	HLANG_IMPORT_FUNCTION(HInt, "less", HLANG_ARGSPILT("HInt"), &HLang::HInt::less);
	HLANG_IMPORT_FUNCTION(HInt, "init", HLANG_ARGSPILT("HInt"), &HLang::HInt::init_int);
	HLANG_INIT_END
public:
	HLANG_EXPORT int value();
	HLANG_EXPORT HInt* setvalue(int i = 0);
	HLANG_EXPORT HPointer equals(HArgs args);
	HLANG_EXPORT HPointer greater(HArgs args);
	HLANG_EXPORT HPointer less(HArgs args);
	HLANG_EXPORT HPointer init_int(HArgs args);
	HLANG_EXPORT HPointer set(HArgs args);
private:
	int data;
};
HLANG_NAMESPACE_END