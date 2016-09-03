#include "DirOneLevelIterator.h"

using namespace darknessNight::Filesystem;

darknessNight::Filesystem::DirOneLevelIterator::DirOneLevelIterator():entry("."){
	handle = nullptr;
}

darknessNight::Filesystem::DirOneLevelIterator::DirOneLevelIterator(std::string parentPath):entry("."){
	getFirstEntry(parentPath);
	this->parentPath = parentPath+"/";
}

void darknessNight::Filesystem::DirOneLevelIterator::getFirstEntry(std::string &parentPath) {
	findFirstFile(parentPath);
	entry = Entry(getNextFileName());
}

DirOneLevelIterator & darknessNight::Filesystem::DirOneLevelIterator::operator++() {
	findNextFile();
	return *this;
}

DirOneLevelIterator darknessNight::Filesystem::DirOneLevelIterator::operator++(int) {
	DirOneLevelIterator old(*this);
	operator++();
	return old;
}

void darknessNight::Filesystem::DirOneLevelIterator::findNextFile() {
	if (!nextFileExists()) {
		closeFind();
	} else {
		auto tmp = getNextFileName();
		entry = Entry(tmp);
	}
}

Entry& darknessNight::Filesystem::DirOneLevelIterator::operator*() {
	return entry;
}

Entry* darknessNight::Filesystem::DirOneLevelIterator::operator->() {
	return &entry;
}

