#pragma once
#include "HLogic/HFunction.h"
#include "HData/HBool.h"
class HWhile :
	public HFunction
{
	H_OBJECT(HWhile);
public:
	HWhile();
	HPointer setcond(HArgs args);
	HPointer run(HArgs args);
private:
	QSharedPointer<HBool> data;
};
