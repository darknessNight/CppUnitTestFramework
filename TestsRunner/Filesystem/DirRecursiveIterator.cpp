#include "DirRecursiveIterator.h"

darknessNight::Filesystem::DirRecursiveIterator::DirRecursiveIterator(HANDLE handle, Entry & entry, std::string parentPath)
:DirOneLevelIterator(handle, entry,parentPath)
{
}

darknessNight::Filesystem::DirRecursiveIterator::DirRecursiveIterator(Entry & entry) 
	:DirOneLevelIterator(entry) 
{}

bool darknessNight::Filesystem::DirRecursiveIterator::nextFileExists(WIN32_FIND_DATAA & ffd) {
	return DirOneLevelIterator::nextFileExists(ffd);
}

void darknessNight::Filesystem::DirRecursiveIterator::getNextFile(WIN32_FIND_DATAA & ffd) {
	DirOneLevelIterator::getNextFile(ffd);
}

void darknessNight::Filesystem::DirRecursiveIterator::closeFind() {
	DirOneLevelIterator::closeFind();
}
