#include "SystemDirIterator.h"
#ifdef __linux
#include <dirent.h>

namespace darknessNight {
	namespace Filesystem {
        class SystemDirIterator;

		class SystemDirIteratorLinux:public SystemDirIterator {
		protected:
            DIR *handle=nullptr;
            struct dirent *dirEntry=nullptr;
			std::string parentPath;
			const std::string patternAll = "*";
		public:
			bool operator==(const SystemDirIterator& other) const;
			bool operator!=(const SystemDirIterator& other) const;

			//SystemDirIterator();
			virtual bool findFirstFile(std::string path);
			virtual bool isEnded();
			virtual int findNextFileFromHandle();
			virtual bool nextFileExists();
			virtual std::string getNextFileName();
			virtual void closeFind();
		};

		typedef SystemDirIteratorLinux CurrentSystemDirIterator;
	}
}
#endif
