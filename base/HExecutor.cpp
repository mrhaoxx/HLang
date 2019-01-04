#include "HExecutor.h"

HPointer HLang::HExecutor::_run_(std::string __class__, std::string __function__, HArgs args)
{
	if (this->define->_access_(__class__) != nullptr)
		return this->define->_access_(__class__)->__do__(__function__, args);
	return nullptr;
}

void HLang::HExecutor::_delete_(std::string __class__)
{
	this->define->_delete_(__class__);
}

bool HLang::HExecutor::_new_(std::string __save_As__, std::string __class__, HArgs args)
{
	if (registeredclasses.count(__class__) != 0)
		this->define->_import_(__save_As__, registeredclasses[__class__](args));
	else
		return false;
	return true;
}