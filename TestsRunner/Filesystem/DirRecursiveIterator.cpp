#include "DirRecursiveIterator.h"
#include <Windows.h>
#include <regex>

darknessNight::Filesystem::DirRecursiveIterator::DirRecursiveIterator(HANDLE handle, Entry & entry, std::string parentPath)
:DirOneLevelIterator(handle, entry,parentPath)
{
}

darknessNight::Filesystem::DirRecursiveIterator::DirRecursiveIterator(Entry & entry) 
	:DirOneLevelIterator(entry) 
{}

bool darknessNight::Filesystem::DirRecursiveIterator::nextFileExists(WIN32_FIND_DATAA & ffd) {
	if (FindNextFileA(handle, &ffd) == 0) {
		return changeSearchDir(ffd);
	}
	return true;
}

bool darknessNight::Filesystem::DirRecursiveIterator::changeSearchDir(WIN32_FIND_DATAA & ffd) {
	if (dirs.size() > 0) {
		FindClose(handle);
		return setNewSearchDir(ffd);
	}
	return false;
}

bool darknessNight::Filesystem::DirRecursiveIterator::setNewSearchDir(WIN32_FIND_DATAA & ffd) {
	handle = FindFirstFileA((dirs.front() + "*").c_str(), &ffd);
	if (handle != nullptr) {
		setNewParentPrefixAndRemoveDirFromList();
		return true;
	}
	return false;
}

void darknessNight::Filesystem::DirRecursiveIterator::setNewParentPrefixAndRemoveDirFromList() {
	parentPath = dirs.front();
	dirs.pop_front();
}

void darknessNight::Filesystem::DirRecursiveIterator::getNextFile(WIN32_FIND_DATAA & ffd) {
	DirOneLevelIterator::getNextFile(ffd);
	std::regex reg(".*\\/\\.{1,2}$");
	if (entry.isDir() && !std::regex_match(entry.getPath(),reg))
		dirs.push_back(entry.getPath() + "/");
}
