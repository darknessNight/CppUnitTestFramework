#include "StringTools.h"

 std::vector<std::string> darknessNight::TextParser::StringTools::split(std::string string, char delimiter) {
	std::vector<std::string> array;
	int pos = string.find(delimiter);
	while (pos >= 0) {
		array.push_back(string.substr(0, pos));
		string = string.substr(pos + 1, string.size() - pos);
		pos = string.find(delimiter);
	}
	array.push_back(string);
	return array;
}

 std::array<std::string, 2> darknessNight::TextParser::StringTools::splitOnFirst(std::string string, char delimiter) {
	std::array<std::string, 2> array;
	int pos = string.find(delimiter);
	if (pos >= 0) {
		array[0] = string.substr(0, pos);
		array[1] = string.substr(pos + 1, string.size() - pos);
	} else
		array[0] = string;
	return array;
}

 std::string darknessNight::TextParser::StringTools::trimWhitespace(std::string string) {
	return trimChar(string, { ' ','\t','\n','\r' });
}

 std::string darknessNight::TextParser::StringTools::trimChar(std::string string, std::initializer_list<char> charsToTrim) {
	string = trimCharAtBegin(string, charsToTrim);
	string = trimCharAtEnd(string, charsToTrim);
	return string;
}

 std::string darknessNight::TextParser::StringTools::trimCharAtEnd(std::string& string, std::initializer_list<char> charsToTrim) {
	int i = string.size() - 1;
	while (i >= 0 && isOneFromChars(string[i], charsToTrim))
		i--;
	return string.substr(0, i + 1);
}

 std::string darknessNight::TextParser::StringTools::trimCharAtBegin(std::string& string, std::initializer_list<char> charsToTrim) {
	int i = 0;
	while (string.size() > i && isOneFromChars(string[i], charsToTrim))
		i++;
	return string.substr(i, string.size() - i);
}

 bool darknessNight::TextParser::StringTools::isOneFromChars(const char searchChar, std::initializer_list<char> patternChars) {
	for (auto ch : patternChars)
		if (searchChar == ch)
			return true;
	return false;
}

 std::string darknessNight::TextParser::StringTools::trim(std::string stringToTrim, std::string patternString) {
	stringToTrim = trimStringAtBegin(stringToTrim, patternString);
	stringToTrim = trimStringAtEnd(stringToTrim, patternString);
	return stringToTrim;
}

 std::string darknessNight::TextParser::StringTools::trimStringAtBegin(std::string stringToTrim, std::string patternString) {
	while (isBeginWith(stringToTrim, patternString))
		stringToTrim = stringToTrim.substr(patternString.size(), stringToTrim.size() - patternString.size());
	return stringToTrim;
}

 bool darknessNight::TextParser::StringTools::isBeginWith(std::string string, std::string patternString) {
	return static_cast<int>(string.find(patternString)) == 0;
}

 std::string darknessNight::TextParser::StringTools::trimStringAtEnd(std::string stringToTrim, std::string patternString) {
	while (isEndWith(stringToTrim, patternString))
		stringToTrim = stringToTrim.substr(0, stringToTrim.size() - patternString.size());
	return stringToTrim;
}

 bool darknessNight::TextParser::StringTools::isEndWith(std::string string, std::string patternString) {
	return static_cast<int>(string.find(patternString)) == string.size() - patternString.size();
}

 int darknessNight::TextParser::StringTools::beginWith(std::string string, std::vector<std::string> patternStrings) {
	for (auto i = 0; i < patternStrings.size(); i++)
		if (isBeginWith(string, patternStrings[i]))
			return i;
	return -1;
}

 int darknessNight::TextParser::StringTools::endWith(std::string string, std::vector<std::string> patternStrings) {
	for (auto i = 0; i < patternStrings.size(); i++)
		if (isEndWith(string, patternStrings[i]))
			return i;
	return -1;
}
