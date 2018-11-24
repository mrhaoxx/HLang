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
	HObject* hconnect(HArgs args);
	HObject* hdisconnect(HArgs args);
	HObject* hconnectToHost(HArgs args);
	HObject* send(HArgs args);
	HObject* hreadAll(HArgs args);
	HObject* hreadLine(HArgs args);
private:
	HFunction* whenReadyRead = nullptr;
	HFunction* whenConnected = nullptr;
};
