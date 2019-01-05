#include "HInt.h"
#include "HBool.h"
#include "HVoid.h"
#include <iostream>

HPointer HLang::HInt::equals(HArgs args)
{
	return HPointer(HBool::__new__(HArgs())->to<HInt>()->setvalue(data == args[0]->to<HInt>()->value()));
}

HPointer HLang::HInt::greater(HArgs args)
{
	return HPointer(HBool::__new__(HArgs())->to<HBool>()->setvalue(data > args[0]->to<HInt>()->value()));
}

HPointer HLang::HInt::less(HArgs args)
{
	return HPointer(HBool::__new__(HArgs())->to<HBool>()->setvalue(data < args[0]->to<HInt>()->value()));
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

HPointer HLang::HInt::hw(HArgs args)
{
	std::cout << args[0]->to<HInt>()->value();
	return HPointer(new HVoid);
}

HLang::HInt* HLang::HInt::setvalue(int i)
{
	this->data = i;
	return this;
}