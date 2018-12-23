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
}

HInt::~HInt()
{
	delete data;
}

int HInt::value()
{
	return int(*data);
}

HInt::operator int()
{
	return int(*data);
}

HPointer HInt::setStr(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	int i = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	*data = i;
	return HPointer(new HVoid);
}
HPointer HInt::setInt(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	int i = *HObjectHelper(args[0]).to<HInt>();
	*data = i;
	return HPointer(new HVoid);
}

HPointer HInt::plus(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	*data = *data + HObjectHelper(args[0]).to<HInt>()->value();
	return HPointer(new HVoid);
}

HPointer HInt::minus(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	*data = *data - HObjectHelper(args[0]).to<HInt>()->value();
	return HPointer(new HVoid);
}

HPointer HInt::toString(HArgs args)
{
	CheckArgs(0);
	return HPointer(new HString(QString::number(*data)));
}

HPointer HInt::getAndplusplus(HArgs args)
{
	CheckArgs(0);
	*data = *data + 1;
	return HPointer(new HInt(*this));
}