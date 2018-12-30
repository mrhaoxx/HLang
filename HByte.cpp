#include "HByte.h"
#include "HInt.h"
#include "HVoid.h"
#include "HBool.h"

HLang::HByte::HByte(HArgs args)
{
	HLANG_IFARGS(1, == )
		HLANG_IFARGTYPE(0, HInt)
		this->data = (char)args[0]->to<HInt>()->value();
}

HLang::HByte::HByte(int i)
{
	this->data = (char)i;
}

HPointer HLang::HByte::toInt(HArgs args)
{
	HLANG_CHECKARGS(0, == );
	return HPointer(new HInt((int)this->data));
}

HPointer HLang::HByte::fromInt(HArgs args)
{
	HLANG_CHECKARGS(1, == );
	HLANG_CHECKARGTYPE(0, HInt);
	this->data = (char)args[0]->to<HInt>()->value();
	return HPointer(new HVoid);
}

HPointer HLang::HByte::equals(HArgs args)
{
	HLANG_CHECKARGS(1, == );
	HLANG_CHECKARGTYPE(0, HByte);
	return HPointer(new HBool(data == args[0]->to<HInt>()->value()));
}
