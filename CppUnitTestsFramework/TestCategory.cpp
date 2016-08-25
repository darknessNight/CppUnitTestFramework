#include "TestCategory.h"
using namespace darknessNight_CppUnitTestFramework;

TestCategory TestCategory::emptyCategory;

darknessNight_CppUnitTestFramework::TestCategory::TestCategory() {
	name = "";
}

darknessNight_CppUnitTestFramework::TestCategory::TestCategory(std::string suiteName) {
	splitCategoryStringIfNeeded(suiteName);
}

std::string darknessNight_CppUnitTestFramework::TestCategory::getFullName() const {
	std::string name = getName();
	addNextLevelFullName(name);
	return name;
}

void darknessNight_CppUnitTestFramework::TestCategory::addNextLevelFullName(std::string & name) const
{
	if (subCategory != nullptr)
		name += "." + subCategory->getFullName();
}

void darknessNight_CppUnitTestFramework::TestCategory::splitCategoryStringIfNeeded(std::string & suiteName)
{
	int splitPos = suiteName.find(".");
	if (splitPos > 0) {
		saveMultiLevelCategoryString(suiteName, splitPos);
	}
	else {
		saveSimpleCategoryString(suiteName);
	}
}

void darknessNight_CppUnitTestFramework::TestCategory::saveSimpleCategoryString(std::string & suiteName)
{
	name = suiteName;
}

void darknessNight_CppUnitTestFramework::TestCategory::saveMultiLevelCategoryString(std::string & suiteName, int splitPos)
{
	name = suiteName.substr(0, splitPos);
	subCategory = std::shared_ptr<TestCategory>(new TestCategory(suiteName.substr(splitPos + 1)));
}

const TestCategory & darknessNight_CppUnitTestFramework::TestCategory::getSubCategory() const {
	if (subCategory != nullptr)
		return *subCategory;
	else
		return emptyCategory;
}

std::string darknessNight_CppUnitTestFramework::TestCategory::getName() const {
	return name;
}

bool TestCategory::operator==(const TestCategory& category)const {
	return getFullName() == category.getFullName();
}