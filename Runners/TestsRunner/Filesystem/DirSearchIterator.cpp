#include "DirSearchIterator.h"
#include <regex>

darknessNight::Filesystem::DirSearchIterator::DirSearchIterator(std::string parentPath, std::string pattern)
	:DirRecursiveIterator(parentPath), searchRegex(pattern) {
	findFirstMatchedEntry();
}

void darknessNight::Filesystem::DirSearchIterator::findFirstMatchedEntry() {
	if (!matchPattern(entry.getPath()))
		findNextFile();
}

darknessNight::Filesystem::DirSearchIterator::DirSearchIterator()
	: DirRecursiveIterator() {
}

void darknessNight::Filesystem::DirSearchIterator::findNextFile() {
	do {
		DirRecursiveIterator::findNextFile();
	} while (entryNotMatchAndCanSearch());
}

bool darknessNight::Filesystem::DirSearchIterator::entryNotMatchAndCanSearch() {
	return !isEnded() && !matchPattern(entry.getPath());
}

bool darknessNight::Filesystem::DirSearchIterator::matchPattern(std::string str) {
	return std::regex_match(str, searchRegex);
}