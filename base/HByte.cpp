#include "HByte.h"
#include "HInt.h"
#include "HVoid.h"
#include "HBool.h"

HPointer HLang::HByte::toInt(HArgs args)
{
	return HPointer(HInt::__new__(HArgs())->to<HInt>()->setvalue(this->data));
}

HPointer HLang::HByte::set(HArgs args)
{
	this->data = (char)args[0]->to<HInt>()->value();
	return HPointer(new HVoid);
}

HPointer HLang::HByte::equals(HArgs args)
{
	return HPointer(HBool::__new__(HArgs())->to<HBool>()->setvalue(data == args[0]->to<HInt>()->value()));
}

HPointer HLang::HByte::init_int(HArgs args)
{
	this->data = (char)args[0]->to<HInt>()->value();
	return HPointer(new HVoid);
}

char HLang::HByte::value() const
{
	return data;
}

HLang::HByte* HLang::HByte::setvalue(char c)
{
	this->data = c;
	return this;
}

HLang::HByte* HLang::HByte::setvalue(int i /*= 0*/)
{
	this->data = i;
	return this;
}