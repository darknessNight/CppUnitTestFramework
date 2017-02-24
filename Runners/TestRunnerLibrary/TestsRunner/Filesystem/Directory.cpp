#include "Directory.h"

using namespace darknessNight::Filesystem;

Directory::iterator Directory::begin() {
	return iterator(path);
}

Directory::iterator Directory::end() {
	return iterator();
}

Directory::recursiveIterator Directory::recursiveBegin() {
	return recursiveIterator(path);
}

Directory::recursiveIterator Directory::recursiveEnd() {
	return recursiveIterator();
}

Directory::searchIterator Directory::searchBegin(std::string pattern) {
	return searchIterator(path, pattern);
}

Directory::searchIterator Directory::searchEnd() {
	return searchIterator();
}

std::shared_ptr<Directory> Directory::get(std::string path) {
	return std::make_shared<Directory>(path);
}

std::vector<Entry> Directory::getElements() {
	std::vector<Entry> entries;
	for (auto el : *this)
		entries.push_back(el);
	return entries;
}

std::vector<Entry> Directory::getElementsRecursive() {
	std::vector<Entry> entries;
	for (auto iter=recursiveBegin();iter!=recursiveEnd();iter++)
		entries.push_back(*iter);
	return entries;
}

std::vector<Entry> Directory::searchElements(std::string pattern) {
	std::vector<Entry> entries;
	for (auto iter = searchBegin(pattern); iter != searchEnd(); iter++)
		entries.push_back(*iter);
	return entries;
}

Directory::Directory(std::string path):Entry(path) {
	if(!isDir())
		throw FilesystemException("Path <"+path+"> is not directory");
}

Directory Directory::Current() {
	char buff[1000];
	getcwd(buff, 1000);
	return Directory(buff);
}