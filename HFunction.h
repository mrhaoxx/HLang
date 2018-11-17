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
	HObject* add(std::vector<HObject*> args);
	HObject* hexec(std::vector<HObject*> args);
	HObject* loadfile(std::vector<HObject*> args);

private:
	QVector<QString*> commands;
};
