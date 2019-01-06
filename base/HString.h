#pragma once
#include "HVector.h"
HLANG_NAMESPACE_START
class HString :
	public HVector
{
	HLANG_OBJECT(HString);
	HLANG_INIT_START
		HLANG_INHERITS(HString, HVector);
	HLANG_INIT_END

public:
	HLANG_EXPORT HString(std::string str = "");
	HLANG_EXPORT std::string toStdString();
	HLANG_EXPORT HString* setvalue(std::string str);
};

HLANG_NAMESPACE_END