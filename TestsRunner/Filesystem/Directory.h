#pragma once
#include "DirRecursiveIterator.h"
namespace darknessNight {
	namespace Filesystem {

		class Directory:public Entry {
		private:
			Directory() {}
		public:
			typedef DirOneLevelIterator iterator;
			typedef DirRecursiveIterator recursiveIterator;
			iterator begin();
			iterator end();
			recursiveIterator recursiveBegin();
			recursiveIterator recursiveEnd();
			Directory(std::string path);
			static Directory Current();
		private:
			Entry findFirstFile(void*& handle);
		};
	}
}