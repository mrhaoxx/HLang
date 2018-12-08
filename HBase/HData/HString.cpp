#include "HString.h"
#include "HInt.h"

HString::operator QString&()
{
	return *data;
}

HString::operator const char*()
{
	return data->toStdString().c_str();
}

HString::HString(QString *parent)
{
	DefineMemberFunction("set", &HString::set);
	MDebug("Constructed");
	this->data = new QString(*parent);
}

HString::HString(QString str)
{
	DefineMemberFunction("set", &HString::set);
	MDebug("Constructed");
	data = new QString;
	*this->data = str;
}
QString& HString::toQString()
{
	return *data;
}

HObject* HString::set(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	*data = HObjectHelper(args[0]).to<HString>()->toQString();
	return new HInt(data->length());
}

HString::operator std::string()
{
	return data->toStdString();
}
HString::~HString() {
	MDebug("Destructed");
	delete data;
}