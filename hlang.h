#ifndef HLANG_H
#define HLANG_H

#include <QObject>
#include <QString>
#include "hobject.h"
#include "hargs.h"
#include "hvariable.h"
#include "hstdlib.h"

class HLang
{
public:
    HLang();
    void setCode(QStringList _code){code=_code;}
    QStringList getCode(){return code;}
    void run();
    void runline(QString);
private:
    QStringList code;
    QMap<QString,HObject*> map;

};

#endif // HLANG_H
