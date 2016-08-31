#include <CppUnitTestsFramework/Framework.h>

using namespace darknessNight::CppUnitTestFramework;

namespace ExampleProject {
	namespace Tests {
		TEST_CLASS(ClassTests) {

			TEST_METHOD(PassingMethod) {
				Assert::Pass("Passing test!");
			}

			TEST_METHOD(FallingMethod) {
				Assert::Fail("This test has some error!");
			}

			ARG_TEST_METHOD(ArgTest, "FirstArg", "Second", 3);
			ARG_TEST_METHOD(ArgTest, "F", "S", 3);
			ARG_TEST_METHOD(ArgTest, "F", "Se", 3);
			void ArgTest(std::string first, std::string second, unsigned result) {
				Assert::AreEqual(first.size() + second.size(), result);
			}
		};
	}
}