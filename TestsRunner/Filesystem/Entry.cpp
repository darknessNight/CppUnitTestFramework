#include "Entry.h"


darknessNight::Filesystem::Entry::Entry(std::string path) {
	getInfoOrThrowIfNotExists(path);
	this->path = path;
}

void darknessNight::Filesystem::Entry::getInfoOrThrowIfNotExists(std::string &path) {
	struct stat fileInfo;
	getInfoStruct(fileInfo, path);

	_isDir = (ModeIsDir & fileInfo.st_mode) != 0;
	_isFile = (ModeIsFile & fileInfo.st_mode) != 0;
	aTime = fileInfo.st_atime;
	cTime = fileInfo.st_ctime;
	mTime = fileInfo.st_mtime;
}

void darknessNight::Filesystem::Entry::getInfoStruct(struct stat &fileInfo, std::string & path) {
	memset(&fileInfo, 0, sizeof(fileInfo));
	if (stat(path.c_str(), &fileInfo) != 0)
		throw FilesystemException("Path is not exists");
}

std::string darknessNight::Filesystem::Entry::getPath() const {
	return path;
}
unsigned long darknessNight::Filesystem::Entry::getModificationTime() const {
	return mTime;
}
unsigned long darknessNight::Filesystem::Entry::getCreateTime()  const {
	return cTime;
}
unsigned long darknessNight::Filesystem::Entry::getLastAccessTime()  const {
	return aTime;
}

bool darknessNight::Filesystem::Entry::isDir() const {
	return _isDir;
}

bool darknessNight::Filesystem::Entry::isFile() const {
	return _isFile;
}

