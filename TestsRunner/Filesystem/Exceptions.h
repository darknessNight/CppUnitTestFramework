#pragma once

#include "../Exceptions.h"

namespace darknessNight {
	namespace Filesystem {
		class FilesystemException :public Exception {
		public:
			FilesystemException(std::string mess) : Exception(mess) {}
		};
	}
}