#include "SystemDirIterator.h"

bool darknessNight::Filesystem::SystemDirIterator::operator==(const SystemDirIterator & other) const {
	return handle == other.handle;
}

bool darknessNight::Filesystem::SystemDirIterator::operator!=(const SystemDirIterator & other) const {
	return handle != other.handle;
}

darknessNight::Filesystem::SystemDirIterator::SystemDirIterator() {
	memset(&ffd, 0, sizeof(WIN32_FIND_DATAA));
}

bool darknessNight::Filesystem::SystemDirIterator::findFirstFile(std::string path) {
	parentPath = path + "/";
	handle = FindFirstFileA((path + "/*").c_str(), &ffd);
	return !isEnded();
}

bool darknessNight::Filesystem::SystemDirIterator::isEnded() {
	return handle == nullptr;
}

int darknessNight::Filesystem::SystemDirIterator::findNextFileFromHandle() {
	return FindNextFileA(handle, &ffd);
}

bool darknessNight::Filesystem::SystemDirIterator::nextFileExists() {
	return findNextFileFromHandle() != 0;
}

std::string darknessNight::Filesystem::SystemDirIterator::getNextFileName() {
	return parentPath + ffd.cFileName;
}

void darknessNight::Filesystem::SystemDirIterator::closeFind() {
	if (handle != nullptr)
		FindClose(handle);
	handle = nullptr;
}
