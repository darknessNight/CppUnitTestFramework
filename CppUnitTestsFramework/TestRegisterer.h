#pragma once
#include "TestContainer.h"
#include "TestSuiteInstanceCreator.h"
#include "TestCaseFunc.h"
#include "TestCaseMethod.h"

namespace darknessNight::CppUnitTestFramework {
	class TestExportCollection{
	private:
		static std::unique_ptr<TestContainer> suiteContainer;
	public:
		static TestContainer& getTestContainer() {
			if (suiteContainer == nullptr)
				suiteContainer = std::unique_ptr<TestContainer>(new TestContainer);
			return *suiteContainer;
		}

		static void discoverTest() {
			throw exception();
		}
	};

	class TestRegister {
	protected:
		TestRegister() {}

		TestSuitePtr getTestSuite(std::string &testSuite)
		{
			auto suite = TestExportCollection::getTestContainer().getTestSuiteByName(testSuite);
			return suite;
		}
	};

	template<typename TestSuiteType> class TestClassRegister{
	public:
		TestClassRegister(std::string name){
			std::shared_ptr<TestSuiteCreator> testSuite(new TestSuiteInstanceCreator<TestSuiteType>(name.substr(strlen("class "))));
			TestExportCollection::getTestContainer().addTestSuite(testSuite);
		}
	};

	class TestFuncRegister:TestRegister {
	public:
		TestFuncRegister(std::function<void()> func, string testCaseName, string testSuite) {
			auto suite = getTestSuite(testSuite);
			addTestCase(func, testCaseName, suite);
		}
	protected:
		void addTestCase(std::function<void()> func, std::string &name, darknessNight::CppUnitTestFramework::TestSuitePtr &suite)
		{
			TestCasePtr testCase(new TestCaseFunc(func, name));
			suite->addTestCase(testCase);
		}
	};

	class TestMethodRegister:TestRegister {

	};
}