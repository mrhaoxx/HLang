#include "HDomain.h"
#include "HVoid.h"

HLang::HDomain::HDomain(HDomain *upper /*= nullptr*/)
{
	this->upper = upper;
}

bool HLang::HDomain::Import(std::string __name__, HPointer __ptr__)
{
	if (this->classes.count(__name__) != 0)
		return false;
	else
		this->classes[__name__] = __ptr__;
	return true;
}

void HLang::HDomain::Delete(std::string __name__, bool __do_delete__ /*= true*/)
{
	if (this->classes.count(__name__) != 0)
	{
		if (__do_delete__)
			delete classes[__name__];
		classes.erase(__name__);
	}
}

HPointer HLang::HDomain::Access(std::string __name__, bool __access_upper__ /*= true*/)
{
	if (this->classes.count(__name__) != 0)
		return classes[__name__];
	else
		if (__access_upper__)
			if (upper != nullptr)
				return upper->Access(__name__);
			else
				return nullptr;
		else
			return nullptr;
}
bool HLang::HDomain::New(std::string __save_As__, std::string __class__, HArgs args)
{
	if (this->getRegisteredClass(__class__) != nullptr)
		this->Import(__save_As__, this->getRegisteredClass(__class__)(args));
	else
		return false;
	return true;
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

bool HLang::HDomain::RegisterClass(std::string __name__, HPointer(*__handle__)(HArgs))
{
	if (registeredclasses.count(__name__) == 0)
	{
		registeredclasses[__name__] = __handle__;
		return true;
	}
	else return false;
}
HPointer(*HLang::HDomain::getRegisteredClass(std::string __name__))(HArgs) {
	if (registeredclasses.count(__name__) == 0)
		if (upper == nullptr)
			return nullptr;
		else
			return upper->getRegisteredClass(__name__);
	return registeredclasses[__name__];
}