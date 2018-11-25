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
	operator bool();
	HObject* set(HArgs args);
private:
	bool data;
};
