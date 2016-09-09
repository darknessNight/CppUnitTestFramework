#pragma once
#include <CppUnitTestFramework/TestReport.h>

using namespace darknessNight::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace Tests {
			class FakeTestReport :public TestReport {
			public:
				FakeTestReport(std::string name) {
					this->testName = name;
				}

				FakeTestReport(std::string name, int time) {
					this->testName = name;
					this->testResult.setDurationTime(std::chrono::duration_cast<TestResult::TimeDuration>
						(std::chrono::milliseconds(time)));
				}

				FakeTestReport(std::string name, TestCategory cat) {
					this->testName = name;
					this->testCategory = cat;
				}

				FakeTestReport(std::string name, std::string suite) {
					this->testName = name;
					this->testSuite = suite;
				}

				FakeTestReport(std::string name, TestResult res) {
					this->testName = name;
					this->testResult = res;
				}
			};
		}
	}
}