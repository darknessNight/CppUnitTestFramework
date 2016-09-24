#include "DirOneLevelIterator.h"
#include "SystemDirIteratorLinux.h"
#include "SystemDirIteratorWindows.h"

using namespace darknessNight::Filesystem;

DirOneLevelIterator::DirOneLevelIterator():entry("."){
	systemIterator = std::make_shared<CurrentSystemDirIterator>();
}

DirOneLevelIterator::DirOneLevelIterator(std::string parentPath):entry("."){
    systemIterator = std::make_shared<CurrentSystemDirIterator>();
	getFirstEntry(parentPath);
}

bool DirOneLevelIterator::nextFileExists() {
	return systemIterator->nextFileExists();
}

void DirOneLevelIterator::getFirstEntry(std::string &parentPath) {
	systemIterator->findFirstFile(parentPath);
	entry = Entry(systemIterator->getNextFileName());
}

DirOneLevelIterator & DirOneLevelIterator::operator++() {
	findNextFile();
	return *this;
}

DirOneLevelIterator DirOneLevelIterator::operator++(int) {
	DirOneLevelIterator old(*this);
	operator++();
	return old;
}

bool DirOneLevelIterator::operator==(const DirOneLevelIterator & other) const {
	return *systemIterator==*other.systemIterator;
}

bool DirOneLevelIterator::operator!=(const DirOneLevelIterator & other) const {
	return *systemIterator != *other.systemIterator;
}

void DirOneLevelIterator::findNextFile() {
	if (!nextFileExists()) {
		systemIterator->closeFind();
	} else {
		auto tmp = systemIterator->getNextFileName();
		entry = Entry(tmp);
	}
}

Entry& DirOneLevelIterator::operator*() {
	return entry;
}

Entry* DirOneLevelIterator::operator->() {
	return &entry;
}

