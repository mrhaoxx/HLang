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
	HObject* which(HArgs args);
	HObject* htrue(HArgs args);
	HObject* hfalse(HArgs args);
	HObject* hexec(HArgs args);

private:
	HFunction* iftrue;
	HFunction* iffalse;
	HBool* ifwhich;
};
