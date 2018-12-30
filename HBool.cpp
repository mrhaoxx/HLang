#include "HBool.h"
#include "HVoid.h"
HLang::HBool::HBool(HArgs args) {
	HLANG_CHECKARGS(1, <= );
	HLANG_IFARGS(1, == )
	{
		HLANG_CHECKARGTYPE(0, HBool);
		this->data = args[0]->to<HBool>()->value();
	}
}

HLang::HBool::HBool(bool __data__)
{
	data = __data__;
}

bool HLang::HBool::value()
{
	return data;
}

HPointer HLang::HBool::set(HArgs args)
{
	HLANG_CHECKARGS(1, == );
	HLANG_CHECKARGTYPE(0, HBool);
	this->data = args[0]->to<HBool>()->value();
	return HPointer(new HVoid);
}