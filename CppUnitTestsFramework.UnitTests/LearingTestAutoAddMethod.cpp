#include "stdafx.h"
#include "LearningTestAutoAddMethod.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	
	TEST_CLASS(LearingAutoAddMethodTest)
	{
	public:
		TEST_METHOD(TestGetMethodFromCreatedObject) {
			TestSendOwnMethodToOtherClass test;
			std::bind(StaticVarsContainer::func, test)();
			Assert::IsTrue(StaticVarsContainer::enabled);
		}

		TEST_METHOD(TestGetClassNameFromNotDefClass) {
			StringAssert::Constains("CppUnitTestFramework::UnitTests::NoDefClass", testOverLimits.testName);
		}

		TEST_METHOD(TestGetClassNameInnerThisClass) {
			StringAssert::Constains("CppUnitTestFramework::UnitTests::NoDefClass", testOverLimits.testName);
		}
	};
}