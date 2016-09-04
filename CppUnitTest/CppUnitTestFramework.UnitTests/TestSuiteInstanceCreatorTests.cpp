#include "stdafx.h"
#include <CppUnitTestFramework\TestSuiteInstanceCreator.h>
#include <CppUnitTestFramework\TestSuite.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
			
			TEST_CLASS(TestSuiteInstanceCreatorTests) {
public:
	TEST_METHOD(CreateSuiteTestInstance_HasTestSuiteClassType_CheckReturnInstance) {
		TestSuiteInstanceCreator<TestSuite> creator("SuiteName");
		TestSuitePtr testSuite = creator.createInstance();
		StringAssert::Constains("TestSuite", testSuite->getName());
	}

public:
	TEST_METHOD(getSuiteName_HasTestSuiteClassType_CheckReturnCorrectName) {
		TestSuiteInstanceCreator<TestSuite> creator("SuiteName");
		StringAssert::Constains("SuiteName", creator.getSuiteName());
	}

public:
	TEST_METHOD(CreateInstance_HasTestSuiteClassType_CheckReturnOnlyOneInstance) {
		TestSuiteInstanceCreator<TestSuite> creator("SuiteName");
		TestSuitePtr result1 = creator.createInstance();
		TestSuitePtr result2 = creator.createInstance();
		bool areEqual = result1 == result2;
		Assert::IsTrue(areEqual);
	}
			};
		}
	}
}