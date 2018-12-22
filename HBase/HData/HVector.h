#pragma once
#include "HObject.h"
class HVector :
	public HObject
{
	H_OBJECT(HVector);
	QVector<HPointer> *data;
public:
	HVector();
	HPointer append(HArgs args);
	HPointer get(HArgs args);
};
