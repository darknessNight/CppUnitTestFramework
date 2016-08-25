#pragma once
#include <string>


class ExceptionWithInnerException : public std::exception {
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
	TearDownException(std::exception& inner) :ExceptionWithInnerException(inner) {
	}
};

class NullPointerException :public std::exception {
public:
	NullPointerException(std::string message) :exception(message.c_str()) {
	}
};

class NotFoundException :public std::exception {
public:
	NotFoundException(std::string message) :exception(message.c_str()) {
	}
};

class TestRegisterException :public std::exception {
public:
	TestRegisterException(std::string message) :exception(message.c_str()) {
	}
};