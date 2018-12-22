#pragma once
#include "HObject.h"
#include <QWidget>
#include <QString>
#include <QVector>
class HLang
{
public:
	HLang(HLang* hl);
	~HLang();
	bool importclass(QString __name, HPointer __class);
	HWeakPointer accessclass(QString __name);
	void deleteclass(QString __name);
	int tmpused = 0;
	QMap<QString, HPointer>* dr();
private:
	HLang *higherlevel;
	QMap<QString, HPointer> classes;
};