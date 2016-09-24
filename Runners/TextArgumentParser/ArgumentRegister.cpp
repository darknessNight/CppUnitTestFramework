#include "ArgumentRegister.h"

 darknessNight::TextParser::ArgumentRegister& darknessNight::TextParser::ArgumentRegister::asNameOnly() {
	hasParam = false;
	hasArrayParam = false;
	return *this;
}

 darknessNight::TextParser::ArgumentRegister& darknessNight::TextParser::ArgumentRegister::withParam() {
	hasParam = true;
	hasArrayParam = false;
	return *this;
}

 darknessNight::TextParser::ArgumentRegister& darknessNight::TextParser::ArgumentRegister::withArrayParam() {
	hasParam = true;
	hasArrayParam = true;
	return *this;
}

 darknessNight::TextParser::ArgumentRegister& darknessNight::TextParser::ArgumentRegister::isRequired(bool req) {
	required = req;
	return *this;
}

 darknessNight::TextParser::ArgumentRegister& darknessNight::TextParser::ArgumentRegister::withDefaultValue(std::string defValue) {
	defaultValue = defValue;
	return *this;
}
