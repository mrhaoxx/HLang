#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HExecutor :
	public HObject
{
	HLANG_OBJECT(HExecutor);
	HLANG_INIT_START HLANG_INIT_END
public:
	HPointer run(std::string __class__, std::string __function__, HArgs args);
};
HLANG_NAMESPACE_END