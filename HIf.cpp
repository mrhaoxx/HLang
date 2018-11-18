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
	CheckArgsType(0, HBool);
	this->ifwhich = HObjectHelper(args[0]).to<HBool>();
	return new HRet(true);
}

HObject* HIf::htrue(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->iftrue = HObjectHelper(args[0]).to<HFunction>();
	return new HRet(true);
}

HObject* HIf::hfalse(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->iffalse = HObjectHelper(args[0]).to<HFunction>();
	return new HRet(true);
}

HObject* HIf::hexec(HArgs args)
{
	CheckArgs(0);
	if (iftrue == nullptr || iffalse == nullptr)
		return new HRet(nullptr, false, WhyIfExecFailed);
	if (ifwhich->value())
		iftrue->hexec(args);
	else
		iffalse->hexec(args);
	return new HRet(true);
}