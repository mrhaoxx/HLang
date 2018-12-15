#pragma once
#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
#include "HData/HBool.h"
#include "HData/HInt.h"
#include "HData/HString.h"
#include <memory>
class HLang
{
public:
	HLang(HLang* hl);
	~HLang();
	bool importclass(QString __name, QSharedPointer<HObject> __class);
	QSharedPointer<HObject> accessclass(QString __name);
	void deleteclass(QString __name);
	void IgnClass(QString __name);
	int tmpused = 0;
private:
	HLang *higherlevel;
	QMap<QString, QSharedPointer<HObject>> classes;
};