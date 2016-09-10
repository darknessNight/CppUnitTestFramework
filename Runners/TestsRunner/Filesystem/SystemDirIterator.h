#pragma once
#include "Entry.h"

namespace darknessNight {
	namespace Filesystem {
		class SystemDirIterator{
		public:
		public:
			virtual bool operator==(const SystemDirIterator& other) const=0;
			virtual bool operator!=(const SystemDirIterator& other) const=0;

			virtual bool findFirstFile(std::string path)=0;
			virtual bool isEnded()=0;
			virtual int findNextFileFromHandle()=0;
			virtual bool nextFileExists()=0;
			virtual std::string getNextFileName()=0;
			virtual void closeFind()=0;
		};
	}
}


#ifdef __linux
    class SystemDirIterator{
    };
#endif
