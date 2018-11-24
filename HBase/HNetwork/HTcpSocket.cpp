#include "HTcpSocket.h"

HTcpSocket::HTcpSocket()
{
	DefineMemberFunction("connectToHost", &HTcpSocket::hconnectToHost);
	DefineMemberFunction("send", &HTcpSocket::send);
	DefineMemberFunction("connect", &HTcpSocket::hconnect);
	DefineMemberFunction("readAll", &HTcpSocket::hreadAll);
	DefineMemberFunction("readLine", &HTcpSocket::hreadLine);
	this->connect(this, &QTcpSocket::readyRead, this, [&] {
		HArgs *args = new HArgs;
		args->push_front(this);
		if (whenReadyRead != nullptr)
			whenReadyRead->hexec(*args);
	});
	this->connect(this, &QTcpSocket::connected, this, [&] {
		HArgs args;
		args.push_front(this);
		if (whenConnected != nullptr)
			whenConnected->hexec(args);
	});
}

HObject* HTcpSocket::hconnect(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HFunction);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "connected") {
		this->whenConnected = HObjectHelper(args[1]).to<HFunction>();
		return new HRet(true);
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "readyread") {
		this->whenReadyRead = HObjectHelper(args[1]).to<HFunction>();
		return new HRet(true);
	}
	return new HRet(nullptr, false, WhyTcpSocketConnectSlotError);
}

HObject* HTcpSocket::hdisconnect(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "connected") {
		this->whenConnected = nullptr;
		return new HRet(true);
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "readyread") {
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
	this->connectToHost(HObjectHelper(args[0]).to<HString>()->toQString(), *HObjectHelper(args[1]).to<HInt>()->value());
	return new HRet(nullptr, true, ret);
}

HObject* HTcpSocket::send(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->write(HObjectHelper(args[0]).to<HString>()->toQString().toLatin1());
	this->flush();
	return new HRet(true);
}

HObject* HTcpSocket::hreadAll(HArgs args)
{
	CheckArgs(0);
	return new HRet(new HString(new QString(this->readAll())));
}

HObject* HTcpSocket::hreadLine(HArgs args)
{
	CheckArgs(0);
	return new HRet(new HString(new QString(this->readLine())));
}