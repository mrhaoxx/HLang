#pragma once
#include "HObject.h"
#include <QVector>
class HFunction :
	public HObject
{
	H_OBJECT(HFunction);
public:
	HFunction();
	~HFunction();
	H_MemberFunction_def(add, HFunction);
	H_MemberFunction_def(hexec, HFunction);
	H_MemberFunction_def(loadfile, HFunction);

private:
	QVector<QString*> commands;
};
