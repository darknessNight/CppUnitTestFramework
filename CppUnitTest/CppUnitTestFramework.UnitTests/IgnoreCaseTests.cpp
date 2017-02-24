#include "stdafx.h"
#include <CppUnitTestFramework\TestCase.h>
#include <CppUnitTestFramework\TestCaseIgnored.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			TEST_CLASS(IgnoredCaseTests) {
public:
	TEST_METHOD(IgnoredCase_ConstructorHasIgnoreCauseAndName_CheckCorrectRemeberData) {
		TestCasePtr testCase = TestCasePtr(new TestCaseIgnored("name", "IgnoredTest"));
		TestReport report = testCase->runTestAndGetReport();
		StringAssert::AreEqual("Ignored", report.getResult().getCause());
		StringAssert::AreEqual("name", report.getTestName());
		StringAssert::AreEqual("IgnoredTest", report.getResult().getErrorMessage());
	}
			};
		}
	}
}