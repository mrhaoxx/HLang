#include "HByte.h"
#include "HInt.h"
#include "HVoid.h"
#include "HBool.h"

HLang::HByte::HByte(int i)
{
	this->data = (char)i;
}

HPointer HLang::HByte::toInt(HArgs args)
{
	return HPointer(new HInt((int)this->data));
}

HPointer HLang::HByte::set(HArgs args)
{
	this->data = (char)args[0]->to<HInt>()->value();
	return HPointer(new HVoid);
}

HPointer HLang::HByte::equals(HArgs args)
{
	return HPointer(new HBool(data == args[0]->to<HInt>()->value()));
}

HPointer HLang::HByte::init_int(HArgs args)
{
	this->data = (char)args[0]->to<HInt>()->value();
	return HPointer();
}

char HLang::HByte::value() const
{
	return data;
}