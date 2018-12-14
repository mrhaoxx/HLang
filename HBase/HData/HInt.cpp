#include "HInt.h"
#include "HString.h"
#include "HVoid.h"

HInt::HInt(int i)
{
	data = new int(i);
	DefineMemberFunction(HInt, "++", &HInt::getAndplusplus);
	DefineMemberFunction(HInt, "fromString", &HInt::setStr);
	DefineMemberFunction(HInt, "toString", &HInt::toString);
	DefineMemberFunction(HInt, "set", &HInt::setInt);
	DefineMemberFunction(HInt, "+", &HInt::plus);
	DefineMemberFunction(HInt, "-", &HInt::minus);
	MDebug("Constructed");
}

HInt::~HInt()
{
	delete data;
	MDebug("Destructed");
}

int HInt::value()
{
	return int(*data);
}

HInt::operator int()
{
	return int(*data);
}

HObject* HInt::setStr(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	int i = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	*data = i;
	return new HVoid;
}
HObject* HInt::setInt(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	int i = *HObjectHelper(args[0]).to<HInt>();
	*data = i;
	return new HVoid;
}

HObject* HInt::plus(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	*data = *data + HObjectHelper(args[0]).to<HInt>()->value();
	return new HVoid;
}

HObject* HInt::minus(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	*data = *data - HObjectHelper(args[0]).to<HInt>()->value();
	return new HVoid;
}

HObject* HInt::toString(HArgs args)
{
	CheckArgs(0);
	return new HString(QString::number(*data));
}

HObject* HInt::getAndplusplus(HArgs args)
{
	CheckArgs(0);
	*data = *data + 1;
	return this;
}