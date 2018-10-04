#ifndef HARGS_H
#define HARGS_H
#include <QObject>
#include <QString>

class HArgs
{
public:
    HArgs(QString data);
    QString operator()(){return data;}
private:
    QString data;
};

#endif // HARGS_H
