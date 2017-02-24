#pragma once
#include <string>
//#define ADDITIONAL_LOGS

namespace darknessNight {
	namespace TestsRunner {
		class MessageLogger {
		public:
			virtual void sendMessage(std::string) = 0;
			virtual void sendError(std::string) = 0;
			virtual void sendWarning(std::string) = 0;
		};
	}
}