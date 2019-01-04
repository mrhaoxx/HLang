#include "HExecutor.h"
#include "HInt.h"
#include "HBool.h"
#include "HByte.h"
#include "HVoid.h"

HPointer HLang::HExecutor::_run_(std::string __class__, std::string __function__, HArgs args)
{
	if (this->define->Access(__class__) != nullptr)
		return this->define->Access(__class__)->__do__(__function__, args);
	return nullptr;
}

void HLang::HExecutor::_delete_(std::string __class__)
{
	this->define->Delete(__class__);
}