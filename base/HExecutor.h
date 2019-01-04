#pragma once
#include "HObject.h"
#include "HDomain.h"
#include "HInt.h"
#include "HBool.h"
#include "HByte.h"
#include "HVoid.h"
HLANG_NAMESPACE_START
std::map < std::string, HPointer(*)(HArgs)> registeredclasses({
			std::make_pair("int",&HLang::HInt::__new__),
			std::make_pair("bool",&HLang::HBool::__new__),
			std::make_pair("byte",&HLang::HByte::__new__),
			std::make_pair("void",&HLang::HVoid::__new__)
	});
class HExecutor :
	public HObject
{
	HLANG_OBJECT(HExecutor);
	HLANG_INIT_START HLANG_INIT_END
public:
	HExecutor(HDomain* def = new HDomain) : define(def) {};
	HPointer _run_(std::string __class__, std::string __function__, HArgs args);
	bool _new_(std::string __save_As__, std::string __class__, HArgs args);
	void _delete_(std::string __class__);
private:
	HDomain* define;
};
HLANG_NAMESPACE_END