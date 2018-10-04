#ifndef HOBJECT_H
#define HOBJECT_H

#include <QObject>
#include <QMap>
#include <functional>
#include "hargs.h"

class HObject : public QObject
{
	Q_OBJECT
public:
    explicit HObject(QObject *parent = nullptr) : QObject(parent) {

    }
    QMap<QString, std::function<HArgs(HArgs)>> map;
private:
};

#endif // HOBJECT_H
