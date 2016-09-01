#include "Directory.h"


using namespace darknessNight::Filesystem;
darknessNight::Filesystem::Directory::Directory(std::string path):Entry(path) {
	if(!isDir())
		throw FilesystemException("Path is not directory");
}

Directory darknessNight::Filesystem::Directory::Current() {
	char buff[1000];
	getcwd(buff, 1000);
	return Directory(buff);
}