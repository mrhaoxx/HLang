#pragma once
#include "HObject.h"
class HVector :
	public HObject
{
	H_OBJECT(HVector);
	QVector<HWeakPointer> data;
public:
	HVector();
	~HVector();
	HPointer append(HArgs args);
	HPointer get(HArgs args);
};
