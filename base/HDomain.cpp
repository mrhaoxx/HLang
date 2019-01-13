#include "HDomain.h"
#include "HVoid.h"

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
	return HPointer(HVoid::__new__(HArgs()));
}

HPointer HLang::HDomain::init_has_not_upper(HArgs args)
{
	this->upper = nullptr;
	return HPointer(HVoid::__new__(HArgs()));
}

bool HLang::HDomain::RegisterClass(std::string package, std::string __name__, HFunctionAddress __handle__)
{
	if (registeredclasses.count(package) == 0)
	{
		registeredclasses[package][__name__] = __handle__;
		return true;
	}
	else return false;
}
HFunctionAddress HLang::HDomain::getRegisteredClass(std::string __name__) {
	for (std::map<std::string, std::map<std::string, HFunctionAddress>>::iterator it = registeredclasses.begin(); it != registeredclasses.end(); ++it)
		if (it->second.count(__name__) != 0)
			return it->second[__name__];
	if (upper == nullptr)
		return nullptr;
	else
		return upper->getRegisteredClass(__name__);
}

bool HLang::HDomain::LoadDll(std::string package)
{
	HDllLoader* dll = new HDllLoader(package);
	if (dll->load())
	{
		if (this->dlls.count(package) != 0)
			delete dlls[package];
		this->dlls[package] = dll;
		this->registeredclasses[package] = dll->get();
		return true;
	}
	else
		return false;
}

void HLang::HDomain::FreeDll(std::string package)
{
	this->registeredclasses[package].clear();
	this->registeredclasses.erase(package);
	if (dlls.count(package) != 0)
		delete this->dlls.at(package);
}

HLang::HDomain::~HDomain()
{
	clear(All);
}

void HLang::HDomain::clear(ClearType t /*= All*/)
{
	switch (t)
	{
	case HLang::HDomain::All:
	case HLang::HDomain::Classes:
		for (std::map<std::string, HPointer>::iterator it = classes.begin(); it != classes.end(); ++it)
			delete it->second;
		classes.clear();
		if (t != All)
			break;
	case HLang::HDomain::Dlls:
		for (std::map<std::string, HDllLoader*>::iterator it = dlls.begin(); it != dlls.end(); ++it)
			delete it->second;
		dlls.clear();
		break;
	default:
		break;
	}
}

HLang::HDomain* HLang::HDomain::setupper(HDomain *upper /*= nullptr*/)
{
	this->upper = upper;
	return this;
}

HPointer HLang::HDomain::Execute(std::string __class__, std::string __function__, HArgs args)
{
	return (this->Access(__class__)) ? this->Access(__class__)->__do__(__function__, args) : nullptr;
}