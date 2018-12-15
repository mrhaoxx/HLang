#include "HVector.h"
#include "HVoid.h"
#include "HInt.h"

HVector::HVector()
{
	DefineMemberFunction(HVector, "get", &HVector::get);
	DefineMemberFunction(HVector, "append", &HVector::append);
	data = new QVector<QSharedPointer<HObject>>;
}

inline QSharedPointer<HObject> HVector::append(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HObject);
	this->data->append(args[0]);
	return QSharedPointer<HObject>(new HVoid);
}

inline QSharedPointer<HObject> HVector::get(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	return data->at(HObjectHelper(args[0]).to<HInt>()->value());
}