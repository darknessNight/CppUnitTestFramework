#pragma once
#include <memory>
#include "DirSearchIterator.h"
namespace darknessNight {
	namespace Filesystem {
		class Directory:public Entry{
		protected:
			Directory() {}
		public:
			typedef DirOneLevelIterator iterator;
			typedef DirRecursiveIterator recursiveIterator;
			typedef DirSearchIterator searchIterator;
			virtual iterator begin();
			virtual iterator end();
			virtual recursiveIterator recursiveBegin();
			virtual recursiveIterator recursiveEnd();
			virtual searchIterator searchBegin(std::string pattern);
			virtual searchIterator searchEnd();
			virtual std::shared_ptr<Directory> get(std::string path);
			virtual std::vector<Entry> getElements();
			virtual std::vector<Entry> getElementsRecursive();
			virtual std::vector<Entry> searchElements(std::string pattern);
			explicit Directory(std::string path);
			static Directory Current();
		};
	}
}