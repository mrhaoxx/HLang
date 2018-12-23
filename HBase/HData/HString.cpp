#include "HString.h"
#include "HInt.h"
#include "HVoid.h"

HString::operator QString&()
{
	return *data;
}

HString::operator const char*()
{
	return data->toStdString().c_str();
}

HString::HString(QString str)
{
	DefineMemberFunction(HString, "set", &HString::set);
	DefineMemberFunction(HString, "at", &HString::at);
	DefineMemberFunction(HString, "append", &HString::append);
	data = new QString;
	*this->data = str;
}
QString& HString::toQString()
{
	return *data;
}

HPointer HString::set(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	*data = HObjectHelper(args[0]).to<HString>()->toQString();
	return HPointer(new HInt(data->length()));
}

HPointer HString::at(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	return HPointer(new HString(data->at(*HObjectHelper(args[0]).to<HInt>())));
}

HPointer HString::append(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	data->append(HObjectHelper(args[0]).to<HString>()->toQString());
	return HPointer(new HVoid);
}

HString::operator std::string()
{
	return data->toStdString();
}
HString::~HString() {
	delete data;
}