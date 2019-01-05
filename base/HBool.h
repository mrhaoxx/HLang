#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HBool :
	public HLang::HObject
{
	HLANG_OBJECT(HBool);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HBool, set, HLANG_ARGSPILT("HBool"), &HLang::HBool::set);
	HLANG_IMPORT_FUNCTION(HBool, init, HLANG_ARGSPILT("HBool"), &HLang::HBool::init_bool);
	HLANG_INIT_END;
public:
	HLANG_EXPORT HBool* setvalue(bool __data__ = false);
	HLANG_EXPORT bool value() const;
	HLANG_EXPORT HPointer set(HArgs args);
	HLANG_EXPORT HPointer init_bool(HArgs args);
private:
	bool data;
};
HLANG_NAMESPACE_END
