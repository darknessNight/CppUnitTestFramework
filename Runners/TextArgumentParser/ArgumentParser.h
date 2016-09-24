#pragma once
#include <map>
#include <memory>
#include <functional>
#include "Exceptions.h"
#include "StringTools.h"
#include "Argument.h"

namespace darknessNight { namespace TextParser {
	class ArgumentParser {
	protected:
		const char valueDelimiter = '=';
		const char arrayDelimiter = ',';
		const std::string valueDelimiterStr = "=";
		const int nameIndex = 0,
				valueIndex = 1;

		std::map<std::string, std::shared_ptr<Argument>> argumentList;
		std::initializer_list<std::string>::iterator iterator;
		std::initializer_list<std::string>::iterator iteratorEnd;
		bool throwExceptionOnUnexpected=false;
		std::function<void(std::string)> logger=[](std::string){};
	public:
		ArgumentRegister& registerArgument(std::string argName) noexcept(true);
		ArgumentInfo& getArgumentInfo(std::string argName) noexcept(true);
		void parse(std::initializer_list<std::string> argsList)noexcept(false);
		std::map<std::string, std::shared_ptr<const ArgumentInfo>> getArgumentList() noexcept(true);
		ArgumentParser& operator=(const ArgumentParser& other) noexcept(true);

		void setThrowOnUnexpectedArg(bool throws) noexcept(true);
		void setLoggerFunc(std::function<void(std::string)> loggerFunc) noexcept(true);
	protected:
		virtual void checkHasAllRequiredArgs();
		void doUncorrectArgAction(std::string argName) noexcept(false);

		std::initializer_list<std::string>::iterator incrementIterator();
		void setArgumentValuesIfCorrect(std::array<std::string, 2> stringArray, Argument& argument);
		virtual void parseArg() noexcept(false);
		static Argument& getEmptyArgument();
		virtual Argument& getArgument(std::string argName);
		Argument& ArgumentParser::prepareAndReturnArgument(Argument& arg);
		std::vector<std::string> getArgArrayValuesFromIterator(const std::string& value);
		std::vector<std::string> cleanArrayValues(std::vector<std::string> arrayValues);
		bool isAssignOperator(std::string value);
		void detectAndSetArgumentValueOrArrayParam(std::string value, Argument& argument);
		std::vector<std::string> getSplittedArrrayValues(std::string argValue);
		void setArgumentValueFromIterator(std::string value, Argument& argument);
		std::string getArgValueFromIterator(std::string value);
		std::string getNextCorrectValue();
		std::array<std::string, 2> getSplittedArg(std::string arg);
		void clearArgumentAndSetAsUsed(Argument& argument);
	};
}}
