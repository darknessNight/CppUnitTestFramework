#include "SystemDirIteratorLinux.h"
#ifdef __linux

bool darknessNight::Filesystem::SystemDirIteratorLinux::operator==(const SystemDirIterator & other) const {
    auto otherIt=(SystemDirIteratorLinux*)&other;
	return handle == otherIt->handle;
}

bool darknessNight::Filesystem::SystemDirIteratorLinux::operator!=(const SystemDirIterator & other) const {
	auto otherIt=(SystemDirIteratorLinux*)&other;
	return handle != otherIt->handle;
}

bool darknessNight::Filesystem::SystemDirIteratorLinux::findFirstFile(std::string path) {
    if(*path.rbegin()!='/')
        parentPath = path + "/";
    else parentPath=path;
	handle = opendir(path.c_str());
	if(handle==nullptr)
        return false;
    else{
        findNextFileFromHandle();
        return dirEntry;
    }
}

bool darknessNight::Filesystem::SystemDirIteratorLinux::isEnded() {
	return dirEntry == nullptr || handle==nullptr;
}

int darknessNight::Filesystem::SystemDirIteratorLinux::findNextFileFromHandle() {
    dirEntry=readdir(handle);
	return dirEntry?1:0;
}

bool darknessNight::Filesystem::SystemDirIteratorLinux::nextFileExists() {
	return findNextFileFromHandle() != 0;
}

std::string darknessNight::Filesystem::SystemDirIteratorLinux::getNextFileName() {
	return parentPath + dirEntry->d_name;
}

void darknessNight::Filesystem::SystemDirIteratorLinux::closeFind() {
	if (handle != nullptr)
		closedir(handle);
	handle = nullptr;
}
#endif
