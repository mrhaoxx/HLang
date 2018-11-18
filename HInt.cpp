#include "HInt.h"
#include "HBaseInterface.h"
HInt::HInt(int i)
{
	data = new int(i);
	DefineMemberFunction("++", &HInt::getAndplusplus);
	DefineMemberFunction("set", &HInt::set);
	DefineMemberFunction("toString", &HInt::toString);
}

HInt::~HInt()
{
	delete data;
}

int* HInt::value()
{
	return new int(*data);
}

HObject* HInt::set(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	int i = HObjectHelper(args[0]).to<HString>()->toQString().toInt();
	*data = i;
	return new HRet(true);
}

HObject* HInt::toString(HArgs args)
{
	CheckArgs(0);
	return new HRet(new HString(&QString::number(*data)));
}

HObject* HInt::getAndplusplus(HArgs args)
{
	CheckArgs(0);
	*data = *data + 1;
	return new HRet(new HInt(*data));
}