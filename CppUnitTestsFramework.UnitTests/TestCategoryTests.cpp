#include "stdafx.h"
#include "CppUnitTestsFramework\TestCategory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight::CppUnitTestFramework::UnitTests
{		
	TEST_CLASS(TestCategoryTests)
	{
	public:
		TEST_METHOD(TestCategory_HasOneLevelCategoryString_CheckHasCorrectSplit){
			TestCategory cat("OneCategory");
			Assert::AreEqual(string("OneCategory"), cat.getName());
			Assert::AreEqual(string("OneCategory"), cat.getFullName());
			Assert::AreEqual(string(""), cat.getSubCategory().getName());
		}

		TEST_METHOD(TestCategory_HasMultiLevelCategoryString_CheckHasCorrectSplit) {
			TestCategory cat("OneCategory.TwoCategory.ThreeCategory");
			Assert::AreEqual(string("OneCategory"), cat.getName(), L"SimpleName");
			Assert::AreEqual(string("OneCategory.TwoCategory.ThreeCategory"), cat.getFullName(), L"FullName");
			Assert::AreEqual(string("TwoCategory"), cat.getSubCategory().getName(), L"SecondCategoryName");
		}

		TEST_METHOD(TestCategoryEquals_CheckMultiCategoryIsEqual_CheckReturnTrue) {
			TestCategory cat1("OneCategory.TwoCategory.ThreeCategory");
			TestCategory cat2("OneCategory.TwoCategory.ThreeCategory");
			Assert::IsTrue(cat1 == cat2);
		}
	};
}