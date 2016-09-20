#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <array>
#include <functional>

namespace darknessNight { namespace TextParser {
	class StringTools {
	public:
		static std::vector<std::string> split(std::string string, char delimiter) {
			std::vector<std::string> array;
			int pos = string.find(delimiter);
			while(pos >= 0) {
				array.push_back(string.substr(0, pos));
				string = string.substr(pos + 1, string.size() - pos);
				pos = string.find(delimiter);
			}
			array.push_back(string);
			return array;
		}

		static std::array<std::string, 2> splitOnFirst(std::string string, char delimiter) {
			std::array<std::string, 2> array;
			int pos = string.find(delimiter);
			if(pos >= 0) {
				array[0] = string.substr(0, pos);
				array[1] = string.substr(pos + 1, string.size() - pos);
			} else
				array[0] = string;
			return array;
		}

		static std::string trimWhitespace(std::string string) {
			string = trimCharAtBegin(string, ' ');
			string = trimCharAtEnd(string, ' ');
			return string;
		}

		static std::string trimCharAtEnd(std::string& string, char charToTrim) {
			int i = string.size() - 1;
			while(i >= 0 && string[i] == charToTrim)
				i--;
			return string.substr(0, i + 1);
		}

		static std::string trimCharAtBegin(std::string& string, char charToTrim) {
			int i = 0;
			while(string.size() > i && string[i] == charToTrim)
				i++;
			return string.substr(i, string.size() - i);
		}
	};

	class ArgumentRegister {
	protected:
		bool hasParam = false;
		bool hasArrayParam = false;
		bool required = false;
		std::string defaultValue;
	public:
		virtual ArgumentRegister& asNameOnly() {
			hasParam = false;
			hasArrayParam = false;
			return *this;
		}

		virtual ArgumentRegister& withParam() {
			hasParam = true;
			hasArrayParam = false;
			return *this;
		}

		virtual ArgumentRegister& withArrayParam() {
			hasParam = true;
			hasArrayParam = true;
			return *this;
		}

		virtual ArgumentRegister& isRequired(bool req=true) {
			required = req;
			return *this;
		}

		ArgumentRegister& withDefaultValue(std::string defValue) {
			defaultValue = defValue;
			return *this;
		}
	};

	class ArgumentInfo {
	protected:
		std::string value;
		std::vector<std::string> arrayValues;
		bool used;
	public:

		ArgumentInfo() {
			ArgumentInfo::clearInfo();
		}

		virtual bool isUsed() const {
			return used;
		}

		template<typename T>
		T getValue() const{
			static_assert(true,"Implementation for this type not exists");
		}

		template<>
		bool getValue() const{
			if(value == "true" || value == "1")
				return true;
			else
				return false;
		}

		template<> std::string getValue() const{
			return value;
		}

		template<typename T> std::vector<T> getArray() const{
			return std::vector<T>();
		}

		template<> std::vector<std::string> getArray() const{
			return arrayValues;
		}

		virtual void clearInfo() {
			used = false;
			value = "";
			arrayValues.clear();
		}
	};

	class Argument :public ArgumentRegister, public ArgumentInfo {
	protected:
		bool correctArg = true;
	protected:
		friend class ArgumentParser;
	public:
		Argument() = default;

		explicit Argument(bool isEmpty) {
			this->correctArg = isEmpty;
		}
	protected:
		bool isCorrect() const {
			return correctArg;
		}

		void setDefaultValueIfNeeded() {
			if (!used)
				value = defaultValue;
		}

		void clear() {
			clearInfo();
		}
	};

	class IncompleteArgsCollectionException:public std::exception {
	private:
		std::string message;
	public:
		IncompleteArgsCollectionException() {
			message = "One or more required arguments is not used";
		}

		explicit IncompleteArgsCollectionException(std::string mess) {
			message = mess;
		}

		char const* what() const override{
			return message.c_str();
		}
	};
		
	class UnexpectedArgumentException:public std::exception {
	private:
		std::string unexpectedArg;
		std::string message;
	public:
		explicit UnexpectedArgumentException(std::string argName) {
			unexpectedArg = argName;
			message = "Detected unexpected argument: \"" + argName + "\"";
		}

		const char* what() {
			return message.c_str();
		}

		std::string getUnexpectedArg() {
			return unexpectedArg;
		}
	};

	class ArgumentParser {
	protected:
		const char valueDelimiter = '=';
		const char arrayDelimiter = ',';
		const std::string valueDelimiterStr = "=";
		const int nameIndex = 0,
				valueIndex = 1;
		std::initializer_list<std::string>::iterator iterator;
		std::map<std::string, std::shared_ptr<Argument>> argumentList;
		std::initializer_list<std::string>::iterator iteratorEnd;
		bool throwExceptionOnUnexpected=false;
		std::function<void(std::string)> logger=[](std::string){};
	public:
		ArgumentRegister& registerArgument(std::string argName) noexcept(true);
		ArgumentInfo& getArgumentInfo(std::string argName) noexcept(true);
		void parse(std::initializer_list<std::string> argsList)noexcept(false);
		void setThrowOnUnexpectedArg(bool throws);
		void setLoggerFunc(std::function<void(std::string)> loggerFunc);
	protected:
		void checkHasAllRequiredArgs();
		void doUncorrectArgAction(std::string argName) noexcept(false);
		std::initializer_list<std::string>::iterator incrementIterator();
		void setArgumentValuesIfCorrect(std::array<std::string, 2> stringArray, Argument& argument);
		void parseArg() noexcept(false);
		static Argument& getEmptyArgument();
		Argument& getArgument(std::string argName);
		std::vector<std::string> getArgArrayValuesFromIterator(const std::string& value);
		std::vector<std::string> cleanArrayValues(std::vector<std::string> arrayValues);
		bool isAssignOperator(std::string value);
		void detectAndSetArgumentValueOrArrayParam(std::string value, Argument& argument);
		std::vector<std::string> getSplittedArrrayValues(std::string argValue);
		void setArgumentValueFromIterator(std::string value, Argument& argument);
		std::string getArgValueFromIterator(std::string value);
		std::string getNextCorrectValue();
		std::array<std::string, 2> getSplittedArg(std::string arg);
		void emptyArgumentAndSetAsUsed(Argument& argument);
	};
}}
