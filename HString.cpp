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

HObject* HString::set(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->clear();
	this->append(HObjectHelper(args[0]).to<HString>());
	return new HRet(new HInt(this->length()));
}