#include "SystemSpecificDirIterator.h"

bool darknessNight::Filesystem::SystemSpecificDirIterator::operator==(const SystemSpecificDirIterator & other) const {
	return handle == other.handle;
}

bool darknessNight::Filesystem::SystemSpecificDirIterator::operator!=(const SystemSpecificDirIterator & other) const {
	return handle != other.handle;
}

darknessNight::Filesystem::SystemSpecificDirIterator::SystemSpecificDirIterator() {
	memset(&ffd, 0, sizeof(WIN32_FIND_DATAA));
}

bool darknessNight::Filesystem::SystemSpecificDirIterator::findFirstFile(std::string path) {
	handle = FindFirstFileA((path + "/*").c_str(), &ffd);
	return !isEnded();
}

bool darknessNight::Filesystem::SystemSpecificDirIterator::isEnded() {
	return handle == nullptr;
}

int darknessNight::Filesystem::SystemSpecificDirIterator::findNextFileFromHandle() {
	return FindNextFileA(handle, &ffd);
}

bool darknessNight::Filesystem::SystemSpecificDirIterator::nextFileExists() {
	return findNextFileFromHandle() != 0;
}

std::string darknessNight::Filesystem::SystemSpecificDirIterator::getNextFileName() {
	return parentPath + ffd.cFileName;
}

void darknessNight::Filesystem::SystemSpecificDirIterator::closeFind() {
	if (handle != nullptr)
		FindClose(handle);
	handle = nullptr;
}
