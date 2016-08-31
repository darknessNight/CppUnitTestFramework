#pragma once
#include "Exceptions.h"
#include <memory>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace darknessNight {
	namespace FileSystem {

		class Directory {
		private:
			std::string path;
		private:
			Directory(std::string path);
		public:
			static Directory Current();
			std::string getPath();
		};
	}
}