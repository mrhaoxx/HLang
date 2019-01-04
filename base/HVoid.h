#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HVoid :
	public HLang::HObject
{
	HLANG_OBJECT(HVoid);
	HLANG_INIT_START HLANG_INIT_END
public:
	HVoid();
};
HLANG_NAMESPACE_END