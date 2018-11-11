#pragma once
#include "HObject.h"
#include "HFunction.h"
#include "HBool.h"
class HIf :
	public HObject
{
	H_OBJECT(HIf);
public:
	HIf();
	H_MemberFunction_def(which, HIf);
	H_MemberFunction_def(htrue, HIf);
	H_MemberFunction_def(hfalse, HIf);
	H_MemberFunction_def(hexec, HIf);
private:
	HFunction* iftrue;
	HFunction* iffalse;
	HBool* ifwhich;
};
