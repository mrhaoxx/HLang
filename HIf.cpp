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
	if (HObjTo(HMain->accessclass(GetArg(0)), HBool*) != nullptr)
		this->ifwhich = HObjTo(HMain->accessclass(GetArg(0)), HBool*);
	else
		return new HBool(false);
	return new HBool(true);
}

H_MemberFunction_def(htrue, HIf)
{
	CheckArgs(1);
	SetupArgs;
	if (HObjTo(HMain->accessclass(GetArg(0)), HFunction*) != nullptr)
		this->iftrue = HObjTo(HMain->accessclass(GetArg(0)), HFunction*);
	else
		return new HBool(false);
	return new HBool(true);
}

H_MemberFunction_def(hfalse, HIf)
{
	CheckArgs(1);
	SetupArgs;
	if (HObjTo(HMain->accessclass(GetArg(0)), HFunction*) != nullptr)
		this->iffalse = HObjTo(HMain->accessclass(GetArg(0)), HFunction*);
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