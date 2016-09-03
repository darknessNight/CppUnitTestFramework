#pragma once
#include "Entry.h"
#include <iterator>
#ifdef _WIN32
#include "SystemSpecificDirIterator.h"

namespace darknessNight {
	namespace Filesystem {
		class DirOneLevelIterator :public std::iterator<std::input_iterator_tag, void*>, public SystemSpecificDirIterator {
		protected:
			Entry entry;
			friend class Directory;
		public:
			DirOneLevelIterator& operator++();
			DirOneLevelIterator operator++(int);
			Entry& operator*();
			Entry* operator->();
		protected:
			explicit DirOneLevelIterator(std::string parentPath);
			explicit DirOneLevelIterator();
			void getFirstEntry(std::string &parentPath);
			virtual void findNextFile();
		};

	}
}
#endif