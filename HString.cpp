#include "HString.h"
#include "HBaseInterface.h"
HString::HString(QString *parent)
	: QString(*parent)
{
	DefineMemberFunction("set", &HString::set);
}

HString::~HString()
{
}

QString HString::toQString()
{
	return *(QString*)this;
}

H_MemberFunction_def(set, HString)
{
	CheckArgs(1);
	SetupArgs;
	this->clear();
	this->append(GetArg(0));
	return new HInt(this->length());
}