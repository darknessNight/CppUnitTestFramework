#pragma once
#include <iterator>
#include "Entry.h"

namespace darknessNight {
	namespace Filesystem {

		class DirIterator:public std::iterator<std::input_iterator_tag, void*>{
		private:
		public:
			explicit DirIterator(long _num = 0);
			iterator& operator++();
			bool operator==(iterator other) const;
			bool operator!=(iterator other) const;
			Entry operator*() const;
			Entry operator->() const;
		};

		class Directory:public Entry {
		private:
			Directory() {}
		public:
			typedef DirIterator iterator;
			iterator begin();
			iterator end();
			Directory(std::string path);
			static Directory Current();
		};
	}
}