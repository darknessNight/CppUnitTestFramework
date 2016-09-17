#pragma once
#include <msclr\marshal_cppstd.h>
#include <string>
#include <chrono>

namespace darknessNight::CppUnitTest::VSAdapter {
	ref class ConvertTools {
	public:
		static std::string CliStringToCppString(System::String ^str) {
			return msclr::interop::marshal_as<std::string>(str);
		}
		
		static System::String^ CppStringToCliString(std::string str) {
			return gcnew System::String(str.c_str());
		}

		static System::DateTimeOffset ChronoTimePointToDateTimeOffset(std::chrono::high_resolution_clock::time_point time) {
			return System::DateTimeOffset::FromUnixTimeMilliseconds(
				std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count());
		}

		static System::TimeSpan ChronoDurationToTimeSpan(std::chrono::nanoseconds duration) {
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(duration).count()*System::TimeSpan::TicksPerMillisecond / 1000;
			return System::TimeSpan::FromTicks(time);
		}
	};
}