#pragma once
#include "HObject.h"
class HBool :
	public HObject
{
	H_OBJECT(HBool);
public:
	HBool(bool par = false)
	{
		data = par;
		DefineMemberFunction("set", &HBool::set);
	}
	bool value() { return data; }
	H_MemberFunction_def(set, HBool);
private:
	bool data;
};
