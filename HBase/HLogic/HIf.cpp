#include "HIf.h"
#include "HData/HBool.h"
HIf::HIf()
{
	DefineMemberFunction("setwhich", &HIf::which);
	DefineMemberFunction("settrue", &HIf::htrue);
	DefineMemberFunction("setfalse", &HIf::hfalse);
	DefineMemberFunction("run", &HIf::hexec);
}
HObject* HIf::which(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HBool);
	this->ifwhich = HObjectHelper(args[0]).to<HBool>();
	return new HVoid;
}

HObject* HIf::htrue(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->iftrue = HObjectHelper(args[0]).to<HFunction>();
	return new HVoid;
}

HObject* HIf::hfalse(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->iffalse = HObjectHelper(args[0]).to<HFunction>();
	return new HVoid;
}

HObject* HIf::hexec(HArgs args)
{
	CheckArgs(0);
	if (iftrue == nullptr || iffalse == nullptr || ifwhich == nullptr)
		throw HError(HError::RT_ERROR, WhyIfExecFailed);
	if (ifwhich)
		iftrue->run(args);
	else
		iffalse->run(args);
	return new HVoid;
}