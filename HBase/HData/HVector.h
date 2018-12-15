#pragma once
#include "HObject.h"
class HVector :
	public HObject
{
	H_OBJECT(HVector);
	QVector<QSharedPointer<HObject>> *data;
public:
	HVector();
	QSharedPointer<HObject> append(HArgs args);
	QSharedPointer<HObject> get(HArgs args);
};
