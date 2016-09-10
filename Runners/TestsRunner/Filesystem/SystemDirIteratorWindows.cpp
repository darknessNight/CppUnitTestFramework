#include "SystemDirIteratorWindows.h"
#ifdef _WIN32

bool darknessNight::Filesystem::SystemDirIteratorWindows::operator==(const SystemDirIterator & other) const {
	auto otherIt=(SystemDirIteratorWindows*)&other;
	return handle == otherIt->handle;
}

bool darknessNight::Filesystem::SystemDirIteratorWindows::operator!=(const SystemDirIterator & other) const {
	auto otherIt=(SystemDirIteratorWindows*)&other;
	return handle != otherIt->handle;
}

darknessNight::Filesystem::SystemDirIteratorWindows::SystemDirIteratorWindows() {
	memset(&ffd, 0, sizeof(WIN32_FIND_DATAA));
}

bool darknessNight::Filesystem::SystemDirIteratorWindows::findFirstFile(std::string path) {
	parentPath = path + "/";
	handle = FindFirstFileA((path + "/*").c_str(), &ffd);
	return !isEnded();
}

bool darknessNight::Filesystem::SystemDirIteratorWindows::isEnded() {
	return handle == nullptr;
}

int darknessNight::Filesystem::SystemDirIteratorWindows::findNextFileFromHandle() {
	return FindNextFileA(handle, &ffd);
}

bool darknessNight::Filesystem::SystemDirIteratorWindows::nextFileExists() {
	return findNextFileFromHandle() != 0;
}

std::string darknessNight::Filesystem::SystemDirIteratorWindows::getNextFileName() {
	return parentPath + ffd.cFileName;
}

void darknessNight::Filesystem::SystemDirIteratorWindows::closeFind() {
	if (handle != nullptr)
		FindClose(handle);
	handle = nullptr;
}
#endif
