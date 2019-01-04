#include "HDomain.h"
#include "HVoid.h"

HLang::HDomain::HDomain(HDomain *upper /*= nullptr*/)
{
	this->upper = upper;
}

bool HLang::HDomain::_import_(std::string __name__, HPointer __ptr__)
{
	if (this->classes.count(__name__) != 0)
		return false;
	else
		this->classes[__name__] = __ptr__;
	return true;
}

void HLang::HDomain::_delete_(std::string __name__, bool __do_delete__ /*= true*/)
{
	if (this->classes.count(__name__) != 0)
	{
		if (__do_delete__)
			delete classes[__name__];
		classes.erase(__name__);
	}
}

HPointer HLang::HDomain::_access_(std::string __name__, bool __access_upper__ /*= true*/)
{
	if (this->classes.count(__name__) != 0)
		return classes[__name__];
	else
		if (__access_upper__)
			if (upper != nullptr)
				return upper->_access_(__name__);
			else
				return nullptr;
		else
			return nullptr;
}

HPointer HLang::HDomain::init_has_upper(HArgs args)
{
	this->upper = args[0]->to<HDomain>();
	return HPointer(new HVoid);
}

HPointer HLang::HDomain::init_has_not_upper(HArgs args)
{
	this->upper = nullptr;
	return HPointer(new HVoid);
}