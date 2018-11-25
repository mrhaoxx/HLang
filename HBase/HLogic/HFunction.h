#pragma once
#include "HObject.h"
#include <QVector>
#include "HLang.h"
#include "HBuiltin.h"
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
	HObject* fromString(HArgs args);
	HObject* addArgs(HArgs args);
	HObject* link(HArgs args);
private:
	void reset();
	HLang *def = new HLang;
	std::vector<QString*> argsname;
	QVector<QString*> commands;
};
