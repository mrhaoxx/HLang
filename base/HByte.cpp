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
	this->data = (wchar_t)args[0]->to<HInt>()->value();
	return HPointer(HVoid::__new__(HArgs()));
}

HPointer HLang::HByte::equals(HArgs args)
{
	return HPointer(HBool::__new__(HArgs())->to<HBool>()->setvalue(data == args[0]->to<HInt>()->value()));
}

HPointer HLang::HByte::init_int(HArgs args)
{
	this->data = (char)args[0]->to<HInt>()->value();
	return HPointer(HVoid::__new__(HArgs()));
}

wchar_t HLang::HByte::value() const
{
	return data;
}

HLang::HByte* HLang::HByte::setvalue(wchar_t c)
{
	this->data = c;
	return this;
}

HLang::HByte* HLang::HByte::setvalue(int i /*= 0*/)
{
	this->data = i;
	return this;
}