#pragma once
#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
#include "HData/HBool.h"
#include "HData/HInt.h"
#include "HData/HString.h"
class HLang
{
public:
	HLang(HLang* hl);
	~HLang();
	bool importclass(QString __name, HObject* __class);
	HObject* accessclass(QString __name);
	void deleteclass(QString __name);
	int tmpused = 0;
private:
	HLang *higherlevel;
	QMap<QString, HObject*> classes;
};