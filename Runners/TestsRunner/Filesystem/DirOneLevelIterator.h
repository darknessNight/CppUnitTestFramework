#pragma once
#include "Entry.h"
#include <iterator>
#ifdef _WIN32
#include "SystemSpecificDirIterator.h"

namespace darknessNight {
	namespace Filesystem {
		class DirOneLevelIterator :public std::iterator<std::input_iterator_tag, Entry>, public SystemSpecificDirIterator {
		protected:
			Entry entry;
			friend class Directory;
		public:
			virtual DirOneLevelIterator& operator++();
			virtual DirOneLevelIterator operator++(int);
			virtual Entry& operator*();
			virtual Entry* operator->();
		protected:
			explicit DirOneLevelIterator(std::string parentPath);
			explicit DirOneLevelIterator();
			void getFirstEntry(std::string &parentPath);
			virtual void findNextFile();
		};

	}
}
#endif