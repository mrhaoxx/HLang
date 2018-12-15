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
	MDebug("Constructed");
}

QSharedPointer<HObject> HTcpSocket::hconnect(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HFunction);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "connected") {
		this->whenConnected = HObjectHelper(args[1]).to<HFunction>();
		return QSharedPointer<HObject>(new HVoid);
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "readyread") {
		this->whenReadyRead = HObjectHelper(args[1]).to<HFunction>();
		return QSharedPointer<HObject>(new HVoid);
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}

QSharedPointer<HObject> HTcpSocket::hdisconnect(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "connected") {
		this->whenConnected = nullptr;
		return QSharedPointer<HObject>(new HVoid);
	}
	else if (HObjectHelper(args[0]).to<HString>()->toQString() == "readyread") {
		this->whenReadyRead = nullptr;
		return QSharedPointer<HObject>(new HVoid);
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}

QSharedPointer<HObject> HTcpSocket::hconnectToHost(HArgs args)
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

QSharedPointer<HObject> HTcpSocket::send(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->write(HObjectHelper(args[0]).to<HString>()->toQString().toLatin1());
	this->flush();
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HTcpSocket::hreadAll(HArgs args)
{
	CheckArgs(0);
	return QSharedPointer<HObject>(new HString(this->readAll()));
}

QSharedPointer<HObject> HTcpSocket::hreadLine(HArgs args)
{
	CheckArgs(0);
	return QSharedPointer<HObject>(new HString(this->readLine()));
}
HTcpSocket::~HTcpSocket()
{
	MDebug("Destructed");
}