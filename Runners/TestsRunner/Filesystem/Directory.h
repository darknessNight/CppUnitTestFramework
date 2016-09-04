#pragma once
#include "DirSearchIterator.h"
namespace darknessNight {
	namespace Filesystem {

		class IDirectory {
		public:
			typedef DirOneLevelIterator iterator;
			typedef DirRecursiveIterator recursiveIterator;
			typedef DirSearchIterator searchIterator;
			virtual iterator begin()=0;
			virtual iterator end()=0;
			virtual recursiveIterator recursiveBegin()=0;
			virtual recursiveIterator recursiveEnd() = 0;
			virtual searchIterator searchBegin(std::string pattern) = 0;
			virtual searchIterator searchEnd() = 0;
		};

		class Directory:public Entry, public IDirectory {
		private:
			Directory() {}
		public:
			typedef DirOneLevelIterator iterator;
			typedef DirRecursiveIterator recursiveIterator;
			typedef DirSearchIterator searchIterator;
			iterator begin();
			iterator end();
			recursiveIterator recursiveBegin();
			recursiveIterator recursiveEnd();
			searchIterator searchBegin(std::string pattern);
			searchIterator searchEnd();
			virtual std::vector<Entry> getElements();
			virtual std::vector<Entry> getElementsRecursive();
			virtual std::vector<Entry> searchElements(std::string pattern);
			explicit Directory(std::string path);
			static Directory Current();
		};
	}
}