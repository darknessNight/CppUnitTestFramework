#pragma once
using namespace System;
using namespace Microsoft::VisualStudio::TestPlatform::ObjectModel::Logging;

namespace darknessNight::CppUnitTest::VSAdapter {
	public ref class MessageLogger :public IMessageLogger {
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

		void sendErro(String^ message) {
			SendMessage(TestMessageLevel::Error, message);
		}

		void sendWarning(String^ message) {
			SendMessage(TestMessageLevel::Warning, message);
		}
	};
}