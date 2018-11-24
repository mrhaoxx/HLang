#include "HInt.h"
#include "HString.h"

HInt::HInt(int i)
{
	data = new int(i);
	DefineMemberFunction("++", &HInt::getAndplusplus);
	DefineMemberFunction("fromString", &HInt::setStr);
	DefineMemberFunction("toString", &HInt::toString);
	DefineMemberFunction("set", &HInt::setInt);
}

HInt::~HInt()
{
	delete data;
}

int* HInt::value()
{
	return new int(*data);
}

HObject* HInt::setStr(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	int i = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	*data = i;
	return new HRet(true);
}
HObject* HInt::setInt(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	int i = *HObjectHelper(args[0]).to<HInt>()->value();
	*data = i;
	return new HRet(true);
}
HObject* HInt::toString(HArgs args)
{
	CheckArgs(0);
	return new HRet(new HString(new QString(QString::number(*data))));
}

HObject* HInt::getAndplusplus(HArgs args)
{
	CheckArgs(0);
	*data = *data + 1;
	return new HRet(new HInt(*data));
}