#include "HObject.h"
namespace HLang {
	class HLANG_EXPORT HArgs :public std::vector<HObject*> {};
	class HLANG_EXPORT HFunction : public HObject {
		struct OneLine
		{ //A command Data
			bool is_function_or_class; // false:class;true:function
			std::string class_or_function_name_in_stack;
			std::string member_function_name;
			std::vector<std::string> args;
		};
		void ExecOneLine(OneLine ol, memorystack* stk);
	public:
		HFunction(std::vector<std::pair<std::string/*name*/, std::string/*type*/>> args);
		std::string Type() { return "function"; }
		HArgs Execute(HArgs args);
	private:
		std::vector<std::pair<std::string/*name*/, std::string/*type*/>> arg_info;
		std::vector<OneLine> commands;
		memorystack* rt = nullptr;
	};
}