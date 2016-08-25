#pragma once
#include<string>
#include <memory>
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class TestCategory {
	private:
		string name;
		shared_ptr<TestCategory> subCategory=nullptr;
		static TestCategory emptyCategory;
	public:
		TestCategory();
		TestCategory(string suiteName);
		string getFullName() const;
		void addNextLevelFullName(std::string &name) const;
		const TestCategory& getSubCategory() const;
		string getName() const;
		bool operator==(const TestCategory& category) const;
	private:
		void splitCategoryStringIfNeeded(std::string &suiteName);
		void saveSimpleCategoryString(std::string &suiteName);
		void saveMultiLevelCategoryString(std::string &suiteName, int splitPos);
	};
}