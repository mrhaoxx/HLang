#include "HIf.h"
#include "HLang.h"
HIf::HIf()
{
	DefineMemberFunction("setwhich", &HIf::which);
	DefineMemberFunction("settrue", &HIf::htrue);
	DefineMemberFunction("setfalse", &HIf::hfalse);
	DefineMemberFunction("exec", &HIf::hexec);
}
HObject* HIf::which(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HBool>() != nullptr)
		this->ifwhich = HObjectHelper(args[0]).to<HBool>();
	else
		return new HBool(false);
	return new HBool(true);
}

HObject* HIf::htrue(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HFunction>() != nullptr)
		this->iftrue = HObjectHelper(args[0]).to<HFunction>();
	else
		return new HBool(false);
	return new HBool(true);
}

HObject* HIf::hfalse(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HFunction>() != nullptr)
		this->iffalse = HObjectHelper(args[0]).to<HFunction>();
	else
		return new HBool(false);
	return new HBool(true);
}

HObject* HIf::hexec(HArgs args)
{
	CheckArgs(0);
	if (ifwhich->value())
		iftrue->hexec(args);
	else
		iffalse->hexec(args);
	return new HBool(true);
}