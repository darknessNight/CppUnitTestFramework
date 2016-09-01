#pragma once

#include <string>
#include <sys/stat.h>
#include "Exceptions.h"
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#define stat _stat
#define ModeIsDir S_IFDIR
#define ModeIsFile S_IFREG
#else
#include <unistd.h>
#define ModeIsDir S_ISDIR
#define ModeIsFile S_ISREG
#endif

namespace darknessNight {
	namespace Filesystem {
		class Entry {
		protected:
			bool _isDir, _isFile;
			std::string path;
			unsigned long mTime, cTime, aTime;
		public:
			Entry(std::string);
			std::string getPath();
			unsigned long getModificationTime();
			unsigned long getCreateTime();
			unsigned long getLastAccessTime();
			bool isDir();
			bool isFile();
		protected:
			Entry() {}
		private:
			void getInfoOrThrowIfNotExists(std::string &path);
			void getInfoStruct(struct stat &fileInfo, std::string & path);
		};
	}
}