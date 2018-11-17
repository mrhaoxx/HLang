#pragma once
#include "HObject.h"

class HBuiltin :
	public HObject
{
	H_OBJECT(HBuiltin)
public:
	HBuiltin();
	HObject* newclass(std::vector<HObject*> args);
	HObject* deleteclass(std::vector<HObject*> args);
	HObject* sleep(std::vector<HObject*> args);
	HObject* system(std::vector<HObject*> args);
	HObject* msg(std::vector<HObject*> args);
};
