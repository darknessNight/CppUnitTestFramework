#include "Directory.h"
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace darknessNight::FileSystem;
#ifdef _WIN32
darknessNight::FileSystem::Directory::Directory(std::string path) {
	this->path = path;
}

Directory darknessNight::FileSystem::Directory::Current() {
	char buff[1000];
	GetCurrentDir(buff, 1000);
	return Directory(buff);
}

std::string darknessNight::FileSystem::Directory::getPath() {
	return path;
}
#endif
#ifdef __linux
#error Not supported yet
#endif