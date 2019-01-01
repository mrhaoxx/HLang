#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HFunction :
	public HLang::HObject
{
	HLANG_OBJECT(HFunction);
	HLANG_INIT_START
		HLANG_INIT_END
public:
	HFunction();
	~HFunction();
};
HLANG_NAMESPACE_END