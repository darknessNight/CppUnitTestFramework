#pragma once
#include <CppUnitTestsFramework\FunctionTester.h>
#include <CppUnitTestsFramework\AssertExceptions.h>

namespace darknessNight::CppUnitTestFramework::UnitTests {
	const string methodFailedString = "MethodFailed";
	static void testDoNothingFunc() {
	}

	static void testCollapseFunc() {
		throw exception(methodFailedString.c_str());
	}

	static void testThrowingAssertFunc() {
		throw AssertException(methodFailedString);
	}

	class FakeFunctionTester : public FunctionTester {
	public:
		bool setUpRunned = false;
		bool tearDownRunned = false;
	public:
		FakeFunctionTester(FunctionTester::TestMethod method) :FunctionTester(method) {
		}

		void setUp() override {
			setUpRunned = true;
			tearDownRunned = false;
		}

		void tearDown() override {
			tearDownRunned = true;
		}
	};


	class SpecialException :public std::exception {
	public:
		SpecialException(string message) :exception(message.c_str()) {}
	};

	class FakeCollapseFunctionTester : public FunctionTester {
	public:
		bool collapseSetUp = false;
		bool collapseTearDown = false;
	public:
		FakeCollapseFunctionTester() :FunctionTester(testDoNothingFunc) {
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