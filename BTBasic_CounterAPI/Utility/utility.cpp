#include "../Headers//lib.h"

void copyReturnString(const char* input, char* returnString)
{
	size_t sizeOfMessage = strlen(input) + 1;
	strcpy_s(returnString, sizeOfMessage, input);
}

std::vector<std::string> parse_C_style_str(char* input)
{
	bool stringIsParsed = false;
	std::vector<std::string> result;
	std::string inputStr = input;

	if (inputStr.empty())
	{
		return result;
	}

	std::string next = inputStr;
	std::string temp;
	size_t indexOfCurrentComma = 0;
	while (!stringIsParsed)
	{
		indexOfCurrentComma = next.find(",");

		if (indexOfCurrentComma == std::string::npos)
		{
			result.push_back(next);
			stringIsParsed = true;
		}
		else
		{
			temp = next.substr(0, indexOfCurrentComma);
			result.push_back(temp);

			next = next.substr(indexOfCurrentComma + 1, inputStr.size());
		}
	}
	return result;
}