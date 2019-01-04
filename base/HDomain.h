#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HDomain :
	public HObject
{
	HLANG_OBJECT(HDomain);
	HLANG_INIT_START
		HLANG_IMPORT_FUNCTION(HDomain, init, HLANG_ARGSPILT("HDomain"), &HLang::HDomain::init_has_upper);
	HLANG_IMPORT_FUNCTION(HDomain, init, HLANG_ARGSPILT(""), &HLang::HDomain::init_has_not_upper);
	HLANG_INIT_END
public:
	HDomain(HDomain *upper = nullptr);
	HPointer init_has_upper(HArgs args);
	HPointer init_has_not_upper(HArgs args);
	bool New(std::string __save_As__, std::string __class__, HArgs args);
	bool Import(std::string __name__, HPointer __ptr__);
	void Delete(std::string __name__, bool __do_delete__ = true);
	HPointer Access(std::string __name__, bool __access_upper__ = true);
	bool RegisterClass(std::string __name__, HPointer(*__handle__)(HArgs));
	HPointer(*getRegisteredClass(std::string __name__))(HArgs);
private:
	std::map < std::string, HPointer(*)(HArgs)> registeredclasses;
	std::map<std::string, HPointer> classes;
	HDomain* upper;
};
HLANG_NAMESPACE_END