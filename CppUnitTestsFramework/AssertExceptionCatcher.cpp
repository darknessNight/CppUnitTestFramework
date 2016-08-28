#include "AssertExceptionCatcher.h"

void darknessNight_CppUnitTestFramework::AssertExceptionCatcher::throwCatchUnknowException(std::string userMessage)
{
	std::string assertMessage = ("Wrong exception throwed. Unknow exception");
	std::string result = getAddOwnMessageIfExists(userMessage, assertMessage);
	BasicAssert::Fail(result);
}

void darknessNight_CppUnitTestFramework::AssertExceptionCatcher::throwThrowFailedMessage(std::string userMessage)
{
	std::string assertMessage = ("Exception not throwed.");
	std::string result = getAddOwnMessageIfExists(userMessage, assertMessage);
	BasicAssert::Fail(result);
}
