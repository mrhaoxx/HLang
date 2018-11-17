#pragma once
#include "HObject.h"
class HBool :
	public HObject
{
	H_OBJECT(HBool);
public:
	HBool(bool par = false);
	~HBool();
	bool value();
	HObject* set(std::vector<HObject*> args);
private:
	bool data;
};
