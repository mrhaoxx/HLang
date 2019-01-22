#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class  HByte :
	public HLang::HObject
{
	HLANG_OBJECT(HByte);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HByte, "toInt", HLANG_ARGSPILT(""), &HLang::HByte::toInt);
	HLANG_IMPORT_FUNCTION(HByte, "equals", HLANG_ARGSPILT("HByte"), &HLang::HByte::equals);
	HLANG_IMPORT_FUNCTION(HByte, "set", HLANG_ARGSPILT("HInt"), &HLang::HByte::set);
	HLANG_IMPORT_FUNCTION(HByte, "init", HLANG_ARGSPILT("HInt"), &HLang::HByte::init_int);
	HLANG_INIT_END
public:
	HLANG_EXPORT HByte* setvalue(int i = 0);
	HLANG_EXPORT HByte* setvalue(wchar_t c = 0);
	HLANG_EXPORT wchar_t value() const;
	HLANG_EXPORT HPointer toInt(HArgs args);
	HLANG_EXPORT HPointer set(HArgs args);
	HLANG_EXPORT HPointer equals(HArgs args);
	HLANG_EXPORT HPointer init_int(HArgs args);
private:
	wchar_t data;
};
HLANG_NAMESPACE_END