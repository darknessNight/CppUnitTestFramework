#pragma once
#include <string>
#include <memory>

namespace darknessNight_CppUnitTestFramework {
	class TestCategory {
	private:
		std::string name;
		std::shared_ptr<TestCategory> subCategory=nullptr;
		static TestCategory emptyCategory;
	public:
		TestCategory();
		TestCategory(std::string suiteName);
		std::string getFullName() const;
		void addNextLevelFullName(std::string &name) const;
		const TestCategory& getSubCategory() const;
		std::string getName() const;
		bool operator==(const TestCategory& category) const;
	private:
		void splitCategoryStringIfNeeded(std::string &suiteName);
		void saveSimpleCategoryString(std::string &suiteName);
		void saveMultiLevelCategoryString(std::string &suiteName, int splitPos);
	};
}