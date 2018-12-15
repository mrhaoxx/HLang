#pragma once
#include "HObject.h"
class HInt :
	public HObject
{
	H_OBJECT(HInt);
public:
	HInt(int i = 0);
	~HInt();
	int value();
	operator int();
	QSharedPointer<HObject> setStr(HArgs args);
	QSharedPointer<HObject> getAndplusplus(HArgs args);
	QSharedPointer<HObject> toString(HArgs args);
	QSharedPointer<HObject> setInt(HArgs args);
	QSharedPointer<HObject> plus(HArgs args);
	QSharedPointer<HObject> minus(HArgs args);
private:
	int *data;
};
