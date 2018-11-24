#include "HBool.h"
#include "HString.h"

HBool::HBool(bool par)
{
	data = par;
	DefineMemberFunction("set", &HBool::set);
}

HBool::~HBool()
{
}

bool HBool::value()
{
	return data;
}
HObject* HBool::set(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "true")
		data = true;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "false")
		data = false;
	return new HRet(true);
}