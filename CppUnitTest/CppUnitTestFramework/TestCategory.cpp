#include "TestCategory.h"
using namespace darknessNight::CppUnitTestFramework;

TestCategory::TestCategory() {
	name = "";
}

TestCategory::TestCategory(const TestCategory & other) {
	this->name = other.name;
	if(other.subCategory!=nullptr)
		this->subCategory = std::unique_ptr<TestCategory>(new TestCategory(*other.subCategory));
}

TestCategory::TestCategory(std::string suiteName) {
	splitCategoryStringIfNeeded(suiteName);
}

TestCategory& TestCategory::operator=(const TestCategory& other) {
	TestCategory newObj(other);
	this->name = other.name;
	this->subCategory.swap(newObj.subCategory);
	return *this;
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
	subCategory.reset(new TestCategory(suiteName.substr(splitPos + 1)));
}

const TestCategory & TestCategory::getSubCategory() const {
	static TestCategory empty("");
	if (subCategory != nullptr)
		return *subCategory;
	else
		return empty;
}

std::string TestCategory::getName() const {
	return name;
}

bool TestCategory::operator==(const TestCategory& category)const {
	return getFullName() == category.getFullName();
}