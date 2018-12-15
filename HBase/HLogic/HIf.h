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
	QSharedPointer<HObject> which(HArgs args);
	QSharedPointer<HObject> htrue(HArgs args);
	QSharedPointer<HObject> hfalse(HArgs args);
	QSharedPointer<HObject> hexec(HArgs args);

private:
	QSharedPointer<HFunction> iftrue;
	QSharedPointer<HFunction> iffalse;
	QSharedPointer<HBool> ifwhich;
};
