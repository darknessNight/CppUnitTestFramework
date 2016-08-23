#pragma once
#include "TestSuiteInstanceCreator.h"
namespace darknessNight::CppUnitTestFramework {
	class TestContainer {
		std::map<string, std::shared_ptr<TestSuiteCreator>> mapArray;
		std::shared_ptr<TestSuiteCreator> unnamedSuite;
	public:
		TestContainer() {
			unnamedSuite = std::shared_ptr<TestSuiteCreator>(new TestSuiteInstanceCreator<TestSuite>("Unnamed"));
			addTestSuite(unnamedSuite);
		}

		void addTestSuite(std::shared_ptr<TestSuiteCreator> creator) {
			string name = creator->getSuiteName();
			mapArray[name] = creator;
		}

		TestSuitePtr getTestSuiteByName(std::string name) {
			name = setUnnamedIfNotHaveName(name);
			if (keyExistsInArray(name))
				return mapArray[name]->createInstance();
			else throw NotFoundException("Suite not exists throwed in: " __FILE__);
		}

		void registerTestCaseToUnnamedSuite(TestCasePtr testCase) {
			registerTestCase("", testCase);
		}

		void registerTestCase(string testSuite, TestCasePtr testCase) {
			testSuite = setUnnamedIfNotHaveName(testSuite);
			addTestCaseToSuite(testSuite, testCase);
		}
	private:
		void addTestCaseToSuite(std::string &testSuite, darknessNight::CppUnitTestFramework::TestCasePtr &testCase){
			throwExceptionIfNotExistsSuite(testSuite);
			saveTestCase(testSuite, testCase);
		}

		void saveTestCase(std::string & name, darknessNight::CppUnitTestFramework::TestCasePtr & testCase)
		{
			TestSuitePtr testSuite=mapArray[name]->createInstance();
			testSuite->addTestCase(testCase);
		}

		void throwExceptionIfNotExistsSuite(std::string & testSuite)
		{
			if (!keyExistsInArray(testSuite))
				throw NotFoundException("Not found suite with this name: " + testSuite + " in registerTestCase");
		}

		string setUnnamedIfNotHaveName(string name) {
			if (name.size() <= 0)
				name = "Unnamed";
			return name;
		}

		bool keyExistsInArray(string name) {
			return mapArray.find(name) != mapArray.end();
		}
	};
}