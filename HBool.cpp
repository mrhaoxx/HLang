#include "HBool.h"
#include "HBaseInterface.h"
H_MemberFunction_def(set, HBool)
{
	CheckArgs(1);
	SetupArgs;
	if (GetArg(0) == "true")
		data = true;
	else if (GetArg(0) == "false")
		data = false;
	return new HBool(true);
}