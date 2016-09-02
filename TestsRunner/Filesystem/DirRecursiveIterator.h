#pragma once
#include "DirOneLevelIterator.h"
#include <list>
namespace darknessNight {
	namespace Filesystem {
		class DirRecursiveIterator :public DirOneLevelIterator {
		protected:
			std::list<std::string> dirs;
			std::string actPath;
		protected:
			friend class Directory;
			DirRecursiveIterator(HANDLE handle, Entry& entry, std::string parentPath);
			DirRecursiveIterator(Entry& entry);
		public:
			virtual bool nextFileExists(WIN32_FIND_DATAA &ffd);
			bool changeSearchDir(WIN32_FIND_DATAA & ffd);
			bool setNewSearchDir(WIN32_FIND_DATAA & ffd);
			void setNewParentPrefixAndRemoveDirFromList();
			virtual void getNextFile(WIN32_FIND_DATAA &ffd);
		};

	}
}