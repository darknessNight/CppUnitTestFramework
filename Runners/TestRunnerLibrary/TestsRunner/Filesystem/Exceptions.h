#pragma once
#include "../SharedLibrary/Exceptions.h"

namespace darknessNight {
	namespace Filesystem {
		class FilesystemException :public Exception {
		public:
			explicit FilesystemException(std::string mess) : Exception(mess) {}
		};
	}
}
