#pragma once
#include "HObject.h"

class HBuiltin :
	public HObject
{
	H_OBJECT(HBuiltin)
public:
	HBuiltin();
	HObject* newclass(HArgs args);
	HObject* deleteclass(HArgs args);
	HObject* sleep(HArgs args);
	HObject* system(HArgs args);
	HObject* msg(HArgs args);
};
