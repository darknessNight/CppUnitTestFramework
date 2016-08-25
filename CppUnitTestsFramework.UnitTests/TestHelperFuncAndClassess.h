#pragma once
#include <CppUnitTestsFramework\FunctionTester.h>
#include <CppUnitTestsFramework\AssertExceptions.h>

namespace darknessNight_CppUnitTestFramework::UnitTests {
	const std::string methodFailedString = "MethodFailed";
	static void testDoNothingFunc() {
	}

	static void testCollapseFunc() {
		throw exception(methodFailedString.c_str());
	}

	static void testThrowingAssertFunc() {
		throw AssertException(methodFailedString);
	}

	class MockFunctionTester : public FunctionTester {
	public:
		bool setUpRunned = false;
		bool tearDownRunned = false;
	public:
		MockFunctionTester(FunctionTester::TestMethod method) :FunctionTester(method) {
		}

		void setUp() override {
			setUpRunned = true;
			tearDownRunned = false;
		}

		void tearDown() override {
			tearDownRunned = true;
		}
	};


	class SpecialException :public exception {
	public:
		SpecialException(std::string message) :exception(message.c_str()) {}
	};

	class FakeFunctionTester : public FunctionTester {
	public:
		bool collapseSetUp = false;
		bool collapseTearDown = false;
		bool returnFakeResult = false;
		TestResult returnResult;
	public:
		FakeFunctionTester() :FunctionTester(testDoNothingFunc), returnResult(true) {
		}

		TestResult runTest() override {
			if(!returnFakeResult)
				return FunctionTester::runTest();
			else {
				FunctionTester::runTest();
				return returnResult;
			}
		}

		void setUp() override {
			if (collapseSetUp)
				throw SpecialException(methodFailedString);
		}

		void tearDown() override {
			if (collapseTearDown)
				throw SpecialException(methodFailedString);
		}
	};
}