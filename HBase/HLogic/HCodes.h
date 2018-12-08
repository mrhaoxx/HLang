#pragma once
#include "HObject.h"
#include "HFunction.h"
#include <tuple>
class HCodes :
	public HObject
{
	H_OBJECT(HCodes);
	HLang* upperdef = nullptr;
	HLang* thisdef = nullptr;
	QVector<QPair<QString, QString>> FindDomain(QString whole);
	void LoadToFunction(QString name, QString cmds);
public:
	HCodes(HLang *uf = nullptr);
	HObject* fromString(HArgs args);
	HObject* run(HArgs args);
	HObject* getFunction(HArgs args);
	~HCodes();
};
