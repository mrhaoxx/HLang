#pragma once
#include "HObject.h"
#include "HFunction.h"
#include <tuple>
class HCodes :
	public HObject
{
	H_OBJECT(HCodes);
	HLang* upperdef = nullptr;
	QVector<HFunction*> domains;
	QStringList FindDomain(QString whole);
	void LoadToFunction(QString cmds);
public:
	HCodes(HLang *uf = nullptr);
	HObject* fromString(HArgs args);
	HObject* run(HArgs args);
	HObject* getFunction(HArgs args);
	~HCodes();
};
