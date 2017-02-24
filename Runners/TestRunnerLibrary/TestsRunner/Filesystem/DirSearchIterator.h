#pragma once
#include "DirRecursiveIterator.h"
#include <regex>

namespace darknessNight {
	namespace Filesystem {
		class DirSearchIterator :public DirRecursiveIterator {
		protected:
			std::regex searchRegex;
		protected:
			friend class Directory;
			DirSearchIterator(std::string parentPath, std::string searchPattern);
			void findFirstMatchedEntry();
			DirSearchIterator();
			bool matchPattern(std::string);
		public:
			void findNextFile() override;
			bool entryNotMatchAndCanSearch();
		};

	}
}