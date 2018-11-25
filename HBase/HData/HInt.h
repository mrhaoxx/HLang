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
	HObject* setStr(HArgs args);
	HObject* getAndplusplus(HArgs args);
	HObject* toString(HArgs args);
	HObject* setInt(HArgs args);
private:
	int *data;
};
