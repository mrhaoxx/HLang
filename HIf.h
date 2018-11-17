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
	HObject* which(std::vector<HObject*> args);
	HObject* htrue(std::vector<HObject*> args);
	HObject* hfalse(std::vector<HObject*> args);
	HObject* hexec(std::vector<HObject*> args);

private:
	HFunction* iftrue;
	HFunction* iffalse;
	HBool* ifwhich;
};
