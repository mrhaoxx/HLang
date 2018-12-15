#pragma once
#include "HLogic/HFunction.h"
#include "HData/HBool.h"
class HWhile :
	public HFunction
{
	H_OBJECT(HWhile);
public:
	HWhile();
	QSharedPointer<HObject> setcond(HArgs args);
	QSharedPointer<HObject> run(HArgs args);
private:
	QSharedPointer<HBool> data;
};
