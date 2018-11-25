#pragma once
#include <QString>
#include <HObject.h>

class HString : public QString, public HObject
{
	H_OBJECT(HString);
public:
	operator QString();
	operator const char*();
	operator std::string();
	HString(QString *parent = new QString(""));
	HString(QString str);
	QString toQString();
	HObject* set(HArgs args);
};
