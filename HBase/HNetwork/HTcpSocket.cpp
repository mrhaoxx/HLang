#include "HTcpSocket.h"

HTcpSocket::HTcpSocket()
{
	DefineMemberFunction("connectToHost", &HTcpSocket::hconnectToHost);
	DefineMemberFunction("send", &HTcpSocket::send);
	DefineMemberFunction("setConnectedSlot", &HTcpSocket::setConnected);
	DefineMemberFunction("setReadyReadSlot", &HTcpSocket::setReadReady);
	DefineMemberFunction("unsetReadyReadSlot", &HTcpSocket::unsetConnectReadReady);
	DefineMemberFunction("unsetConnectedSlot", &HTcpSocket::unsetConnectConnected);
	DefineMemberFunction("unsetReadyReadSlotArgs", &HTcpSocket::unsetConnectReadReadyArgs);
	DefineMemberFunction("unsetConnectedSlotArgs", &HTcpSocket::unsetConnectConnectedArgs);
	DefineMemberFunction("setConnectedSlotArgs", &HTcpSocket::setConnectedArgs);
	DefineMemberFunction("setReadyReadSlotArgs", &HTcpSocket::setConnectedArgs);
	this->connect(this, &QTcpSocket::readyRead, this, [&] {
		HArgs *args = (whenReadyReadArgs == nullptr) ? new HArgs : whenReadyReadArgs;
		args->push_back(new HString(new QString(this->readLine())));
		if (whenReadyRead != nullptr)
			whenReadyRead->hexec(*args);
	});
	this->connect(this, &QTcpSocket::connected, this, [&] {
		if (whenConnected != nullptr)
			whenConnected->hexec((whenConnectedArgs == nullptr) ? HArgs() : *whenConnectedArgs);
	});
}

HTcpSocket::~HTcpSocket()
{
}

HObject* HTcpSocket::setConnected(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->whenConnected = HObjectHelper(args[0]).to<HFunction>();
	return new HRet(true);
}
HObject* HTcpSocket::setReadReady(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	this->whenReadyRead = HObjectHelper(args[0]).to<HFunction>();
	return new HRet(true);
}
HObject* HTcpSocket::setReadReadyArgs(HArgs args)
{
	this->whenReadyReadArgs = new HArgs(args);
	return new HRet(true);
}
HObject* HTcpSocket::setConnectedArgs(HArgs args)
{
	this->whenConnectedArgs = new HArgs(args);
	return new HRet(true);
}
HObject* HTcpSocket::unsetConnectReadReady(HArgs args)
{
	CheckArgs(0);
	this->whenReadyRead = nullptr;
	return new HRet(true);
}
HObject* HTcpSocket::unsetConnectConnected(HArgs args)
{
	CheckArgs(0);
	this->whenConnected = nullptr;
	return new HRet(true);
}
HObject* HTcpSocket::unsetConnectReadReadyArgs(HArgs args)
{
	CheckArgs(0);
	this->whenReadyReadArgs = nullptr;
	return new HRet(true);
}
HObject* HTcpSocket::unsetConnectConnectedArgs(HArgs args)
{
	CheckArgs(0);
	this->whenConnectedArgs = nullptr;
	return new HRet(true);
}
HObject* HTcpSocket::hconnectToHost(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HInt);
	QString ret;
	if (whenReadyRead == nullptr)
		ret = WhyTcpSocketConnectWarring;
	this->connectToHost(HObjectHelper(args[0]).to<HString>()->toQString(), *HObjectHelper(args[1]).to<HInt>()->value());
	return new HRet(nullptr, true, ret);
}

HObject* HTcpSocket::send(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->write(HObjectHelper(args[0]).to<HString>()->toQString().toLatin1());
	this->write("\r\n");
	return new HRet(true);
}