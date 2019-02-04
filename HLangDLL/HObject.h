#include <vector>
#include <string>
#include <map>
#include <variant>
#define HLANG_EXPORT __declspec(dllexport)
namespace HLang {
	typedef std::variant<int, bool, std::string, char> HLANG_DATA;
	class HLANG_EXPORT HObject {
	public:
		HObject() {}
		virtual ~HObject() {}
		virtual std::string Type(void) = 0;
	};
	class HLANG_EXPORT memorystack {
	public:
		bool Save(std::string name, HObject* ptr);
		HObject* Read(std::string name);
		void Delete(std::string name);
	private:
		std::map<std::string, HObject*> data;
	};
}