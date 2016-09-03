#include "Directory.h"

using namespace darknessNight::Filesystem;

darknessNight::Filesystem::Directory::iterator darknessNight::Filesystem::Directory::begin() {
	return iterator(path);
}

darknessNight::Filesystem::Directory::iterator darknessNight::Filesystem::Directory::end() {
	return iterator();
}

darknessNight::Filesystem::Directory::recursiveIterator darknessNight::Filesystem::Directory::recursiveBegin() {
	return recursiveIterator(path);
}

darknessNight::Filesystem::Directory::recursiveIterator darknessNight::Filesystem::Directory::recursiveEnd() {
	return recursiveIterator();
}

darknessNight::Filesystem::Directory::searchIterator darknessNight::Filesystem::Directory::searchBegin(std::string pattern) {
	return searchIterator(path, pattern);
}

darknessNight::Filesystem::Directory::searchIterator darknessNight::Filesystem::Directory::searchEnd() {
	return searchIterator();
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