#pragma once
#include "TestSuiteInstanceCreator.h"
#include "Exceptions.h"

namespace darknessNight_CppUnitTestFramework {
	class TestContainer {
		std::map<std::string, std::shared_ptr<TestSuiteCreator>> mapArray;
		std::shared_ptr<TestSuiteCreator> unnamedSuite;
	public:
		TestContainer();
		void addTestSuite(std::shared_ptr<TestSuiteCreator> creator);
		TestSuitePtr getTestSuiteByName(std::string name);
		std::vector<std::string> getTestSuiteList();
		void registerTestCaseToUnnamedSuite(TestCasePtr testCase);
		void registerTestCase(std::string testSuite, TestCasePtr testCase);
		void registerSetUp(std::string testSuite, std::function<void()> setUp);
		void registerTearDown(std::string testSuite, std::function<void()> tearDown);
	private:
		void checkTestSuiteName(std::string &testSuite);
		void throwExceptionIfNotExistsSuite(std::string & testSuite);
		std::string setUnnamedIfNotHaveName(std::string name);
		bool keyExistsInArray(std::string name);
	};
}