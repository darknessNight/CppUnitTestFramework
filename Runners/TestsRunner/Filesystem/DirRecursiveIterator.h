#pragma once
#include "DirOneLevelIterator.h"
#include <list>
namespace darknessNight {
	namespace Filesystem {
		class DirRecursiveIterator :public DirOneLevelIterator {
		protected:
			std::list<std::string> dirs;
		protected:
			friend class Directory;
			explicit DirRecursiveIterator(std::string parentPath);
			DirRecursiveIterator();
		public:
			bool nextFileExists() override;
			bool changeSearchDir();
			std::string getNextDir();
			bool setNewSearchDir();
			void findNextFile()override;
		};

	}
}