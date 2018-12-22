#pragma once
#include "HObject.h"
#include "HFunction.h"
#include "HLang.h"
class HIf :
	public HObject
{
	H_OBJECT(HIf);
public:
	HIf();
	HPointer which(HArgs args);
	HPointer htrue(HArgs args);
	HPointer hfalse(HArgs args);
	HPointer hexec(HArgs args);

private:
	QSharedPointer<HFunction> iftrue;
	QSharedPointer<HFunction> iffalse;
	QSharedPointer<HBool> ifwhich;
};
