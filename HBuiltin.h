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
		DefineMemberFunction("show", &HBuiltin::showvarrs);
		DefineMemberFunction("newvarrs", &HBuiltin::newvarrs);
	}
	H_MemberFunction_def(newclass, HBuiltin);
	H_MemberFunction_def(showvarrs, HBuiltin);
	H_MemberFunction_def(newvarrs, HBuiltin);
	H_MemberFunction_def(deleteclass, HBuiltin);
};
