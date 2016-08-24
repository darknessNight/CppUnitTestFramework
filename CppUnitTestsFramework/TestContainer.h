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
			else throw NotFoundException("Suite \"+"+name+"+\" not exists throwed in: " __FILE__);
		}

		void registerTestCaseToUnnamedSuite(TestCasePtr testCase) {
			registerTestCase("", testCase);
		}

		void registerTestCase(string testSuite, TestCasePtr testCase) {
			checkTestSuiteName(testSuite);
			mapArray[testSuite]->registerTestCase(testCase);
		}

		void registerSetUp(string testSuite, std::function<void()> setUp) {
			checkTestSuiteName(testSuite);
			mapArray[testSuite]->registerSetUp(setUp);
		}

		void registerTearDown(string testSuite, std::function<void()> tearDown) {
			checkTestSuiteName(testSuite);
			mapArray[testSuite]->registerTearDown(tearDown);
		}
	private:

		void checkTestSuiteName(std::string &testSuite)
		{
			testSuite = setUnnamedIfNotHaveName(testSuite);
			throwExceptionIfNotExistsSuite(testSuite);
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