#pragma once
#include "HVector.h"

HLANG_NAMESPACE_START
class HString :
	protected HLang::HVector
{
	HLANG_OBJECT(HString);
	HString();
	HLANG_INIT_START
		HLANG_INHERITS(HString, HVector);
	HLANG_INIT_END

public:
	HString(std::string str) : HVector("HByte") {}
	~HString();
	std::string toStdString();
};

HLANG_NAMESPACE_END