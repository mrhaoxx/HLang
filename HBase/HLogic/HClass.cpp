#include "HClass.h"

HClass::HClass(HLang *uf)
{
	DefineMemberFunction(HClass, "run", &HClass::run);
	DefineMemberFunction(HClass, "fromString", &HClass::fromString);
	DefineMemberFunction(HClass, "addvar", &HClass::addVar);
	this->upperdef = uf;
	this->thisdef = new HLang(upperdef);
	MDebug("Constructed");
}

HPointer HClass::fromString(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	QString w = (*HObjectHelper(args[0]).to<HString>());
	QVector<std::tuple<QString, QStringList, QString>> l = FindDomain(w);
	if (l.length() == 0)
		throw HError(HError::RT_WARNING, "No Function Found");
	RT_DEBUG << YELLOWCOLOR << "Functions:" << ColorClear;
	for (int i = 0; i < l.length(); i++)
		LoadToFunction(std::get<0>(l[i]), std::get<1>(l[i]), std::get<2>(l[i]));
	return HPointer(new HVoid);
}

HPointer HClass::run(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Class Running" << ColorClear;
	RT_DEBUG << YELLOWCOLOR << "[" << HObjectHelper(args[0]).to<HString>()->toQString() << "] Function Start" << ColorClear;
	if (thisdef->accessclass(HObjectHelper(args[0]).to<HString>()->toQString()) != nullptr) {
		RT_DEBUG << "{";
		IndentAdd;
		thisdef->accessclass(HObjectHelper(args[0]).to<HString>()->toQString()).toStrongRef()->exec("run", HArgs()).clear();
		IndentRem;
		RT_DEBUG << "}";
	}
	else
		throw HError(HError::RT_NOTICE, "No " + HObjectHelper(args[0]).to<HString>()->toQString() + " Function Found");
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Finished" << ColorClear;
	return HPointer(new HVoid);
}

HPointer HClass::addVar(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HObject);
	this->thisdef->importclass(HObjectHelper(args[0]).to<HString>()->toQString(), args[1]);
	return HPointer(new HVoid);
}

HClass::~HClass()
{
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Cleaning" << ColorClear;
	delete thisdef;
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Destructed" << ColorClear;
	MDebug("Destructed");
}

QVector<std::tuple<QString, QStringList, QString>> HClass::FindDomain(QString whole)
{
	QVector<std::tuple<QString, QStringList, QString>> domains;
	QString t = whole;
	while (t.contains("{") && t.contains("}") && t.length() >= 2)
	{
		QString name = t.split("{")[0];
		QString s = t.split("{")[1].split("}")[0];
		QStringList argnames = (name.split("(").length() > 1) ? name.split("(")[1].chopped(1).split(",") : QStringList();
		for (int i = 0; i < argnames.length(); i++)
			if (argnames[i].simplified() == "")argnames.removeAt(i);
		name = name.split("(")[0];
		if (s != "")
			domains.append(std::tuple<QString, QStringList, QString>(name, argnames, s));
		t = t.mid(t.indexOf("}") + 1);
	}
	return domains;
}

void HClass::LoadToFunction(QString name, QStringList argsn, QString cmds)
{
	HPointer f(new HFunction(thisdef, argsn));
	f->exec("fromString", (HArgs({ HPointer(new HString(cmds)) }))).clear();
	this->thisdef->importclass(name, f);
	IS_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "Class Loaded Function [" << PURPLECOLOR << name << YELLOWCOLOR << "]" << ColorClear;
	RT_DEBUG << name.toStdString().c_str() << "(" << argsn.join(",").toStdString().c_str() << ")" << "{";
	IndentAdd;
	QStringList e = HFunction::SplitCommands(cmds);
	for (int i = 0; i < e.length(); i++)
		RT_DEBUG << e[i].toStdString().c_str() << ";";
	IndentRem;
	RT_DEBUG << "}";
}