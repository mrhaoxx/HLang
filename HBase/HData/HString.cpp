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
	MDebug("Constructed");
	data = new QString;
	*this->data = str;
}
QString& HString::toQString()
{
	return *data;
}

QSharedPointer<HObject> HString::set(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	*data = HObjectHelper(args[0]).to<HString>()->toQString();
	return QSharedPointer<HObject>(new HInt(data->length()));
}

QSharedPointer<HObject> HString::at(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	return QSharedPointer<HObject>(new HString(data->at(*HObjectHelper(args[0]).to<HInt>())));
}

QSharedPointer<HObject> HString::append(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	data->append((QString)*HObjectHelper(args[0]).to<HString>());
	return QSharedPointer<HObject>(new HVoid);
}

HString::operator std::string()
{
	return data->toStdString();
}
HString::~HString() {
	MDebug("Destructed");
	delete data;
}