#include "stdafx.h"
#include "../TestsRunner/TestReportCategoryContainer.h"
#include "FakeTestReport.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace darknessNight {
	namespace TestsRunner {
		namespace Tests {
			TEST_CLASS(CategoryContainerTests) {
				TEST_METHOD(getSubCats_HasTwoTestWithTwoLevelCat_CheckIsCorrect) {
					CategoryContainer container;
					container.addReportToCat(FakeTestReport("Test1", TestCategory("Cat1.Subcat1")));
					container.addReportToCat(FakeTestReport("Test2", TestCategory("Cat1.Subcat2")));

					auto subCats = container.getSubCats();
					Assert::AreEqual<unsigned>(1, subCats.size());
					Assert::AreEqual<unsigned>(2, subCats["Cat1"].getSubCats().size());
				}

				TEST_METHOD(getTests_HasTwoTestWithTwoLevelCat_CheckIsCorrect) {
					CategoryContainer container;
					container.addReportToCat(FakeTestReport("Test1", TestCategory("Cat1.Subcat1")));
					container.addReportToCat(FakeTestReport("Test2", TestCategory("Cat1.Subcat2")));

					Assert::AreEqual<unsigned>(0, container.getTestsReports().size());
					Assert::AreEqual<unsigned>(1, container["Cat1"]["Subcat1"].getTestsReports().size());
					Assert::AreEqual<unsigned>(1, container["Cat1"]["Subcat2"].getTestsReports().size());
				}

			};
		}
	}
}