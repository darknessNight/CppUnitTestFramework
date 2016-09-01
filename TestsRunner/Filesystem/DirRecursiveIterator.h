#pragma once
#include "DirOneLevelIterator.h"
namespace darknessNight {
	namespace Filesystem {
		class DirRecursiveIterator :public DirOneLevelIterator {
		protected:
		protected:
			friend class Directory;
			DirRecursiveIterator(HANDLE handle, Entry& entry, std::string parentPath);
			DirRecursiveIterator(Entry& entry);
		public:
			virtual bool nextFileExists(WIN32_FIND_DATAA &ffd);
			virtual void getNextFile(WIN32_FIND_DATAA &ffd);
			virtual void closeFind();
		};

	}
}