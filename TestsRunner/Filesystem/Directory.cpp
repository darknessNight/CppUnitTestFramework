#include "Directory.h"

using namespace darknessNight::Filesystem;

darknessNight::Filesystem::Directory::iterator darknessNight::Filesystem::Directory::begin() {
	HANDLE handle;
	Entry entry=findFirstFile(handle);
	return iterator(handle, entry, path+"/");
}

#ifdef _WIN32
Entry darknessNight::Filesystem::Directory::findFirstFile(void*& handle) {
	WIN32_FIND_DATAA ffd;
	handle = FindFirstFileA((path + "/*").c_str(), &ffd);
	Entry entry(path + "/" + ffd.cFileName);
	return entry;
}
#endif

darknessNight::Filesystem::Directory::iterator darknessNight::Filesystem::Directory::end() {
	return DirOneLevelIterator(*this);
}

darknessNight::Filesystem::Directory::recursiveIterator darknessNight::Filesystem::Directory::recursiveBegin() {
	HANDLE handle;
	Entry entry = findFirstFile(handle);
	return recursiveIterator(handle, entry, path + "/");
}

darknessNight::Filesystem::Directory::recursiveIterator darknessNight::Filesystem::Directory::recursiveEnd() {
	return recursiveIterator(*this);
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