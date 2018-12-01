#pragma once
#include "HObject.h"
#include <QVector>
#include "HLang.h"
#include "HBuiltin.h"
class HCodes;
class HFunction :
	public HObject
{
	H_OBJECT(HFunction);
	HLang *upperdef;
	friend HCodes;
	QStringList SplitCommands(QString cmds);
	HCommand ResolveCommand(QString cmd);
	void CoutMsg(HError &e);
public:
	HFunction(HLang *upperdef = nullptr);
	HObject* fromString(HArgs args);
	HObject* run(HArgs args);
};
