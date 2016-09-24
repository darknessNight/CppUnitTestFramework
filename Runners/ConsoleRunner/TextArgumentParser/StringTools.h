#pragma once
#include <string>
#include <vector>
#include <array>

namespace darknessNight { namespace TextParser {
	class StringTools {
	public:
		static std::vector<std::string> split(std::string string, char delimiter);
		static std::array<std::string, 2> splitOnFirst(std::string string, char delimiter);
		static std::string trimWhitespace(std::string string);
		static std::string trimChar(std::string string, std::initializer_list<char> charsToTrim);
		static std::string trimCharAtEnd(std::string& string, std::initializer_list<char> charsToTrim);
		static std::string trimCharAtBegin(std::string& string, std::initializer_list<char> charsToTrim);
		static bool isOneFromChars(const char searchChar, std::initializer_list<char> patternChars);
		static std::string trim(std::string stringToTrim, std::string patternString);
		static std::string trimStringAtBegin(std::string stringToTrim, std::string patternString);
		static bool isBeginWith(std::string string, std::string patternString);
		static std::string trimStringAtEnd(std::string stringToTrim, std::string patternString);
		static bool isEndWith(std::string string, std::string patternString);
		static int beginWith(std::string string, std::vector<std::string> patternStrings);
		static int endWith(std::string string, std::vector<std::string> patternStrings);
	};
}}
