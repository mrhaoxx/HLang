#pragma once
#include "HObject.h"
#define  H_DEBUG
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
#ifdef H_DEBUG
		DefineMemberFunction("cout", &HBuiltin::hcout);
#endif
	}
	H_MemberFunction_def(newclass, HBuiltin);
	H_MemberFunction_def(deleteclass, HBuiltin);
	H_MemberFunction_def(hsleep, HBuiltin);
	H_MemberFunction_def(hsystem, HBuiltin);
#ifdef H_DEBUG
	H_MemberFunction_def(hcout, HBuiltin);
#endif
};
