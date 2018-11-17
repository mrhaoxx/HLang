#include "HBool.h"
#include "HBaseInterface.h"

inline HBool::HBool(bool par)
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
HObject* HBool::set(std::vector<HObject*> args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "true")
		data = true;
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "false")
		data = false;
	return new HBool(true);
}