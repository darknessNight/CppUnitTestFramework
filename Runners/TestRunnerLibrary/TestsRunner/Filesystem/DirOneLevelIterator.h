#pragma once
#include "Entry.h"
#include <iterator>
#include <memory>
#include "SystemDirIterator.h"

namespace darknessNight {
	namespace Filesystem {
		class DirOneLevelIterator :public std::iterator<std::input_iterator_tag, Entry>{
		protected:
			Entry entry;
			std::string parent;
			std::shared_ptr<SystemDirIterator> systemIterator;
			friend class Directory;
		public:
			virtual DirOneLevelIterator& operator++();
			virtual DirOneLevelIterator operator++(int);
			bool operator==(const DirOneLevelIterator& other) const;
			bool operator!=(const DirOneLevelIterator& other) const;
			virtual Entry& operator*();
			virtual Entry* operator->();
		protected:
			explicit DirOneLevelIterator(std::string parentPath);
			explicit DirOneLevelIterator();
			virtual bool nextFileExists();
			virtual void getFirstEntry(std::string &parentPath);
			virtual void findNextFile();
		};

	}
}
