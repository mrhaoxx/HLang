#include "HCodes.h"

HCodes::HCodes(HLang *uf)
{
	DefineMemberFunction("run", &HCodes::run);
	DefineMemberFunction("fromString", &HCodes::fromString);
	DefineMemberFunction("getFunction", &HCodes::getFunction);
	this->upperdef = uf;
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
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "CodeBlocks Running" << ColorClean;
	for (int i = 0; i < domains.length(); i++)
	{
		RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "CodeBlocks Domain [" << CLASSCOLOR << domains[i] << NOTICECOLOR << "] Start" << ColorClean;
		domains[i]->run(args);
		RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "CodeBlocks Domain [" << CLASSCOLOR << domains[i] << NOTICECOLOR << "] Finished" << ColorClean;
	}
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "CodeBlocks Finished" << ColorClean;
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
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "CodeBlocks Deleting Domains {" << ColorClean;
	for (int i = 0; i < domains.length(); i++) {
		delete domains[i];
		RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << ERRORCOLOR << "Deleting " << domains[i] << ColorClean;
	}
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "}" << DONECOLOR << "[OK]" << ColorClean;
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
	RT_DEBUG << ">>" << ADDRESSCOLOR << (void*)this << ColorClean << "<<" << NOTICECOLOR << "CodeBlocks Loaded Domain [" << CLASSCOLOR << f << NOTICECOLOR << "]" << ColorClean;
}