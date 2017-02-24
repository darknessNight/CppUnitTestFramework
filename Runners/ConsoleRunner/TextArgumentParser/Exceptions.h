#pragma once
#include <string>

namespace darknessNight { namespace TextParser {
	class IncompleteArgsCollectionException :public std::exception {
	private:
		std::string message;
	public:
		IncompleteArgsCollectionException() {
			message = "One or more required arguments is not used";
		}

		explicit IncompleteArgsCollectionException(std::string mess) {
			message = mess;
		}

		char const* what() const noexcept(true) override {
			return message.c_str();
		}
	};

	class UnexpectedArgumentException :public std::exception {
	private:
		std::string unexpectedArg;
		std::string message;
	public:
		explicit UnexpectedArgumentException(std::string argName) {
			unexpectedArg = argName;
			message = "Detected unexpected argument: \"" + argName + "\"";
		}

		const char* what() const noexcept(true) override{
			return message.c_str();
		}

		std::string getUnexpectedArg() {
			return unexpectedArg;
		}
	};
}}
