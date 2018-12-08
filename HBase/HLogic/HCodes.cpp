#include "HCodes.h"

HCodes::HCodes(HLang *uf)
{
	DefineMemberFunction("run", &HCodes::run);
	DefineMemberFunction("fromString", &HCodes::fromString);
	DefineMemberFunction("getFunction", &HCodes::getFunction);
	this->upperdef = uf;
	MDebug("Constructed");
}

HObject* HCodes::fromString(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	QString w = (*HObjectHelper(args[0]).to<HString>());
	QStringList l = FindDomain(w);
	if (l.length() == 0)
		throw HError(HError::RT_WARNING, "No Blocks Found");
	for (int i = 0; i < l.length(); i++)
		LoadToFunction(l[i]);
	return new HVoid;
}

HObject* HCodes::run(HArgs args)
{
	CheckArgs(0);
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Running" << ColorClear;
	for (int i = 0; i < domains.length(); i++)
	{
		RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Domain [" << PURPLECOLOR << domains[i] << YELLOWCOLOR << "] Start" << ColorClear;
		domains[i]->run(args);
		RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Domain [" << PURPLECOLOR << domains[i] << YELLOWCOLOR << "] Finished" << ColorClear;
	}
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Finished" << ColorClear;
	return new HVoid;
}

HObject* HCodes::getFunction(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	return domains[*HObjectHelper(args[0]).to<HInt>()];
}

HCodes::~HCodes()
{
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Deleting Domains {" << ColorClear;
	for (int i = 0; i < domains.length(); i++) {
		delete domains[i];
		RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << REDCOLOR << "Deleting " << domains[i] << ColorClear;
	}
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "}" << BULECOLOR << "[OK]" << ColorClear;
	MDebug("Destructed");
}

QStringList HCodes::FindDomain(QString whole)
{
	QStringList domains;
	QString t = whole;
	while (t.contains("{") && t.contains("}") && t.length() >= 2)
	{
		int f = whole.indexOf("{");
		int l = whole.indexOf("}");
		QString s = t.mid(f + 1, l - f - 1);
		if (s != "")
			domains.push_back(s);
		t = t.mid(l + 1);
	}
	return domains;
}

void HCodes::LoadToFunction(QString cmds)
{
	HFunction *f = new  HFunction(upperdef);
	f->fromString(HArgs({ new HString(cmds) }));
	this->domains.push_back(f);
	RT_DEBUG << ">>" << HWHITECOLOR << (void*)this << ColorClear << "<<" << YELLOWCOLOR << "CodeBlocks Loaded Domain [" << PURPLECOLOR << f << YELLOWCOLOR << "]" << ColorClear;
}