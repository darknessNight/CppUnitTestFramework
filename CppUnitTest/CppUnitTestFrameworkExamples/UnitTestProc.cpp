#include <CppUnitTestFramework/Framework.h>

using namespace darknessNight::CppUnitTestFramework;

namespace Test {
	TEST_SUITE(TestPackage);
	TEST_SUITE_WITH_CATEGORY(TestPackageWithCategory, "FuncSuite.Unit.Tests");

		TEST_FUNCTION(PassingMethodWithoutSuite) {
			Assert::Pass("Passing test!");
		}

		TEST_FUNCTION_IN_SUITE(PassingFunc,"TestPackage") {
			Assert::Pass("Passing test!");
		}

		TEST_FUNCTION_IN_SUITE(FallingFunc, "TestPackage") {
			Assert::Fail("This test has some error!");
		}

		TEST_FUNCTION_DECLARE(NonDefinedTest);


		void ArgFunc(int number, std::string message);
		ARG_TEST_FUNCTION_IN_SUITE(ArgFunc, "TestPackageWithCategory", 3, "");
		ARG_TEST_FUNCTION_IN_SUITE(ArgFunc, "TestPackageWithCategory", 2, "TestFall");
		ARG_TEST_FUNCTION_IN_SUITE(ArgFunc, "TestPackage", 1, "Elo");
		void ArgFunc(int number, std::string message) {
			Assert::AreEqual(2, number, message);
		}


		void NonDefinedTest() {
			Assert::Pass("Passing test!");
		}
}