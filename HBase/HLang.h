#pragma once
#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
class HLang
{
public:
	HLang(HLang* hl, HWeakPointer ptrthis = HWeakPointer());
	~HLang();
	bool importclass(QString __name, HPointer __class);
	HPointer accessclass(QString __name);
	void deleteclass(QString __name);
	int tmpused = 0;
	QMap<QString, HPointer>* dr();
private:
	HWeakPointer ptrthis;
	HLang *higherlevel;
	QMap<QString, HPointer> classes;
};