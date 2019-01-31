#include "HFunction.h"

void HLang::HFunction::ExecOneLine(OneLine ol, memorystack* stk)
{
}

HLang::HFunction::HFunction(std::vector<std::pair<std::string/*name*/, std::string/*type*/>> args)
{
	this->arg_info = args;
}

HLang::HArgs HLang::HFunction::Execute(HArgs args)
{
	this->rt = new memorystack;
	//CheckArgsType && SaveArgsToStack
	if (args.size() == arg_info.size())
		for (int i = 0; i < (int)args.size(); i++)
			if (args[i]->Type() != arg_info[i].second)
			{
				delete rt;
				return HArgs();
			}
			else
				this->rt->Save(arg_info[i].first, args[i]);
	//Start To Exec
}