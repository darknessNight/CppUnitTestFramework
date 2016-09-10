#include "SystemDirIterator.h"
#ifdef __linux

namespace darknessNight {
	namespace Filesystem {
        class SystemDirIterator;

		class SystemDirIteratorLinux:public SystemDirIterator {
		protected:
			std::string parentPath;
			const std::string patternAll = "*";
		public:
			bool operator==(const SystemDirIterator& other) const{return false;};
			bool operator!=(const SystemDirIterator& other) const{return false;};

			//SystemDirIterator();
			virtual bool findFirstFile(std::string path){return false;};
			virtual bool isEnded(){return false;};
			virtual int findNextFileFromHandle(){return 0;};
			virtual bool nextFileExists(){return false;};
			virtual std::string getNextFileName(){return "";};
			virtual void closeFind(){};
		};

		typedef SystemDirIteratorLinux CurrentSystemDirIterator;
	}
}
#endif
