#include "HWhile.h"

HWhile::HWhile()
{
	InheritFrom(HFunction, HWhile);
	DefineMemberFunction(HWhile, "run", &HWhile::run);
	DefineMemberFunction(HWhile, "set", &HWhile::setcond);
}

HPointer HWhile::setcond(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HBool);
	data = HObjectHelper(args[0]).to<HBool>();
	return HPointer(new HVoid);
}

HPointer HWhile::run(HArgs args)
{
	if (data.isNull())
		throw HError(HError::RT_ERROR, "While Not Setup");
	while (data->value())
	{
		return this->HFunction::run(args);
	}
	return HPointer(new HVoid);
}