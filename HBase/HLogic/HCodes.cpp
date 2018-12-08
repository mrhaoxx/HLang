#include "HCodes.h"

HCodes::HCodes(HLang *uf)
{
	DefineMemberFunction("run", &HCodes::run);
	DefineMemberFunction("fromString", &HCodes::fromString);
	this->upperdef = uf;
	this->thisdef = new HLang(upperdef);
	MDebug("Constructed");
}

HObject* HCodes::fromString(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	QString w = (*HObjectHelper(args[0]).to<HString>());
	QVector<std::tuple<QString, QStringList, QString>> l = FindDomain(w);
	if (l.length() == 0)
		throw HError(HError::RT_WARNING, "No Blocks Found");
	for (int i = 0; i < l.length(); i++)
		LoadToFunction(std::get<0>(l[i]), std::get<1>(l[i]), std::get<2>(l[i]));
	return new HVoid;
}

HObject* HCodes::run(HArgs args)
{
	CheckArgs(0);
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Running" << ColorClear;
	if (thisdef->accessclass("main") != nullptr) {
		IndentAdd;
		delete thisdef->accessclass("main")->exec("run", HArgs());
		IndentRem;
	}
	else
		throw HError(HError::RT_NOTICE, "No Main Function Found");
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Finished" << ColorClear;
	return new HVoid;
}

HCodes::~HCodes()
{
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Cleaning" << ColorClear;
	delete thisdef;
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Destructed" << ColorClear;
	MDebug("Destructed");
}

QVector<std::tuple<QString, QStringList, QString>> HCodes::FindDomain(QString whole)
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

void HCodes::LoadToFunction(QString name, QStringList argsn, QString cmds)
{
	HFunction *f = new  HFunction(thisdef, argsn);
	HObject * w = new HString(cmds);
	delete f->fromString(HArgs({ w }));
	this->thisdef->importclass(name, f);
	delete w;
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Loaded Domain [" << PURPLECOLOR << name << YELLOWCOLOR << "]" << ColorClear;
}