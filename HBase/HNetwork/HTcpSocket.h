#pragma once
#include "HObject.h"
#include <QTcpSocket>
#include "HData/HString.h"
#include "HData/HInt.h"
#include "HLogic/HFunction.h"
class HTcpSocket :
	public HObject,
	public QTcpSocket
{
	H_OBJECT(HTcpSocket);
public:
	HTcpSocket();
	~HTcpSocket();
	QSharedPointer<HObject> hconnect(HArgs args);
	QSharedPointer<HObject> hdisconnect(HArgs args);
	QSharedPointer<HObject> hconnectToHost(HArgs args);
	QSharedPointer<HObject> send(HArgs args);
	QSharedPointer<HObject> hreadAll(HArgs args);
	QSharedPointer<HObject> hreadLine(HArgs args);
private:
	QSharedPointer<HFunction> whenReadyRead = nullptr;
	QSharedPointer<HFunction> whenConnected = nullptr;
};
