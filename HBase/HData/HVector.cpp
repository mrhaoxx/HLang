#include "HVector.h"
#include "HVoid.h"
#include "HInt.h"

HVector::HVector()
{
	DefineMemberFunction(HVector, "get", &HVector::get);
	DefineMemberFunction(HVector, "append", &HVector::append);
}

HVector::~HVector()
{
	foreach(HPointer p, data)
		p.clear();
}

inline HPointer HVector::append(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HObject);
	this->data.append(args[0]);
	return HPointer(new HVoid);
}

inline HPointer HVector::get(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	return data.at(HObjectHelper(args[0]).to<HInt>()->value()).toStrongRef();
}