#include "DirOneLevelIterator.h"

using namespace darknessNight::Filesystem;

darknessNight::Filesystem::DirOneLevelIterator::DirOneLevelIterator():entry("."){
	systemIterator = std::make_shared<SystemDirIterator>();
}

darknessNight::Filesystem::DirOneLevelIterator::DirOneLevelIterator(std::string parentPath):DirOneLevelIterator(){
	getFirstEntry(parentPath);
}

bool darknessNight::Filesystem::DirOneLevelIterator::nextFileExists() {
	return systemIterator->nextFileExists();
}

void darknessNight::Filesystem::DirOneLevelIterator::getFirstEntry(std::string &parentPath) {
	systemIterator->findFirstFile(parentPath);
	entry = Entry(systemIterator->getNextFileName());
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

bool darknessNight::Filesystem::DirOneLevelIterator::operator==(const DirOneLevelIterator & other) const {
	return *systemIterator==*other.systemIterator;
}

bool darknessNight::Filesystem::DirOneLevelIterator::operator!=(const DirOneLevelIterator & other) const {
	return *systemIterator != *other.systemIterator;
}

void darknessNight::Filesystem::DirOneLevelIterator::findNextFile() {
	if (!nextFileExists()) {
		systemIterator->closeFind();
	} else {
		auto tmp = systemIterator->getNextFileName();
		entry = Entry(tmp);
	}
}

Entry& darknessNight::Filesystem::DirOneLevelIterator::operator*() {
	return entry;
}

Entry* darknessNight::Filesystem::DirOneLevelIterator::operator->() {
	return &entry;
}

