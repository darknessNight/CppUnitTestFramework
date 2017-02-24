#pragma once
#include "MessageLogger.h"


namespace darknessNight {
	namespace TestsRunner {
		class ConsoleMessageLogger :public MessageLogger {
		public:
			virtual void sendMessage(std::string) override;
			virtual void sendError(std::string) override;
			virtual void sendWarning(std::string) override;
		};

		class QuietMessageLogger :public MessageLogger {
		public:
			virtual void sendMessage(std::string) override{}
			virtual void sendError(std::string) override{}
			virtual void sendWarning(std::string) override{}
		};
	}
}