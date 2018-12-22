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
	HPointer hconnect(HArgs args);
	HPointer hdisconnect(HArgs args);
	HPointer hconnectToHost(HArgs args);
	HPointer send(HArgs args);
	HPointer hreadAll(HArgs args);
	HPointer hreadLine(HArgs args);
private:
	QSharedPointer<HFunction> whenReadyRead = nullptr;
	QSharedPointer<HFunction> whenConnected = nullptr;
};
