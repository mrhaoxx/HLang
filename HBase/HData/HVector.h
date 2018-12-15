#pragma once
#include "HObject.h"
template<typename T>
class HVector :
	public HObject
{
	H_OBJECT(HVector);
	QVector <QSharedPointer<T>> *data;
public:
	HVector();
	QSharedPointer<HObject> insert(HArgs args);
	QSharedPointer<HObject> get(HArgs args);
};

template<typename T>
inline HVector<T>::HVector()
{
	data = new QVector<QSharedPointer<T>>;
}

template<typename T>
inline QSharedPointer<HObject> HVector<T>::insert(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, T);
	this->data->insert(args[0]);
	return QSharedPointer<HObject>(new HVoid);
}

template<typename T>
inline QSharedPointer<HObject> HVector<T>::get(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HInt);
	return data[HObjectHelper(args[0]).to<HInt>()->value()];
}
