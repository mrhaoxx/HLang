#include "HIf.h"
#include "HData/HBool.h"
HIf::HIf()
{
	DefineMemberFunction(HIf, "setwhich", &HIf::which);
	DefineMemberFunction(HIf, "settrue", &HIf::htrue);
	DefineMemberFunction(HIf, "setfalse", &HIf::hfalse);
	DefineMemberFunction(HIf, "run", &HIf::hexec);
}
QSharedPointer<HObject> HIf::which(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HBool);
	this->ifwhich = HObjectHelper(args[0]).to<HBool>();
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HIf::htrue(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->iftrue = HObjectHelper(args[0]).to<HFunction>();
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HIf::hfalse(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->iffalse = HObjectHelper(args[0]).to<HFunction>();
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HIf::hexec(HArgs args)
{
	CheckArgs(0);
	if (iftrue == nullptr || iffalse == nullptr || ifwhich == nullptr)
		throw HError(HError::RT_ERROR, WhyIfExecFailed);
	if (ifwhich)
		iftrue->run(args);
	else
		iffalse->run(args);
	return QSharedPointer<HObject>(new HVoid);
}