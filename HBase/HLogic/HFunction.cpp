#include "HFunction.h"
QStringList HFunction::SplitCommands(QString cmds)
{
	QStringList strlist;
	QString f = cmds;
	f = f.replace("\\\"", "\u0001");
	QStringList t = cmds.split("\"");
	for (int i = 0; i < t.length(); i++)
		if ((i & 1) != 0)
			strlist.push_back(t[i]);
	for (int i = 0; i < strlist.length(); i++)
		f.replace(strlist[i], "(\u0002" + QString(i) + ")");
	for (int x = 0; x < strlist.length(); x++)
		strlist[x] = strlist[x].replace("\u0001", "\\\"");
	QStringList a = f.simplified().split(";");
	for (int x = 0; x < a.length(); x++)
		if (a[x].contains("\u0002"))
			for (int y = 0; y < strlist.length(); y++)
				if (a[x].contains("\u0002" + QString(y)))
					a[x] = a[x].replace("(\u0002" + QString(y) + ")", strlist[y]);
	for (int i = 0; i < a.length(); i++)
		a[i] = a[i].simplified();
	while (a.last().isEmpty())
		a.removeLast();
	return a;
}

HFunction::~HFunction() {
	this->resetdef();
}
HCommand HFunction::ResolveCommand(QString cmd)
{
	HCommand c;
	QString f = cmd.split(QRegExp("\\((.*)"))[0];
	c._backvalue_name = cmd.contains("=") ? f.split("=")[0] : QString("");
	if (cmd.contains("="))f = f.split("=")[1];
	c._class = cmd.contains(".") ? f.split(".")[0] : QString("builtin");
	c._func = cmd.contains(".") ? f.split(".")[1] : f;
	f = cmd.split("(").mid(1).join("(");
	QStringList t = f.split(")");
	t.removeLast();
	f = t.join(")");
	c._pure_args = f;
	f = f.replace("\\\"", "\u0001");
	if (f.contains("\"")) {
		t = f.split("\"");
		if (t.first().isEmpty())
			t.removeFirst();
		QStringList strlist;
		for (int i = 0; i < t.length(); i++)
			if ((i & 1) == 0)
				strlist.push_back(t[i]);
		for (int i = 0; i < strlist.length(); i++)
			f.replace(strlist[i], "(\u0002" + QString(i) + ")");
		for (int x = 0; x < strlist.length(); x++)
			strlist[x] = strlist[x].replace("\u0001", "\\\"");
		c._argstrs = strlist;
	}
	c._args = f.split(",");
	return c;
};

void HFunction::CoutMsg(HError &e)
{
	QString LMSG;
	switch (e.getELevel())
	{
	case HError::NONE:
		LMSG = QString(NOCOLOR) + "NONE" + QString(ColorClear);
		break;
	case HError::RT_NOTICE:
		LMSG = QString(YELLOWCOLOR) + "NOTICE" + QString(ColorClear);
		break;
	case HError::RT_WARNING:
		LMSG = QString(WARNINGCOLOR) + "WARNING" + QString(ColorClear);
		break;
	case HError::RT_ERROR:
		LMSG = QString(REDCOLOR) + "ERROR" + QString(ColorClear);
		break;
	}
	RT_DEBUG << (QString("\b\b\b\b\b\b\b[" + LMSG + "]") + BWCOLOR + e.getWhy() + ColorClear).toStdString().c_str();
}

void HFunction::runcode(HCommand cmd)
{
	QTextStream(stdout) << NOCOLOR << indent->toStdString().c_str() << ((cmd._backvalue_name != "") ? (cmd._backvalue_name + "=") : QString("")) + (cmd._class + "->" + cmd._func) + ("(" + cmd._pure_args + ")") << "[EXEC] ";
	if (thisdef == nullptr) {
		thisdef = new HLang(upperdef);
		thisdef->importclass("builtin", HPointer(new HBuiltin(thisdef)));
	}
	try {
		HArgs args;
		for (int x = 0; x < cmd._args.length(); x++)
			if (cmd._args[x].contains("\u0002"))
				for (int y = 0; y < cmd._argstrs.length(); y++)
					if (cmd._args[x].contains("\u0002" + QString(y))) {
						args.insert(x, HPointer(new HString(cmd._argstrs[y])));
					}
					else;
			else {
				bool isit = false;
				int  toit = cmd._args[x].toInt(&isit);
				if (isit) {
					args.insert(x, HPointer(new HInt(toit)));
				}
				else
					if (cmd._args[x] == "true") {
						args.insert(x, HPointer(new HBool(true)));
					}
					else if (cmd._args[x] == "false") {
						args.insert(x, HPointer(new HBool(false)));
					}
					else if (cmd._args[x].isEmpty()) {
						args.insert(x, HPointer(new HVoid));
					}
					else
					{
						HPointer arg = thisdef->accessclass(cmd._args[x]);
						if (arg.isNull())
							throw HError(HError::RT_ERROR, "Args Class Not Find");
						else
							args.insert(x, arg);
					}
			}
		HPointer aceobj = thisdef->accessclass(cmd._class);
		if (!aceobj.isNull()) {
			if (!cmd._backvalue_name.isEmpty())
				thisdef->importclass(cmd._backvalue_name, aceobj->exec(cmd._func, args));
			else
				aceobj->exec(cmd._func, args).clear();
		}
		else
			throw HError(HError::RT_ERROR, "Object Class Not Found");
		QTextStream(stdout) << "\b\b\b\b\b\b\b[OK]  \n";
	}
	catch (HError& e)
	{
		CoutMsg(e);
	}
}

void HFunction::resetdef()
{
	if (thisdef == nullptr)
		return;
	delete thisdef;
	thisdef = nullptr;
	return;
}

HFunction::HFunction(HLang *upperdef, QStringList argsname)
{
	DefineMemberFunction(HFunction, "fromString", &HFunction::fromString);
	DefineMemberFunction(HFunction, "run", &HFunction::run);
	this->upperdef = upperdef;
	this->argnames = argsname;
}

HPointer HFunction::fromString(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->commands = SplitCommands(*HObjectHelper(args[0]).to<HString>());
	return HPointer(new HVoid);
}

HPointer HFunction::run(HArgs args)
{
	CheckArgs(argnames.length());
	if (thisdef == nullptr) {
		thisdef = new HLang(upperdef);
		thisdef->importclass("builtin", HPointer(new HBuiltin(thisdef)));
	}
	for (int i = 0; i < argnames.length(); i++)
		thisdef->importclass(argnames[i], args[i]);
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Function Running" << ColorClear;
	for (int i = 0; i < commands.length(); i++)
	{
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<[" << BULECOLOR << "START" << ColorClear << "]{" << SKYBLUECOLOR << commands[i] << ColorClear << "}";
		HCommand c = ResolveCommand(commands[i]);
		if (c._func != "return")
			runcode(ResolveCommand(commands[i]));
		else
		{
			HPointer p(thisdef->accessclass((c._args.length() > 0) ? c._args[0] : ""));
			this->resetdef();
			return p;
		}
		IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<[" << BULECOLOR << "DONE" << ColorClear << "]{" << SKYBLUECOLOR << commands[i] << ColorClear << "}";
	}
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Function Cleaning" << ColorClear;
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Function Finished" << ColorClear;
	return HPointer(new HVoid);
}

HPointer HFunction::copy(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->argnames = (HObjectHelper(args[0]).to<HFunction>()->argnames);
	this->commands = (HObjectHelper(args[0]).to<HFunction>()->commands);
	return HPointer(new HVoid);
}