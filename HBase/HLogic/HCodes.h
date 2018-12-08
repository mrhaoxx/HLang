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
	QVector<std::tuple<QString, QStringList, QString>> FindDomain(QString whole);
	void LoadToFunction(QString name, QStringList argsn, QString cmds);
public:
	HCodes(HLang *uf = nullptr);
	HObject* fromString(HArgs args);
	HObject* run(HArgs args);
	HObject* getFunction(HArgs args);
	~HCodes();
};
