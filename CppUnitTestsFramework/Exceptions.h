#pragma once
#include <string>

namespace darknessNight_CppUnitTestFramework {
	class exception : public std::exception {
	protected:
		std::string message;
	public:
		exception() {}
		exception(std::exception& ex) :std::exception(ex) {
			this->message = ex.what();
		}
		exception(const char* message) {
			this->message = message;
		}
		const char* what() {
			return message.c_str();
		}
	};

	class ExceptionWithInnerException : public exception {
	protected:
		exception* innerException;
	public:
		ExceptionWithInnerException(exception& inner) :exception(inner.what()) {
			innerException = &inner;
		}

		const exception& getInnerException() {
			return *innerException;
		}
	};

	class SetUpException :public ExceptionWithInnerException {
	public:
		SetUpException(exception& inner) :ExceptionWithInnerException(inner) {
		}
	};

	class TearDownException :public ExceptionWithInnerException {
	public:
		TearDownException(exception& inner) :ExceptionWithInnerException(inner) {
		}
	};

	class NullPointerException :public exception {
	public:
		NullPointerException(std::string message) :exception(message.c_str()) {
		}
	};

	class NotFoundException :public exception {
	public:
		NotFoundException(std::string message) :exception(message.c_str()) {
		}
	};

	class TestRegisterException :public exception {
	public:
		TestRegisterException(std::string message) :exception(message.c_str()) {
		}
	};

}