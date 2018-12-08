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
	QVector<QPair<QString, QString>> l = FindDomain(w);
	if (l.length() == 0)
		throw HError(HError::RT_WARNING, "No Blocks Found");
	for (int i = 0; i < l.length(); i++)
		LoadToFunction(l[i].first, l[i].second);
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
	delete thisdef;
	MDebug("Destructed");
}

QVector<QPair<QString, QString>> HCodes::FindDomain(QString whole)
{
	QVector<QPair<QString, QString>> domains;
	QString t = whole;
	while (t.contains("{") && t.contains("}") && t.length() >= 2)
	{
		QString name = t.split("{")[0];
		QString s = t.split("{")[1].split("}")[0];
		if (s != "")
			domains.append(QPair<QString, QString>(name, s));
		t = t.mid(t.indexOf("}") + 1);
	}
	return domains;
}

void HCodes::LoadToFunction(QString name, QString cmds)
{
	HFunction *f = new  HFunction(thisdef);
	HObject * w = new HString(cmds);
	delete f->fromString(HArgs({ w }));
	this->thisdef->importclass(name, f);
	delete w;
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Loaded Domain [" << PURPLECOLOR << name << YELLOWCOLOR << "]" << ColorClear;
}