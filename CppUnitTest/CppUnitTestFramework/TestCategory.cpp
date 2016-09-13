#include "TestCategory.h"
using namespace darknessNight::CppUnitTestFramework;

TestCategory TestCategory::emptyCategory;

TestCategory::TestCategory() {
	name = "";
}

TestCategory::TestCategory(std::string suiteName) {
	splitCategoryStringIfNeeded(suiteName);
}

std::string TestCategory::getFullName() const {
	std::string name = getName();
	addNextLevelFullName(name);
	return name;
}

void TestCategory::addNextLevelFullName(std::string & name) const
{
	if (subCategory != nullptr)
		name += "." + subCategory->getFullName();
}

void TestCategory::splitCategoryStringIfNeeded(std::string & suiteName)
{
	int splitPos = suiteName.find(".");
	if (splitPos > 0) {
		saveMultiLevelCategoryString(suiteName, splitPos);
	}
	else {
		saveSimpleCategoryString(suiteName);
	}
}

void TestCategory::saveSimpleCategoryString(std::string & suiteName)
{
	name = suiteName;
}

void TestCategory::saveMultiLevelCategoryString(std::string & suiteName, int splitPos)
{
	name = suiteName.substr(0, splitPos);
	subCategory = std::shared_ptr<TestCategory>(new TestCategory(suiteName.substr(splitPos + 1)));
}

const TestCategory & TestCategory::getSubCategory() const {
	if (subCategory != nullptr)
		return *subCategory;
	else
		return emptyCategory;
}

std::string TestCategory::getName() const {
	return name;
}

bool TestCategory::operator==(const TestCategory& category)const {
	return getFullName() == category.getFullName();
}