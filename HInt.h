#pragma once
#include "HObject.h"
class HInt :
	public HObject
{
	H_OBJECT(HInt);
public:
	HInt(int i = 0);
	~HInt();
	int* value();
	H_MemberFunction_def(set, HInt);
	H_MemberFunction_def(getAndplusplus, HInt);
	H_MemberFunction_def(toString, HInt);
private:
	int *data;
};
