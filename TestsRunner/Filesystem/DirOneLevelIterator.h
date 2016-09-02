#pragma once
#include "Entry.h"
#include <iterator>
#ifdef _WIN32
#include <Windows.h>

namespace darknessNight {
	namespace Filesystem {
		class DirOneLevelIterator :public std::iterator<std::input_iterator_tag, void*> {
		protected:
			HANDLE handle;
			Entry entry;
			std::string parentPath;
			friend class Directory;
		public:
			bool operator==(DirOneLevelIterator other) const;
			bool operator!=(DirOneLevelIterator other) const;
			DirOneLevelIterator& operator++();
			DirOneLevelIterator operator++(int);
			Entry& operator*();
			Entry* operator->();
		protected:
			DirOneLevelIterator(HANDLE handle, Entry& entry, std::string parentPath);
			DirOneLevelIterator(Entry& entry);
			void findNextFile();
			virtual bool nextFileExists(WIN32_FIND_DATAA &ffd);
			virtual void getNextFile(WIN32_FIND_DATAA &ffd);
			virtual void closeFind();
		};

	}
}
#endif