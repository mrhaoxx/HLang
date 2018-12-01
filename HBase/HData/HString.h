#pragma once
#include <QString>
#include <HObject.h>

class HString : public HObject
{
	H_OBJECT(HString);
	QString* data = nullptr;
public:
	operator QString&();
	operator const char*();
	operator std::string();
	HString(QString *parent = new QString(""));
	HString(QString str);
	QString& toQString();
	HObject* set(HArgs args);
};
