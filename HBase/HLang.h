#pragma once
#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
#include <QPair>
class HLang
{
public:
	HLang(HLang* hl);
	~HLang();
	bool importclass(QString __name, HPointer __class, bool own = true);
	HWeakPointer accessclass(QString __name);
	void deleteclass(QString __name);
	int tmpused = 0;
private:
	HLang *higherlevel;
	QMap<QString, QPair<HPointer, HWeakPointer>> classes;
};