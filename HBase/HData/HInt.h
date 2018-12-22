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
	HPointer setStr(HArgs args);
	HPointer getAndplusplus(HArgs args);
	HPointer toString(HArgs args);
	HPointer setInt(HArgs args);
	HPointer plus(HArgs args);
	HPointer minus(HArgs args);
private:
	int *data;
};
