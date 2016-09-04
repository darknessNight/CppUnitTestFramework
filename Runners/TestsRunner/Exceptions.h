#pragma once
#include <string>

namespace darknessNight {
	namespace Exceptions {
		class Exception :public std::exception {
		protected:
			std::string message;
		public:
			Exception(std::string mess) {
				message = mess;
			}

			const char* what() {
				return message.c_str();
			}

			std::string getMessage() {
				return message;
			}
		};
	}
}

using namespace darknessNight::Exceptions;
namespace darknessNight {
	namespace SharedLibrary {
		class FunctionLoadException :public Exception {
		public:
			FunctionLoadException(std::string mess) :Exception(mess) {
			}
		};
		class LibraryLoadException :public Exception {
		public:
			LibraryLoadException(std::string mess) :Exception(mess) {
			}
		};
	}
}