#include "DirOneLevelIterator.h"

using namespace darknessNight::Filesystem;

darknessNight::Filesystem::DirOneLevelIterator::DirOneLevelIterator(Entry& entry) :entry(entry) {
	handle = nullptr;
}

darknessNight::Filesystem::DirOneLevelIterator::DirOneLevelIterator(HANDLE handle, Entry& entry, std::string parentPath) : entry(entry) {
	this->handle = handle;
	this->parentPath = parentPath;
}

DirOneLevelIterator & darknessNight::Filesystem::DirOneLevelIterator::operator++() {
	findNextFile();
	return *this;
}

DirOneLevelIterator & darknessNight::Filesystem::DirOneLevelIterator::operator++(int) {
	DirOneLevelIterator old(*this);
	operator++();
	return old;
}

void darknessNight::Filesystem::DirOneLevelIterator::findNextFile() {
	WIN32_FIND_DATAA ffd;
	if (nextFileExists(ffd)) {
		closeFind();
	} else
		getNextFile(ffd);
}

bool darknessNight::Filesystem::DirOneLevelIterator::nextFileExists(WIN32_FIND_DATAA &ffd) {
	return FindNextFileA(handle, &ffd) == 0;
}

void darknessNight::Filesystem::DirOneLevelIterator::getNextFile(WIN32_FIND_DATAA &ffd) {
	entry = Entry(parentPath + ffd.cFileName);
}

void darknessNight::Filesystem::DirOneLevelIterator::closeFind() {
	FindClose(handle);
	handle = nullptr;
}

bool darknessNight::Filesystem::DirOneLevelIterator::operator==(DirOneLevelIterator other) const {
	return handle == other.handle;
}

bool darknessNight::Filesystem::DirOneLevelIterator::operator!=(DirOneLevelIterator other) const {
	return handle != other.handle;
}

Entry& darknessNight::Filesystem::DirOneLevelIterator::operator*() {
	return entry;
}

Entry* darknessNight::Filesystem::DirOneLevelIterator::operator->() {
	return &entry;
}

