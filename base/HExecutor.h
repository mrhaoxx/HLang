#pragma once
#include "HObject.h"
#include "HDomain.h"
#include <map>
HLANG_NAMESPACE_START

class HExecutor :
	public HObject
{
	HLANG_OBJECT(HExecutor);
	HLANG_INIT_START HLANG_INIT_END
public:
	HExecutor(HDomain* def = new HDomain) : define(def) {};
	HPointer _run_(std::string __class__, std::string __function__, HArgs args);
	void _delete_(std::string __class__);
private:
	HDomain* define;
};
HLANG_NAMESPACE_END