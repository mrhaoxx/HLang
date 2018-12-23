#pragma once
#include "HObject.h"
#include "HFunction.h"
#include <tuple>
class HClass :
	public HObject
{
	H_OBJECT(HClass);
	HLang* upperdef = nullptr;
	HLang* thisdef = nullptr;
	QVector<std::tuple<QString, QStringList, QString>> FindDomain(QString whole);
	void LoadToFunction(QString name, QStringList argsn, QString cmds);
public:
	HClass(HLang *uf = nullptr);
	HPointer fromString(HArgs args);
	HPointer run(HArgs args);
	HPointer getFunction(HArgs args);
	HPointer addVar(HArgs args);
	void setupthis(HPointer ptrtothis);
	~HClass();
};
