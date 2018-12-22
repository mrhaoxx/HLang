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
#include "HLogic/HClass.h"
#include "HNetwork/HTcpSocket.h"
#include <QThread>
class HBuiltin :
	public HObject
{
	H_OBJECT(HBuiltin)
public:
	HBuiltin(HLang* def);
	HPointer newclass(HArgs args);
	HPointer deleteclass(HArgs args);
	HPointer sleep(HArgs args);
	HPointer system(HArgs args);
	HPointer msg(HArgs args);
	HPointer cout(HArgs args);
	HPointer termimate(HArgs args);
	HPointer keepexec(HArgs args);
	HPointer quit(HArgs args);
	HPointer ret(HArgs args);
	HPointer setdebug(HArgs args);
	HPointer aboutQt(HArgs args);
	HLang* HDef;
};
