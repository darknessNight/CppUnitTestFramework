#include "ArgumentParser.h"

std::initializer_list<std::string>::iterator darknessNight::TextParser::ArgumentParser::incrementIterator() {
	iterator++;
	if(iterator < iteratorEnd && isAssignOperator(*iterator)) {
		iterator++;
		iterator++;
	}
	return iterator;
}

void darknessNight::TextParser::ArgumentParser::parse(std::initializer_list<std::string> argsList) {
	for(iterator = argsList.begin() , iteratorEnd = argsList.end(); iterator < iteratorEnd; incrementIterator()) {
		parseArg();
	}
	checkHasAllRequiredArgs();
}

void darknessNight::TextParser::ArgumentParser::checkHasAllRequiredArgs() {
	for(auto arg : argumentList)
		if(arg.second->required && !arg.second->used)
			throw IncompleteArgsCollectionException();
}

void darknessNight::TextParser::ArgumentParser::parseArg() {
	auto stringArray = getSplittedArg(*iterator);
	auto& argument = getArgument(stringArray[nameIndex]);
	setArgumentValuesIfCorrect(stringArray, argument);
}

std::array<std::string, 2> darknessNight::TextParser::ArgumentParser::getSplittedArg(std::string arg) {
	auto stringArray = StringTools::splitOnFirst(arg, valueDelimiter);
	for(unsigned i = 0; i < stringArray.size(); i++)
		stringArray[i] = StringTools::trimWhitespace(stringArray[i]);
	return stringArray;
}

void darknessNight::TextParser::ArgumentParser::setArgumentValuesIfCorrect(std::array<std::string, 2> stringArray, Argument& argument) {
	if(argument.isCorrect()) {
		clearArgumentAndSetAsUsed(argument);
		setArgumentValueFromIterator(stringArray[valueIndex], argument);
	} else
		doUncorrectArgAction(stringArray[nameIndex]);
}

void darknessNight::TextParser::ArgumentParser::doUncorrectArgAction(std::string argName) noexcept(false) {
	logger(argName);
	if(throwExceptionOnUnexpected)
		throw UnexpectedArgumentException(argName);
}

void darknessNight::TextParser::ArgumentParser::clearArgumentAndSetAsUsed(Argument& argument) {
	argument.clearInfo();
	argument.used = true;
}

darknessNight::TextParser::Argument& darknessNight::TextParser::ArgumentParser::getEmptyArgument() {
	static Argument empty(false);
	empty.clear();
	return empty;
}

void darknessNight::TextParser::ArgumentParser::setArgumentValueFromIterator(std::string value, Argument& argument) {
	if(argument.hasParam) {
		detectAndSetArgumentValueOrArrayParam(value, argument);
	}
}

void darknessNight::TextParser::ArgumentParser::detectAndSetArgumentValueOrArrayParam(std::string value, darknessNight::TextParser::Argument& argument) {
	if(argument.hasArrayParam)
		argument.arrayValues = getArgArrayValuesFromIterator(value);
	else
		argument.value = getArgValueFromIterator(value);
}

std::string darknessNight::TextParser::ArgumentParser::getArgValueFromIterator(std::string value) {
	if(value.empty()) {
		return getNextCorrectValue();
	}
	return value;
}

std::string darknessNight::TextParser::ArgumentParser::getNextCorrectValue() {
	iterator++;
	if(iterator >= iteratorEnd)
		return "";
	if(isAssignOperator(*iterator))
		iterator++;
	return *iterator;
}

std::vector<std::string> darknessNight::TextParser::ArgumentParser::getArgArrayValuesFromIterator(const std::string& value) {
	auto argValue = getArgValueFromIterator(value);
	auto arrayValues = getSplittedArrrayValues(argValue);
	return arrayValues;
}

std::vector<std::string> darknessNight::TextParser::ArgumentParser::getSplittedArrrayValues(std::string argValue) {
	auto arrayValues = StringTools::split(argValue, arrayDelimiter);
	return cleanArrayValues(arrayValues);
}

std::vector<std::string> darknessNight::TextParser::ArgumentParser::cleanArrayValues(std::vector<std::string> arrayValues) {
	for(unsigned i = 0; i < arrayValues.size(); i++)
		arrayValues[i] = StringTools::trimWhitespace(arrayValues[i]);
	return arrayValues;
}

bool darknessNight::TextParser::ArgumentParser::isAssignOperator(std::string value) {
	return StringTools::trimWhitespace(value) == valueDelimiterStr;
}

darknessNight::TextParser::ArgumentRegister& darknessNight::TextParser::ArgumentParser::registerArgument(std::string argName) noexcept(true) {
	auto arg = std::make_shared<Argument>();
	argumentList[argName] = arg;
	return *arg;
}

darknessNight::TextParser::ArgumentInfo& darknessNight::TextParser::ArgumentParser::getArgumentInfo(std::string argName) noexcept(true) {
	return ArgumentParser::getArgument(argName);
}

darknessNight::TextParser::Argument& darknessNight::TextParser::ArgumentParser::getArgument(std::string argName) {
	auto elementIter = argumentList.find(argName);
	if (elementIter != argumentList.end()) {
		return prepareAndReturnArgument(*elementIter->second);
	} else
		return getEmptyArgument();
}

darknessNight::TextParser::Argument& darknessNight::TextParser::ArgumentParser::prepareAndReturnArgument(Argument& arg) {
	arg.setDefaultValueIfNeeded();
	return arg;
}

void darknessNight::TextParser::ArgumentParser::setThrowOnUnexpectedArg(bool throws) noexcept(true) {
	throwExceptionOnUnexpected = throws;
}

void darknessNight::TextParser::ArgumentParser::setLoggerFunc(std::function<void(std::string)> loggerFunc) noexcept(true) {
	logger = loggerFunc;
}

std::map<std::string, std::shared_ptr<const darknessNight::TextParser::ArgumentInfo>> darknessNight::TextParser::ArgumentParser::getArgumentList() noexcept(true) {
	std::map<std::string, std::shared_ptr<const ArgumentInfo>> ret;
	for(auto el : argumentList)
		ret.insert_or_assign(el.first, el.second);
	return ret;
}

darknessNight::TextParser::ArgumentParser& darknessNight::TextParser::ArgumentParser::operator=(const ArgumentParser& other) noexcept(true) {
	logger = other.logger;
	for (auto el : other.argumentList)
		argumentList.insert_or_assign(el.first, std::make_shared<Argument>(*el.second));
	throwExceptionOnUnexpected = other.throwExceptionOnUnexpected;
	return *this;
}
