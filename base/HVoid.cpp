#include "HVoid.h"
HLang::HVoid::HVoid() {};
std::vector<std::string> split(std::string str, std::string pat) {
	std::vector<std::string> bufStr;

	while (true)
	{
		int index = (int)str.find(pat);

		std::string subStr = str.substr(0, index);
		if (!subStr.empty())
			bufStr.push_back(subStr);

		str.erase(0, index + pat.size());

		if (index == -1)
			break;
	}
	return bufStr;
}