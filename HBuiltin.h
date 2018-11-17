#pragma once
#include "HObject.h"

class HBuiltin :
	public HObject
{
	H_OBJECT(HBuiltin)
public:
	HBuiltin() {
		DefineMemberFunction("new", &HBuiltin::newclass);
		DefineMemberFunction("delete", &HBuiltin::deleteclass);
		DefineMemberFunction("usleep", &HBuiltin::hsleep);
		DefineMemberFunction("system", &HBuiltin::hsystem);
		DefineMemberFunction("msg", &HBuiltin::msg);
	}
	H_MemberFunction_def(newclass, HBuiltin);
	H_MemberFunction_def(deleteclass, HBuiltin);
	H_MemberFunction_def(hsleep, HBuiltin);
	H_MemberFunction_def(hsystem, HBuiltin);
	H_MemberFunction_def(msg, HBuiltin);
};
