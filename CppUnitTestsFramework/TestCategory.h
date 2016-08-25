#pragma once
#include<string>
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class TestCategory {
	private:
		string name;
		shared_ptr<TestCategory> subCategory=nullptr;
	public:
		TestCategory() {}

		TestCategory(string suiteName) {
			int splitPos=suiteName.find(".");
			name = suiteName.substr(0, splitPos);
			subCategory = shared_ptr<TestCategory>(new TestCategory(suiteName.substr(splitPos + 1)));
		}

		string getFullName() {
			string name = getName();
			if (subCategory != nullptr)
				name += "." + subCategory->getName();
			return name;
		}

		string getName() {
			return name;
		}
	};
}