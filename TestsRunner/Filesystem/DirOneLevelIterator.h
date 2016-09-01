#pragma once
#include "Entry.h"
#include <iterator>
#include <Windows.h>

namespace darknessNight {
	namespace Filesystem {
		class DirOneLevelIterator :public std::iterator<std::input_iterator_tag, void*> {
		protected:
			HANDLE handle;
			Entry entry;
			std::string parentPath;
		protected:
			friend class Directory;
			DirOneLevelIterator(HANDLE handle, Entry& entry, std::string parentPath);
			DirOneLevelIterator(Entry& entry);
		public:
			DirOneLevelIterator& operator++();
			void findNextFile();
			virtual bool nextFileExists(WIN32_FIND_DATAA &ffd);
			virtual void getNextFile(WIN32_FIND_DATAA &ffd);
			virtual void closeFind();
			bool operator==(DirOneLevelIterator other) const;
			bool operator!=(DirOneLevelIterator other) const;
			Entry& operator*();
			Entry& operator->();
		};

	}
}