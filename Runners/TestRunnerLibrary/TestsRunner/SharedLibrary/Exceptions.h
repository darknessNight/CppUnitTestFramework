#pragma once
#include "../Exception.h"

using namespace darknessNight::Exceptions;
namespace darknessNight {
	namespace SharedLibrary {
		class FunctionLoadException :public Exception {
		public:
			explicit FunctionLoadException(std::string mess) :Exception(mess) {
			}
		};
		class LibraryLoadException :public Exception {
		public:
			explicit LibraryLoadException(std::string mess) :Exception(mess) {
			}
		};
	}
}