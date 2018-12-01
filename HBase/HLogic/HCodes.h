#pragma once
#include "HObject.h"
#include "HFunction.h"
#include <tuple>
class HCodes :
	public HObject
{
	H_OBJECT(HCodes);
	HLang* upperdef;
	QVector<QPair<HFunction*, QString>> domains;
	QStringList FindDomain(QString whole);
public:
	HCodes(HLang *uf);
	HObject* fromString(HArgs args);
	HObject* doFucntion(HArgs args);
	~HCodes();
};
