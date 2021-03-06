#include "AssertExceptionCatcher.h"

void darknessNight::CppUnitTestFramework::AssertExceptionCatcher::DoesNotThrow(void(*func)(), std::string message) {
	try {
		func();
	}
	catch (std::exception &ex) {
		helper.throwFailedExceptionFromPattern("Catched unexpected exception <%result>", std::string(""), std::string(typeid(ex).name()), message);
	}
	catch (...) {
		throwCatchUnknowException(message);
	}
}

void darknessNight::CppUnitTestFramework::AssertExceptionCatcher::throwCatchUnknowException(std::string userMessage)
{
	helper.throwFailedExceptionFromPattern("Catched unexpected exception <%result>", std::string(""), std::string("Unknow-Type"), userMessage);
}

void darknessNight::CppUnitTestFramework::AssertExceptionCatcher::throwThrowFailedMessage(std::string userMessage)
{
	std::string assertMessage = ("Exception not throwed.");
	std::string result = helper.getAddOwnMessageIfExists(userMessage, assertMessage);
	Fail(result);
}
