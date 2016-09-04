#include "stdafx.h"
#include <CppUnitTestFramework\TestCategory.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace darknessNight {
	namespace CppUnitTestFramework {
		namespace UnitTests {
	TEST_CLASS(TestCategoryTests)
	{
	public:
		TEST_METHOD(TestCategory_HasOneLevelCategoryString_CheckHasCorrectSplit){
			TestCategory cat("OneCategory");
			Assert::AreEqual(std::string("OneCategory"), cat.getName());
			Assert::AreEqual(std::string("OneCategory"), cat.getFullName());
			Assert::AreEqual(std::string(""), cat.getSubCategory().getName());
		}

		TEST_METHOD(TestCategory_HasMultiLevelCategoryString_CheckHasCorrectSplit) {
			TestCategory cat("OneCategory.TwoCategory.ThreeCategory");
			Assert::AreEqual(std::string("OneCategory"), cat.getName(), L"SimpleName");
			Assert::AreEqual(std::string("OneCategory.TwoCategory.ThreeCategory"), cat.getFullName(), L"FullName");
			Assert::AreEqual(std::string("TwoCategory"), cat.getSubCategory().getName(), L"SecondCategoryName");
		}

		TEST_METHOD(TestCategoryEquals_CheckMultiCategoryIsEqual_CheckReturnTrue) {
			TestCategory cat1("OneCategory.TwoCategory.ThreeCategory");
			TestCategory cat2("OneCategory.TwoCategory.ThreeCategory");
			Assert::IsTrue(cat1 == cat2);
		}
	};
}}}