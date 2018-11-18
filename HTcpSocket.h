#pragma once
#include "HObject.h"
#include <QTcpSocket>
class HTcpSocket :
	public HObject,
	public QTcpSocket
{
	H_OBJECT(HTcpSocket);
public:
	HTcpSocket();
	~HTcpSocket();
	HObject* setHost(HArgs args);
};
