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
	MDebug("Destructed");
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
	qDebug() << QString("[" + LMSG + "]").toStdString().c_str() << BWCOLOR << e.getWhy() << ColorClear;
}

void HFunction::runcode(HCommand cmd)
{
	HArgs waitdelete;
	if (thisdef == nullptr) {
		thisdef = new HLang(upperdef);
		thisdef->importclass("builtin", new HBuiltin(thisdef));
	}
	try {
		HArgs args;
		for (int x = 0; x < cmd._args.length(); x++)
			if (cmd._args[x].contains("\u0002"))
				for (int y = 0; y < cmd._argstrs.length(); y++)
					if (cmd._args[x].contains("\u0002" + QString(y))) {
						HObject* handle = new HString(cmd._argstrs[y]);
						args.insert(x, handle);
						waitdelete.append(handle);
					}
					else;
			else {
				bool isit = false;
				int  toit = cmd._args[x].toInt(&isit);
				if (isit) {
					HObject* h = new HInt(toit);
					args.insert(x, h);
					waitdelete.append(h);
				}
				else
					if (cmd._args[x] == "true") {
						HObject* h = new HBool(true);
						args.insert(x, h);
						waitdelete.append(h);
					}
					else if (cmd._args[x] == "false") {
						HObject* h = new HBool(false);
						args.insert(x, h);
						waitdelete.append(h);
					}
					else if (cmd._args[x].isEmpty()) {
						HObject* h = new HVoid;
						args.insert(x, h);
						waitdelete.append(h);
					}
					else
					{
						HObject *arg = thisdef->accessclass(cmd._args[x]);
						if (arg == nullptr)
							throw HError(HError::RT_ERROR, "Args Class Not Find");
						else
							args.insert(x, arg);
					}
			}
		HObject* aceobj = thisdef->accessclass(cmd._class);
		if (aceobj != nullptr)
			if (!cmd._backvalue_name.isEmpty())
				thisdef->importclass(cmd._backvalue_name, aceobj->exec(cmd._func, args));
			else
				delete aceobj->exec(cmd._func, args);
		else
			throw HError(HError::RT_ERROR, "Object Class Not Found");
	}
	catch (HError& e)
	{
		CoutMsg(e);
	}
	for (int i = 0; i < waitdelete.length(); i++)
		delete waitdelete[i];
}

void HFunction::resetdef()
{
	if (thisdef == nullptr)
		return;
	delete thisdef;
	return;
}

HFunction::HFunction(HLang *upperdef)
{
	DefineMemberFunction("fromString", &HFunction::fromString);
	DefineMemberFunction("run", &HFunction::run);
	this->upperdef = upperdef;
	MDebug("Constructed");
}

HObject* HFunction::fromString(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->commands = SplitCommands(*HObjectHelper(args[0]).to<HString>());
	return new HVoid;
}

HObject* HFunction::run(HArgs args)
{
	CheckArgs(0);
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Function Running" << ColorClear;
	for (int i = 0; i < commands.length(); i++)
	{
		RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<[" << BULECOLOR << "START" << ColorClear << "]{" << SKYBLUECOLOR << commands[i] << ColorClear << "}";
		HCommand c = ResolveCommand(commands[i]);
		IndentAdd;
		if (c._func != "return")
			runcode(ResolveCommand(commands[i]));
		else
		{
			HObject* o = thisdef->accessclass((c._args.length() > 0) ? c._args[0] : "");
			thisdef->IgnClass((c._args.length() > 0) ? c._args[0] : "");
			return o;
		}
		IndentRem;
		RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<[" << BULECOLOR << "DONE" << ColorClear << "]{" << SKYBLUECOLOR << commands[i] << ColorClear << "}";
	}
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Function Cleaning" << ColorClear;
	this->resetdef();
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Function Finished" << ColorClear;
	return new HVoid;
}