#pragma once
#include <string>
#ifdef _linux
#define abstract
#endif

namespace darknessNight {
	namespace TestsRunner {
		class MessageLogger abstract {
		public:
			virtual void sendMessage(std::string) = 0;
			virtual void sendError(std::string) = 0;
			virtual void sendWarning(std::string) = 0;
		};
	}
}