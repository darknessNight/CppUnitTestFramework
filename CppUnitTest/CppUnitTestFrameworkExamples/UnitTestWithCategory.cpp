#include <CppUnitTestFramework/Framework.h>

using namespace darknessNight::CppUnitTestFramework;

namespace ExampleProject {
	namespace Tests {
		TEST_CLASS_WITH_CATEGORY(ClassTestsWithCategory, "UnitTest.Unit.TestSample") {

			TEST_METHOD(PassingMethod) {
				Assert::Pass("Passing test!");
			}

			TEST_METHOD(FallingMethod) {
				Assert::Fail("This test has some error!");
			}

		};
	}
}