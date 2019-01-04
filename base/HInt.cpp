#include "HInt.h"
#include "HBool.h"
#include "HVoid.h"

HLang::HInt::HInt(int d)
{
	data = d;
}

HPointer HLang::HInt::equals(HArgs args)
{
	return HPointer(new HBool(data == args[0]->to<HInt>()->value()));
}

HPointer HLang::HInt::greater(HArgs args)
{
	return HPointer(new HBool(data > args[0]->to<HInt>()->value()));
}

HPointer HLang::HInt::less(HArgs args)
{
	return HPointer(new HBool(data < args[0]->to<HInt>()->value()));
}

int HLang::HInt::value()
{
	return data;
}

HPointer HLang::HInt::init_int(HArgs args)
{
	this->data = args[0]->to<HInt>()->data;
	return HPointer(new HVoid);
}

HPointer HLang::HInt::set(HArgs args)
{
	this->data = args[0]->to<HInt>()->data;
	return HPointer(new HVoid);
}