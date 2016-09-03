#pragma once
#include "Entry.h"
#include <Windows.h>

namespace darknessNight {
	namespace Filesystem {
		class SystemSpecificDirIterator {
		protected:
			HANDLE handle=nullptr;
			WIN32_FIND_DATAA ffd;
			std::string parentPath;
			const std::string patternAll = "*";
		public:
			bool operator==(const SystemSpecificDirIterator& other) const;
			bool operator!=(const SystemSpecificDirIterator& other) const;
		protected:
			SystemSpecificDirIterator();
			virtual bool findFirstFile(std::string path);
			bool isEnded();
			virtual int findNextFileFromHandle();
			virtual bool nextFileExists();
			virtual std::string getNextFileName();
			void closeFind();
		};
	}
}