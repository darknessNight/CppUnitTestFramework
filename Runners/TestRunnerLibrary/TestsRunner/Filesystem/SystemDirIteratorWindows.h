#include "SystemDirIterator.h"
#ifdef _WIN32
#include <Windows.h>

namespace darknessNight {
	namespace Filesystem {

		class SystemDirIteratorWindows:public SystemDirIterator {
		protected:
			HANDLE handle=nullptr;
			WIN32_FIND_DATAA ffd;
			std::string parentPath;
			const std::string patternAll = "*";
		public:
			bool operator==(const SystemDirIterator& other) const;
			bool operator!=(const SystemDirIterator& other) const;

			SystemDirIteratorWindows();
			virtual bool findFirstFile(std::string path);
			bool isEnded();
			virtual int findNextFileFromHandle();
			virtual bool nextFileExists();
			virtual std::string getNextFileName();
			void closeFind();
		};

		typedef SystemDirIteratorWindows CurrentSystemDirIterator;
	}
}
#endif
