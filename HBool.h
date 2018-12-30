#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HBool :
	public HLang::HObject
{
	HLANG_OBJECT(HBool);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HBool, set, &HLang::HBool::set);
	HLANG_INIT_END;
public:
	HBool(bool __data__ = false);
	bool value();
	HPointer set(HArgs args);
private:
	bool data;
};
HLANG_NAMESPACE_END
