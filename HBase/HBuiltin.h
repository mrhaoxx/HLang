#pragma once
#include "HObject.h"
#include "HLang.h"
#include "HWindow.h"
#include "HPushButton.h"
#include "HLang.h"
#include "HData/HBool.h"
#include "HData/HInt.h"
#include "HData/HString.h"
#include "HLogic/HFunction.h"
#include "HLogic/HIf.h"
#include "HNetwork/HTcpSocket.h"
class HBuiltin :
	public HObject
{
	H_OBJECT(HBuiltin)
public:
	HBuiltin();
	HObject* newclass(HArgs args);
	HObject* deleteclass(HArgs args);
	HObject* sleep(HArgs args);
	HObject* system(HArgs args);
	HObject* msg(HArgs args);
	HObject* cout(HArgs args);
	HLang* HDef = HMain;
};
