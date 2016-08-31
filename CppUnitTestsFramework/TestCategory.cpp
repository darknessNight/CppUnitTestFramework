#include "TestCategory.h"
using namespace darknessNight::CppUnitTestFramework;

TestCategory TestCategory::emptyCategory;

darknessNight::CppUnitTestFramework::TestCategory::TestCategory() {
	name = "";
}

darknessNight::CppUnitTestFramework::TestCategory::TestCategory(std::string suiteName) {
	splitCategoryStringIfNeeded(suiteName);
}

std::string darknessNight::CppUnitTestFramework::TestCategory::getFullName() const {
	std::string name = getName();
	addNextLevelFullName(name);
	return name;
}

void darknessNight::CppUnitTestFramework::TestCategory::addNextLevelFullName(std::string & name) const
{
	if (subCategory != nullptr)
		name += "." + subCategory->getFullName();
}

void darknessNight::CppUnitTestFramework::TestCategory::splitCategoryStringIfNeeded(std::string & suiteName)
{
	int splitPos = suiteName.find(".");
	if (splitPos > 0) {
		saveMultiLevelCategoryString(suiteName, splitPos);
	}
	else {
		saveSimpleCategoryString(suiteName);
	}
}

void darknessNight::CppUnitTestFramework::TestCategory::saveSimpleCategoryString(std::string & suiteName)
{
	name = suiteName;
}

void darknessNight::CppUnitTestFramework::TestCategory::saveMultiLevelCategoryString(std::string & suiteName, int splitPos)
{
	name = suiteName.substr(0, splitPos);
	subCategory = std::shared_ptr<TestCategory>(new TestCategory(suiteName.substr(splitPos + 1)));
}

const TestCategory & darknessNight::CppUnitTestFramework::TestCategory::getSubCategory() const {
	if (subCategory != nullptr)
		return *subCategory;
	else
		return emptyCategory;
}

std::string darknessNight::CppUnitTestFramework::TestCategory::getName() const {
	return name;
}

bool TestCategory::operator==(const TestCategory& category)const {
	return getFullName() == category.getFullName();
}