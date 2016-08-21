#pragma once
#include <string>
namespace darknessNight::CppUnitTestFramework {
	class AssertException :public std::exception {
	public:
		AssertException(const char* message) :exception(message) {
		}

		AssertException(std::string message) :exception(message.c_str()) {
		}
	};

	class ExceptionWithInnerException: public std::exception {
	protected:
		std::exception* innerException;
	public:
		ExceptionWithInnerException(std::exception& inner) :exception(inner.what()) {
			innerException = &inner;
		}

		const std::exception& getInnerException() {
			return *innerException;
		}
	};

	class SetUpException :public ExceptionWithInnerException {
	public:
		SetUpException(std::exception& inner) :ExceptionWithInnerException(inner) {
		}
	};

	class TearDownException :public ExceptionWithInnerException {
	public:
		TearDownException(std::exception& inner) :ExceptionWithInnerException(inner){
		}
	};
}
