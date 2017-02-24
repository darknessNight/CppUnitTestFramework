#pragma once
#include <string>

namespace darknessNight { namespace TextParser {
	class ArgumentRegister {
	protected:
		bool hasParam = false;
		bool hasArrayParam = false;
		bool required = false;
		std::string defaultValue;
	public:
		virtual ArgumentRegister& asNameOnly();
		virtual ArgumentRegister& withParam();
		virtual ArgumentRegister& withArrayParam();
		virtual ArgumentRegister& isRequired(bool req = true);
		ArgumentRegister& withDefaultValue(std::string defValue);
	};
}}
