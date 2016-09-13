#pragma once
#include <msclr\marshal_cppstd.h>
#include <string>

namespace darknessNight::CppUnitTest::VSAdapter {
	ref class ConvertTools {
	public:
		static std::string CliStringToCppString(System::String ^str) {
			return msclr::interop::marshal_as<std::string>(str);
		}
		
		static System::String^ CppStringToCliString(std::string str) {
			return gcnew System::String(str.c_str());
		}
	};
}