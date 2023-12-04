#include "StringUtils.h"

namespace nc
{
	unsigned int StringUtils::id = 0;
	std::string StringUtils::ToUpper(std::string input)
	{
		std::string returnString = "";
		for (int i = 0; i < input.length(); i++)
		{
			returnString += toupper(input.at(i));
		}
		return returnString;
	}

	std::string StringUtils::ToLower(std::string input)
	{
		std::string returnString = "";
		for (int i = 0; i < input.length(); i++)
		{
			returnString += tolower(input.at(i));
		}
		return returnString;
	}
	bool StringUtils::IsEqualIgnoreCase(std::string s1, std::string s2)
	{
		return ToLower(s1) == ToLower(s2);
	}

	std::string StringUtils::CreateUnique(std::string input)
	{
		id++;
		return input + std::to_string(id);
	}

}
