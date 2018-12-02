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
		LMSG = QString(NONECOLOR) + "NONE" + QString(ColorClean);
		break;
	case HError::RT_NOTICE:
		LMSG = QString(NOTICECOLOR) + "NOTICE" + QString(ColorClean);
		break;
	case HError::RT_WARNING:
		LMSG = QString(WARNINGCOLOR) + "WARNING" + QString(ColorClean);
		break;
	case HError::RT_ERROR:
		LMSG = QString(ERRORCOLOR) + "ERROR" + QString(ColorClean);
		break;
	}
	qDebug() << QString("[" + LMSG + "]").toStdString().c_str() << WHYCOLOR << e.getWhy() << ColorClean;
}

void HFunction::runcode(HCommand cmd)
{
	if (thisdef == nullptr) {
		thisdef = new HLang(upperdef);
		thisdef->importclass("builtin", new HBuiltin(thisdef));
	}
	try {
		HArgs args;
		for (int x = 0; x < cmd._args.length(); x++)
			if (cmd._args[x].contains("\u0002"))
				for (int y = 0; y < cmd._argstrs.length(); y++)
					if (cmd._args[x].contains("\u0002" + QString(y)))
						args.insert(x, new HString(cmd._argstrs[y]));
					else;
			else {
				bool isit = false;
				int  toit = cmd._args[x].toInt(&isit);
				if (isit)
					args.insert(x, new HInt(toit));
				else
					if (cmd._args[x] == "true")
						args.insert(x, new HBool(true));
					else if (cmd._args[x] == "false")
						args.insert(x, new HBool(false));
					else if (cmd._args[x].isEmpty());
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
				aceobj->exec(cmd._func, args);
		else
			throw HError(HError::RT_ERROR, "Object Class Not Found");
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
	return;
}

HFunction::HFunction(HLang *upperdef)
{
	DefineMemberFunction("fromString", &HFunction::fromString);
	DefineMemberFunction("run", &HFunction::run);
	this->upperdef = upperdef;
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
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "Function Running" << ColorClean;
	for (int i = 0; i < commands.length(); i++)
	{
		RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<[" << DONECOLOR << "START" << ColorClean << "]{" << CDCOLOR << commands[i] << ColorClean << "}";
		runcode(ResolveCommand(commands[i]));
		RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<[" << DONECOLOR << "DONE" << ColorClean << "]{" << CDCOLOR << commands[i] << ColorClean << "}";
	}
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "Function Cleaning" << ColorClean;
	this->resetdef();
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "Function Finished" << ColorClean;
	return new HVoid;
}