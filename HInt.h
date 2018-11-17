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
	HObject* set(std::vector<HObject*> args);
	HObject* getAndplusplus(std::vector<HObject*> args);
	HObject* toString(std::vector<HObject*> args);
private:
	int *data;
};
