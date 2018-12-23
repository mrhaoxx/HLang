#include "HTcpSocket.h"

HTcpSocket::HTcpSocket()
{
	DefineMemberFunction(HTcpSocket, "connectToHost", &HTcpSocket::hconnectToHost);
	DefineMemberFunction(HTcpSocket, "send", &HTcpSocket::send);
	DefineMemberFunction(HTcpSocket, "connect", &HTcpSocket::hconnect);
	DefineMemberFunction(HTcpSocket, "readAll", &HTcpSocket::hreadAll);
	DefineMemberFunction(HTcpSocket, "readLine", &HTcpSocket::hreadLine);
	this->connect(this, &QTcpSocket::readyRead, this, [&] {
		if (whenReadyRead != nullptr)
			whenReadyRead->run(HArgs()).clear();
	});
	this->connect(this, &QTcpSocket::connected, this, [&] {
		if (whenConnected != nullptr)
			whenConnected->run(HArgs()).clear();
	});
}

HPointer HTcpSocket::hconnect(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HFunction);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "connected") {
		this->whenConnected = HObjectHelper(args[1]).to<HFunction>();
		return HPointer(new HVoid);
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "readyread") {
		this->whenReadyRead = HObjectHelper(args[1]).to<HFunction>();
		return HPointer(new HVoid);
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}

HPointer HTcpSocket::hdisconnect(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "connected") {
		this->whenConnected = nullptr;
		return HPointer(new HVoid);
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "readyread") {
		this->whenReadyRead = nullptr;
		return HPointer(new HVoid);
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}

HPointer HTcpSocket::hconnectToHost(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HInt);
	QString ret;
	if (whenReadyRead == nullptr)
		ret = WhyTcpSocketConnectWarring;
	this->connectToHost(HObjectHelper(args[0]).to<HString>()->toQString(), *HObjectHelper(args[1]).to<HInt>());
	throw HError(HError::RT_WARNING, WhyConnectSlotError);
}

HPointer HTcpSocket::send(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->write(HObjectHelper(args[0]).to<HString>()->toQString().toLatin1());
	this->flush();
	return HPointer(new HVoid);
}

HPointer HTcpSocket::hreadAll(HArgs args)
{
	CheckArgs(0);
	return HPointer(new HString(this->readAll()));
}

HPointer HTcpSocket::hreadLine(HArgs args)
{
	CheckArgs(0);
	return HPointer(new HString(this->readLine()));
}
HTcpSocket::~HTcpSocket()
{
}