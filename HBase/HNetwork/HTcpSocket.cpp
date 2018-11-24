#include "HTcpSocket.h"

HTcpSocket::HTcpSocket()
{
	DefineMemberFunction("connectToHost", &HTcpSocket::hconnectToHost);
	DefineMemberFunction("send", &HTcpSocket::send);
	DefineMemberFunction("connect", &HTcpSocket::hconnect);
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

HObject* HTcpSocket::hconnect(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HFunction);
	if (HObjectHelper(args[0]) == "connected") {
		this->whenConnected = HObjectHelper(args[1]).to<HFunction>();
		return new HRet(true);
	}
	else if (HObjectHelper(args[0]) == "readyread") {
		this->whenReadyRead = HObjectHelper(args[1]).to<HFunction>();
		return new HRet(true);
	}
	return new HRet(nullptr, false, WhyTcpSocketConnectSlotError);
}

HObject* HTcpSocket::hdisconnect(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]) == "connected") {
		this->whenConnected = nullptr;
		return new HRet(true);
	}
	else if (HObjectHelper(args[0]) == "readyread") {
		this->whenReadyRead = nullptr;
		return new HRet(true);
	}
	return new HRet(nullptr, false, WhyTcpSocketConnectSlotError);
}

HObject* HTcpSocket::hconnectToHost(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HInt);
	QString ret;
	if (whenReadyRead == nullptr)
		ret = WhyTcpSocketConnectWarring;
	this->connectToHost((QString)HObjectHelper(args[0]), (int)HObjectHelper(args[1]));
	return new HRet(nullptr, true, ret);
}

HObject* HTcpSocket::send(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->write(HObjectHelper(args[0]).operator QString().toLatin1());
	this->flush();
	return new HRet(true);
}