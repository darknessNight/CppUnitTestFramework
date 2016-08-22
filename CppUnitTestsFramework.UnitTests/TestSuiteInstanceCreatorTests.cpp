#include "stdafx.h"
#include <CppUnitTestsFramework\TestSuiteInstanceCreator.h>
#include <CppUnitTestsFramework\TestSuiteClass.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests {
	TEST_CLASS(TestSuiteInstanceCreatorTests)
	{
	public:
		TEST_METHOD(CreateSuiteTestInstance_HasTestSuiteClassType_CheckReturnInstance)
		{
			TestSuiteInstanceCreator<TestSuiteClass> creator("SuiteName");
			TestSuitePtr testSuite=creator.createInstance();
			StringAssert::Constains("TestSuiteClass", testSuite->getName());
		}

	public:
		TEST_METHOD(getSuiteName_HasTestSuiteClassType_CheckReturnCorrectName)
		{
			TestSuiteInstanceCreator<TestSuiteClass> creator("SuiteName");
			StringAssert::Constains("SuiteName", creator.getSuiteName());
		}

	public:
		TEST_METHOD(CreateInstance_HasTestSuiteClassType_CheckReturnOnlyOneInstance)
		{
			TestSuiteInstanceCreator<TestSuiteClass> creator("SuiteName");
			TestSuitePtr result1 = creator.createInstance();
			TestSuitePtr result2 = creator.createInstance();
			bool areEqual=result1 == result2;
			Assert::IsTrue(areEqual);
		}
	};
}