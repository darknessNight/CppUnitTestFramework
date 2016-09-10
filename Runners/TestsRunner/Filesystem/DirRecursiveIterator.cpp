#include "DirRecursiveIterator.h"
#include <regex>

darknessNight::Filesystem::DirRecursiveIterator::DirRecursiveIterator(std::string parentPath)
:DirOneLevelIterator(parentPath)
{}

darknessNight::Filesystem::DirRecursiveIterator::DirRecursiveIterator()
	:DirOneLevelIterator()
{}

bool darknessNight::Filesystem::DirRecursiveIterator::nextFileExists() {
	if (systemIterator->findNextFileFromHandle() == 0) {
		return changeSearchDir();
	}
	return true;
}

bool darknessNight::Filesystem::DirRecursiveIterator::changeSearchDir() {
	while (dirs.size() > 0) {
		if (setNewSearchDir())
			return true;
	}
	return false;
}

bool darknessNight::Filesystem::DirRecursiveIterator::setNewSearchDir() {
	systemIterator->closeFind();
	if (systemIterator->findFirstFile(getNextDir())){
		return true;
		}
	return false;
}

std::string darknessNight::Filesystem::DirRecursiveIterator::getNextDir() {
	std::string path = dirs.front();
	dirs.pop_front();
	return path;
}

void darknessNight::Filesystem::DirRecursiveIterator::findNextFile() {
    addToListIfIsDir();
	DirOneLevelIterator::findNextFile();
}

void darknessNight::Filesystem::DirRecursiveIterator::addToListIfIsDir(){
    std::regex reg(".*\\/\\.{1,2}$");
	if (entry.isDir() && !std::regex_match(entry.getPath(), reg))
		dirs.push_back(entry.getPath() + "/");
}
