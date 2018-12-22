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
	HString(QString str = "");
	~HString();
	QString& toQString();
	HPointer set(HArgs args);
	HPointer at(HArgs args);
	HPointer append(HArgs args);
};
