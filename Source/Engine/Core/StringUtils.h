#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		static std::string ToUpper(std::string input);
		static std::string ToLower(std::string input);
		static bool IsEqualIgnoreCase(std::string s1, std::string s2);
		static std::string CreateUnique(std::string input);
	private:
		static unsigned int id;
	};

}