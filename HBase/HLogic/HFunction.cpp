#include "HFunction.h"

QStringList HFunction::SplitCommands(QString cmds)
{
	QStringList a = cmds.simplified().split(";");
	for (int i = 0; i < a.length(); i++)
		a[i] = a[i].simplified();
	return a;
}

HCommand HFunction::ResolveCommand(QString cmd)
{
	QString f = cmd.split(QRegExp("\\((.*)"))[0];
	QString _backvalue = cmd.contains("=") ? f.split("=")[0] : QString("");
	f = f.split(_backvalue + "=")[1];
	QString _class = cmd.contains(".") ? f.split(".")[0] : QString("builtin");
	QString _function = cmd.contains(".") ? f.split(".")[1] : f;
	f = cmd.split("(").mid(1).join("(");
	QStringList t = f.split(")");
	t.removeLast();
	f = t.join(")");
	QStringList args = f.split(",");
	HCommand c;
	c._class = _class;
	c._backvalue_name = _backvalue;
	c._args = args;
	c._func = _function;
	return c;
};

HFunction::HFunction(HLang *upperdef)
{
	this->upperdef = upperdef;
}