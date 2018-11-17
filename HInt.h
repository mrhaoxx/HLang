#pragma once
#include "HObject.h"
class HInt :
	public HObject
{
	H_OBJECT(HInt);
public:
	HInt(int i = 0);
	~HInt();
	int* value();
	HObject* set(HArgs args);
	HObject* getAndplusplus(HArgs args);
	HObject* toString(HArgs args);
private:
	int *data;
};
