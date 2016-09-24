#pragma once
#include <string>
#include "ArgumentParser.h"

namespace darknessNight { namespace TextParser {
	class PrefixedArgumentParser :public ArgumentParser {
	protected:
		std::vector<std::string> argsPrefixes;
		int minUnnamedArgs = 0;
		int maxUnnamedArgs = 0;
		std::vector<std::string> unnamedArgs;
	public:
		PrefixedArgumentParser(std::initializer_list<std::string> prefixes);
		PrefixedArgumentParser(const ArgumentParser&, std::initializer_list<std::string> prefixes);
		void setArgPrefix(std::initializer_list<std::string> prefixes);
		void setRequiredUnnamedValues(int count);
		void setMaxUnnamedArgs(int count);
		std::vector<std::string> getUnnamedValues();
	protected:
		bool setUnnamedArg(std::string argName);
		Argument& getUnnamedArgument();
		Argument& getArgument(std::string argName) override;
		void checkHasAllRequiredArgs() override;
	};
}}
