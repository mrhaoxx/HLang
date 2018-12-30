#include "HInt.h"
#include "HBool.h"
HLang::HInt::HInt(HArgs args) {
	HLANG_IFARGS(1, == )
		HLANG_IFARGTYPE(0, HInt)
		this->data = args[0]->to<HInt>()->data;
}

HLang::HInt::HInt(int d)
{
	data = d;
}

HPointer HLang::HInt::equals(HArgs args)
{
	HLANG_CHECKARGS(1, == );
	HLANG_CHECKARGTYPE(0, HInt);
	return HPointer(new HBool(data == args[0]->to<HInt>()->value()));
}

HPointer HLang::HInt::greater(HArgs args)
{
	HLANG_CHECKARGS(1, == );
	HLANG_CHECKARGTYPE(0, HInt);
	return HPointer(new HBool(data > args[0]->to<HInt>()->value()));
}

HPointer HLang::HInt::less(HArgs args)
{
	HLANG_CHECKARGS(1, == );
	HLANG_CHECKARGTYPE(0, HInt);
	return HPointer(new HBool(data < args[0]->to<HInt>()->value()));
}

int HLang::HInt::value()
{
	return data;
}