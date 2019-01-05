#include "HBool.h"
#include "HVoid.h"

HLang::HBool::HBool(bool __data__)
{
	data = __data__;
}

bool HLang::HBool::value() const
{
	return data;
}

HPointer HLang::HBool::set(HArgs args)
{
	this->data = args[0]->to<HBool>()->value();
	return HPointer(new HVoid);
}

HPointer HLang::HBool::init_bool(HArgs args)
{
	this->data = args[0]->to<HBool>()->value();
	return HPointer(new HVoid);
}