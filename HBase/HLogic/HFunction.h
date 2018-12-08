#pragma once
#include "HObject.h"
#include <QVector>
#include "HLang.h"
#include "HBuiltin.h"

struct HCommand {
	QString _class;
	QString _func;
	QStringList _args;
	QStringList _argstrs;
	QString _backvalue_name;
};
class HCodes;
class HFunction :
	public HObject
{
	H_OBJECT(HFunction);
	HLang *upperdef = nullptr;
	HLang *thisdef = nullptr;
	friend HCodes;
	QStringList commands;
	QStringList SplitCommands(QString cmds);
	HCommand ResolveCommand(QString cmd);
	void runcode(HCommand cmd);
	void resetdef();
public:
	HFunction(HLang *upperdef = nullptr);
	HObject* fromString(HArgs args);
	HObject* run(HArgs args);
	static void CoutMsg(HError &e);
	~HFunction();
};
