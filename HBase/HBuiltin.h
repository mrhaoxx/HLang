#pragma once
#include "HObject.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HLang.h"
#include "HData/HBool.h"
#include "HData/HInt.h"
#include "HData/HString.h"
#include "HData/HVoid.h"
#include "HLogic/HFunction.h"
#include "HLogic/HIf.h"
#include "HLogic/HCodes.h"
#include "HNetwork/HTcpSocket.h"
#include <QThread>
class HBuiltin :
	public HObject
{
	H_OBJECT(HBuiltin)
public:
	HBuiltin(HLang* def);
	QSharedPointer<HObject> newclass(HArgs args);
	QSharedPointer<HObject> deleteclass(HArgs args);
	QSharedPointer<HObject> sleep(HArgs args);
	QSharedPointer<HObject> system(HArgs args);
	QSharedPointer<HObject> msg(HArgs args);
	QSharedPointer<HObject> cout(HArgs args);
	QSharedPointer<HObject> termimate(HArgs args);
	QSharedPointer<HObject> keepexec(HArgs args);
	QSharedPointer<HObject> quit(HArgs args);
	QSharedPointer<HObject> ret(HArgs args);
	QSharedPointer<HObject> setdebug(HArgs args);
	QSharedPointer<HObject> aboutQt(HArgs args);
	HLang* HDef;
};
