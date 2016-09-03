#pragma once
#include "DirSearchIterator.h"
namespace darknessNight {
	namespace Filesystem {

		class Directory:public Entry {
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
			explicit Directory(std::string path);
			static Directory Current();
		private:
			Entry findFirstFile(void*& handle);
		};
	}
}