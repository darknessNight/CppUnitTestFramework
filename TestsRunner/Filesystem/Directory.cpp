#include "Directory.h"

using namespace darknessNight::Filesystem;

DirOneLevelIterator darknessNight::Filesystem::Directory::begin() {
	WIN32_FIND_DATAA ffd;
	HANDLE handle=FindFirstFileA((path + "/*").c_str(), &ffd);
	Entry entry(path+"/"+ffd.cFileName);
	return DirOneLevelIterator(handle, entry, path+"/");
}

DirOneLevelIterator darknessNight::Filesystem::Directory::end() {
	return DirOneLevelIterator(*this);
}

darknessNight::Filesystem::Directory::Directory(std::string path):Entry(path) {
	if(!isDir())
		throw FilesystemException("Path is not directory");
}

Directory darknessNight::Filesystem::Directory::Current() {
	char buff[1000];
	getcwd(buff, 1000);
	return Directory(buff);
}