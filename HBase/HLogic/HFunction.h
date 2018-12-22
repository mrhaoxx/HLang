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
	QString _pure_args;
};
class HClass;
class HFunction :
	public HObject
{
	friend HClass;
	H_OBJECT(HFunction);
	HLang *upperdef = nullptr;
	HLang *thisdef = nullptr;
	static QStringList SplitCommands(QString cmds);
	static HCommand ResolveCommand(QString cmd);
	void runcode(HCommand cmd);
	QStringList commands;
	QStringList argnames;
	void resetdef();
public:
	HFunction(HLang *upperdef = nullptr, QStringList argsname = QStringList());
	HPointer fromString(HArgs args);
	HPointer run(HArgs args);
	HPointer copy(HArgs args);
	static void CoutMsg(HError &e);
	~HFunction();
};
