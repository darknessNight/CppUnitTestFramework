#include "PrefixedArgumentParser.h"

darknessNight::TextParser::PrefixedArgumentParser::PrefixedArgumentParser(std::initializer_list<std::string> prefixes) {
	setArgPrefix(prefixes);
}

darknessNight::TextParser::PrefixedArgumentParser::PrefixedArgumentParser(const ArgumentParser& baseParser, std::initializer_list<std::string> prefixes) {
	*static_cast<ArgumentParser*>(this) = baseParser;
	setArgPrefix(prefixes);
}

void darknessNight::TextParser::PrefixedArgumentParser::setArgPrefix(std::initializer_list<std::string> prefixes) {
	argsPrefixes = prefixes;
}

void darknessNight::TextParser::PrefixedArgumentParser::setRequiredUnnamedArgs(int count) {
	minUnnamedArgs = count;
	if(maxUnnamedArgs < minUnnamedArgs)
		maxUnnamedArgs = minUnnamedArgs;
}

void darknessNight::TextParser::PrefixedArgumentParser::setMaxUnnamedArgs(int count) {
	maxUnnamedArgs = count;
	if(minUnnamedArgs > maxUnnamedArgs)
		minUnnamedArgs = maxUnnamedArgs;
}

std::vector<std::string> darknessNight::TextParser::PrefixedArgumentParser::getUnnamedValues() {
	return unnamedArgs;
}

darknessNight::TextParser::Argument& darknessNight::TextParser::PrefixedArgumentParser::setUnnamedArgIfCan(std::string argName) {
	if(setUnnamedArg(argName))
		return getUnnamedArgument();
	else
		return getEmptyArgument();
}

darknessNight::TextParser::Argument& darknessNight::TextParser::PrefixedArgumentParser::getArgument(std::string argName) {
	auto usedPrefix = StringTools::beginWith(argName, argsPrefixes);
	if(usedPrefix >= 0) {
		return getStardardArgument(argName, usedPrefix);
	} else {
		return setUnnamedArgIfCan(argName);
	}
}

darknessNight::TextParser::Argument& darknessNight::TextParser::PrefixedArgumentParser::getStardardArgument(std::string& argName, int usedPrefix) {
	argName = StringTools::trimStringAtBegin(argName, argsPrefixes[usedPrefix]);
	return ArgumentParser::getArgument(argName);
}

void darknessNight::TextParser::PrefixedArgumentParser::checkHasAllRequiredArgs() {
	ArgumentParser::checkHasAllRequiredArgs();
	if (unnamedArgs.size() < minUnnamedArgs)
		throw IncompleteArgsCollectionException("Has not all required unnamed args");
}

bool darknessNight::TextParser::PrefixedArgumentParser::setUnnamedArg(std::string argName) {
	if(unnamedArgs.size() < maxUnnamedArgs) {
		unnamedArgs.push_back(argName);
		return true;
	} else
		return false;
}

darknessNight::TextParser::Argument& darknessNight::TextParser::PrefixedArgumentParser::getUnnamedArgument() {
	static Argument unnamed;
	return unnamed;
}
