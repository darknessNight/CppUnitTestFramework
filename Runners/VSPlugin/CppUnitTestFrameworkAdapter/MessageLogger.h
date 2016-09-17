#pragma once
#include <vcclr.h>
#include <TestsRunner/MessageLogger.h>
#include "ConvertTools.h"
using namespace System;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging;

namespace darknessNight::CppUnitTest::VSAdapter {
	private ref class MessageLogger :public IMessageLogger {
	private:
		IMessageLogger^ myLogger = nullptr;
	public:
		MessageLogger(IMessageLogger^ exLogger) {
			myLogger = exLogger;
		}

		virtual void SendMessage(TestMessageLevel level, String^ message){
			if (myLogger != nullptr)
				myLogger->SendMessage(level, message);
		}

		void sendInfo(String^ message) {
			SendMessage(TestMessageLevel::Informational, message);
		}

		void sendError(String^ message) {
			SendMessage(TestMessageLevel::Error, message);
		}

		void sendWarning(String^ message) {
			SendMessage(TestMessageLevel::Warning, message);
		}
	};

	class CppMessageLogger:public darknessNight::TestsRunner::MessageLogger {
	private:
		gcroot<VSAdapter::MessageLogger^> logger;
	public:
		CppMessageLogger(gcroot<VSAdapter::MessageLogger^> messageLogger) {
			logger = messageLogger;
		}

		void sendMessage(std::string message) {
			logger->sendInfo(ConvertTools::CppStringToCliString(message));
		}

		void sendError(std::string message) {
			logger->sendError(ConvertTools::CppStringToCliString(message));
		}

		void sendWarning(std::string message) {
			logger->sendError(ConvertTools::CppStringToCliString(message));
		}
	};
}