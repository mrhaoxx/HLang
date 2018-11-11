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

HInt::H_MemberFunction_def(set, HInt)
{
	CheckArgs(1);
	SetupArgs;
	int i = GetArg(0).toInt();
	*data = i;
	return new HBool(true);
}

H_MemberFunction_def(toString, HInt)
{
	return new HString(&QString::number(*data));
}

H_MemberFunction_def(getAndplusplus, HInt)
{
	*data = *data + 1;
	return new HInt(*data);
}