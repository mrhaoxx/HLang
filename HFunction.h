#pragma once
#include "HObject.h"
#include <QVector>
#include "HLang.h"
class HFunction :
	public HObject
{
	H_OBJECT(HFunction);
public:
	HFunction();
	~HFunction();
	HObject* add(HArgs args);
	HObject* hexec(HArgs args);
	HObject* loadfile(HArgs args);
	HObject* toString(HArgs args);
	HObject* loadString(HArgs args);
private:
	HLang *def = new HLang;
	QVector<QString*> commands;
};
