#include "HTcpSocket.h"
#include "HBaseInterface.h"
HTcpSocket::HTcpSocket()
{
}

HTcpSocket::~HTcpSocket()
{
}

HObject* HTcpSocket::setHost(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HInt);
}