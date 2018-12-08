#include "HBool.h"
#include "HString.h"
#include "HVoid.h"
HBool::HBool(bool par)
{
	data = par;
	DefineMemberFunction("set", &HBool::set);
	MDebug("Constructed");
}

HBool::~HBool()
{
	MDebug("Destructed");
}

bool HBool::value()
{
	MDebug("Accessing");
	return data;
}

HBool::operator bool()
{
	MDebug("Accessing");
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
	MDebug("Setting");
	__FILENAME__;
	return new HVoid;
}