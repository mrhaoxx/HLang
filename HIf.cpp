#include "HIf.h"
#include "HLang.h"
HIf::HIf()
{
	DefineMemberFunction("setwhich", &HIf::which);
	DefineMemberFunction("settrue", &HIf::htrue);
	DefineMemberFunction("setfalse", &HIf::hfalse);
	DefineMemberFunction("exec", &HIf::hexec);
}

H_MemberFunction_def(which, HIf)
{
	CheckArgs(1);
	SetupArgs;
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HBool>() != nullptr)
		this->ifwhich = HLangHelper(HMain->accessclass(GetArg(0))).to<HBool>();
	else
		return new HBool(false);
	return new HBool(true);
}

H_MemberFunction_def(htrue, HIf)
{
	CheckArgs(1);
	SetupArgs;
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HFunction>() != nullptr)
		this->iftrue = HLangHelper(HMain->accessclass(GetArg(0))).to<HFunction>();
	else
		return new HBool(false);
	return new HBool(true);
}

H_MemberFunction_def(hfalse, HIf)
{
	CheckArgs(1);
	SetupArgs;
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HFunction>() != nullptr)
		this->iffalse = HLangHelper(HMain->accessclass(GetArg(0))).to<HFunction>();
	else
		return new HBool(false);
	return new HBool(true);
}

H_MemberFunction_def(hexec, HIf)
{
	CheckArgs(0);
	SetupArgs;
	if (ifwhich->value())
		iftrue->hexec(HOBJECTS(), HOBJECTS());
	else
		iffalse->hexec(HOBJECTS(), HOBJECTS());
	return new HBool(true);
}