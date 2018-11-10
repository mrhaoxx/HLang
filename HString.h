#pragma once
#include <QString>
#include <HObject.h>
class HString : public QString, public HObject
{
public:
	HString(QString *parent);
	~HString();
};
