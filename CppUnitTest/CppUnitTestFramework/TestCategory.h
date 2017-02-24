#pragma once
#include <string>
#include <memory>

namespace darknessNight {
	namespace CppUnitTestFramework {
		class TestCategory {
		private:
			std::string name;
			std::unique_ptr<TestCategory> subCategory = nullptr;
		public:
			TestCategory();
			TestCategory(const TestCategory& other);
			TestCategory(std::string suiteName);
			TestCategory& operator=(const TestCategory& other);
			bool operator==(const TestCategory& category) const;
			std::string getFullName() const;
			void addNextLevelFullName(std::string &name) const;
			const TestCategory& getSubCategory() const;
			std::string getName() const;
		private:
			void splitCategoryStringIfNeeded(std::string &suiteName);
			void saveSimpleCategoryString(std::string &suiteName);
			void saveMultiLevelCategoryString(std::string &suiteName, int splitPos);
		};
	}
}