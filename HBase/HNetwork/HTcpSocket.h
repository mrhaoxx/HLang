#pragma once
#include "HObject.h"
#include <QTcpSocket>
#include "HFunction.h"
class HTcpSocket :
	public HObject,
	public QTcpSocket
{
	H_OBJECT(HTcpSocket);
public:
	HTcpSocket();
	~HTcpSocket();
	HObject* setConnected(HArgs args);
	HObject* setReadReady(HArgs args);
	HObject* setReadReadyArgs(HArgs args);
	HObject* setConnectedArgs(HArgs args);
	HObject* unsetConnectReadReady(HArgs args);
	HObject* unsetConnectConnected(HArgs args);
	HObject* unsetConnectReadReadyArgs(HArgs args);
	HObject* unsetConnectConnectedArgs(HArgs args);
	HObject* hconnectToHost(HArgs args);
	HObject* send(HArgs args);
private:
	HFunction* whenReadyRead = nullptr;
	HArgs* whenReadyReadArgs = nullptr;
	HFunction* whenConnected = nullptr;
	HArgs* whenConnectedArgs = nullptr;
};
