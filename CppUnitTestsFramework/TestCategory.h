#pragma once
#include<string>
using namespace std;
namespace darknessNight::CppUnitTestFramework {
	class TestCategory {
	private:
		string name;
	public:
		TestCategory() {}

		TestCategory(string myName) {
			name = myName;
		}

		string getName() {
			return name;
		}
	};
}