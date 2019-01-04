#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HByte :
	public HLang::HObject
{
	HLANG_OBJECT(HByte);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HByte, toInt, HLANG_ARGSPILT(""), &HLang::HByte::toInt);
	HLANG_IMPORT_FUNCTION(HByte, equals, HLANG_ARGSPILT("HByte"), &HLang::HByte::equals);
	HLANG_IMPORT_FUNCTION(HByte, set, HLANG_ARGSPILT("HInt"), &HLang::HByte::set);
	HLANG_IMPORT_FUNCTION(HByte, init, HLANG_ARGSPILT("HInt"), &HLang::HByte::init_int);
	HLANG_INIT_END
public:
	HPointer toInt(HArgs args);
	HLANG_EXPORT HByte(int i = 0);
	HPointer set(HArgs args);
	HPointer equals(HArgs args);
	HPointer init_int(HArgs args);
	HLANG_EXPORT char value() const;
private:
	char data;
};
HLANG_NAMESPACE_END