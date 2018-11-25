#include "HString.h"
#include "HInt.h"

HString::operator QString()
{
	return this->toQString();
}

HString::operator const char*()
{
	return this->toQString().toStdString().c_str();
}

HString::HString(QString *parent)
	: QString(*parent)
{
	DefineMemberFunction("set", &HString::set);
}

HString::HString(QString str)
{
	DefineMemberFunction("set", &HString::set);
	this->append(str);
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

HString::operator std::string()
{
	return this->toStdString();
}