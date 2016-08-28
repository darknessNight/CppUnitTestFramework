#include "AssertHelper.h"

std::string darknessNight_CppUnitTestFramework::AssertHelper::getFullAssertMessage(std::string pattern, const std::string & expected, const std::string & result, std::string & message)
{
	pattern = replaceVars(pattern, expected, result);
	return getAddOwnMessageIfExists(message, pattern);
}

std::string darknessNight_CppUnitTestFramework::AssertHelper::replaceVars(std::string & pattern, const std::string & expected, const std::string & result)
{
	int posResult = getResultVarPos(pattern);
	int posExpected = getExpectedVarPos(pattern, posResult, result);

	pattern = replaceVarOnPos(pattern, posResult, resultExp.size(), result);
	pattern = replaceVarOnPos(pattern, posExpected, expectedExp.size(), expected);
	return pattern;
}

int darknessNight_CppUnitTestFramework::AssertHelper::getResultVarPos(std::string & pattern)
{
	return getStringPos(resultExp, pattern);
}

int darknessNight_CppUnitTestFramework::AssertHelper::getExpectedVarPos(std::string & pattern, int posResult, const std::string & result)
{
	int posExpected = getStringPos(expectedExp, pattern);
	if (posResult < posExpected && posResult >= 0)
		posExpected += (result.size() - resultExp.size());
	return posExpected;
}

std::string darknessNight_CppUnitTestFramework::AssertHelper::replaceVarOnPos(std::string & pattern, int posResult, int repLenght, const std::string & result)
{
	if (posResult >= 0)
		pattern = pattern.replace(posResult, repLenght, result);
	return pattern;
}

int darknessNight_CppUnitTestFramework::AssertHelper::getStringPos(std::string & expected, std::string & result) {
	return result.find(expected);
}

const std::string darknessNight_CppUnitTestFramework::AssertHelper::getAddOwnMessageIfExists(std::string userMessage, std::string assertMessage) {
	if (userMessage.size() <= 0)
		return assertMessage;
	else
		return assertMessage + ". Message: <" + userMessage + ">";
}
