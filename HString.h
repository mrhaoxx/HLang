#pragma once
#include <QString>
#include <HObject.h>
class HString : public QString, public HObject
{
	H_OBJECT(HString);
public:
	HString(QString *parent = new QString(""));
	~HString();
	QString toQString();
	HObject* set(std::vector<HObject*> args);
};
