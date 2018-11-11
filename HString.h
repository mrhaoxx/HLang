#pragma once
#include <QString>
#include <HObject.h>
class HString : public QString, public HObject
{
	H_OBJECT(HString);
public:
	HString(QString *parent);
	~HString();
	QString toQString();
	H_MemberFunction_def(set, HString);
};
