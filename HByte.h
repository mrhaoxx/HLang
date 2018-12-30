#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HByte :
	public HLang::HObject
{
	HLANG_OBJECT(HByte);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HByte, toInt, &HLang::HByte::toInt);
	HLANG_INIT_END
public:
	HPointer toInt(HArgs args);
	HByte(int i =0 );
	HPointer fromInt(HArgs args);
	HPointer equals(HArgs args);
private:
	char data;
};
HLANG_NAMESPACE_END