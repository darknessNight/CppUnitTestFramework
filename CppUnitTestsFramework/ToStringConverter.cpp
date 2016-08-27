#include "ToStringConverter.h"

using namespace darknessNight_CppUnitTestFramework;
std::unique_ptr<ToStringConverter> ToStringConverter::instance=std::make_unique<ToStringConverter>();

darknessNight_CppUnitTestFramework::ToStringConverter::ToStringConverter() {
	registerConverter<int>(std::to_string);
	registerConverter<unsigned int>(std::to_string);
	registerConverter<short>([](short obj) {return std::to_string(obj); });
	registerConverter<unsigned short>([](unsigned short obj) {return std::to_string(obj); });
	registerConverter<long>(std::to_string);
	registerConverter<unsigned long>(std::to_string);
	registerConverter<long long>(std::to_string);
	registerConverter<unsigned long long>(std::to_string);
	registerConverter<double>(std::to_string);
	registerConverter<long double>(std::to_string);
	registerConverter<float>(std::to_string);
	registerConverter<std::string>(&ToStringConverter::StringToString);
	registerConverter<std::wstring>(&ToStringConverter::WStringToString);
	registerConverter<bool>([](bool cond)->std::string {return cond ? "True" : "False"; });
}

std::string darknessNight_CppUnitTestFramework::ToStringConverter::ToString(const char * obj) {
	return StringToString(obj);
}

std::string darknessNight_CppUnitTestFramework::ToStringConverter::ToString(const wchar_t * obj) {
	return WStringToString(obj);
}

std::string darknessNight_CppUnitTestFramework::ToStringConverter::StringToString(std::string obj) {
	return "\"" + obj + "\"";
}

std::string darknessNight_CppUnitTestFramework::ToStringConverter::WStringToString(std::wstring obj) {
	std::string str;
	for (auto c = obj.begin(); c != obj.end(); c++) {
		str += *c;
	}
	return "\"" + str + "\"";
}
