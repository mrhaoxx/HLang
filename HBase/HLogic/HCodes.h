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
	QSharedPointer<HObject> fromString(HArgs args);
	QSharedPointer<HObject> run(HArgs args);
	QSharedPointer<HObject> getFunction(HArgs args);
	~HCodes();
};
