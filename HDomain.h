#pragma once
#include "HObject.h"
HLANG_NAMESPACE_START
class HDomain :
	public HObject
{
	HLANG_OBJECT(HDomain);
	HLANG_INIT_START HLANG_INIT_END
public:
	HDomain(HDomain *upper = nullptr);
	bool _import_(std::string __name__, HPointer __ptr__);
	void _delete_(std::string __name__, bool __do_delete__ = true);
	HPointer _access_(std::string __name__, bool __access_upper__ = true);

private:
	std::map<std::string, HPointer> classes;
	HDomain* upper;
};
HLANG_NAMESPACE_END