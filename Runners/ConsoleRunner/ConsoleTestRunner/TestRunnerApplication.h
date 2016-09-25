#pragma once
#include "stdafx.h"
#include <iostream>
#include <TestsRunner/TestDiscover.h>
#include <TestsRunner/TestExecutor.h>
#include "ConsoleTestRunner.h"
#include <TestsRunner/ConsoleMessageLogger.h>
#include <TextArgumentParser/PrefixedArgumentParser.h>

using namespace darknessNight::TestsRunner;
using namespace darknessNight::Filesystem;
using namespace darknessNight::SharedLibrary;
using namespace darknessNight::TextParser;

namespace darknessNight { namespace ConsoleTestRunner {
	class TestRunnerApplication {
	private:
		PrefixedArgumentParser parser = PrefixedArgumentParser({"-","--","/"});
		std::shared_ptr<Directory> dirPtr = std::make_shared<Directory>(".");
		std::shared_ptr<DynamicLibrary> dynamicLibraries = std::make_shared<DynamicLibrary>();
		std::shared_ptr<MessageLogger> logger;
	public:
		int startProgram(int argc, const char* argv[]) {
			parserArguments(argc, argv);
			return runTests();
		}

	private:
		void parserArguments(int argc, const char** argv) {
			prepareParser();
			parser.parse(convertCArgsToVector(argc, argv));
		}

		void prepareParser() {
			parser.setMaxUnnamedArgs(1);
		}

		std::vector<std::string> convertCArgsToVector(int argc, const char** argv) {
			std::vector<std::string> args;
			args.reserve(argc);
			for(int i = 1; i < argc; i++)
				args.push_back(argv[i]);
			return args;
		}

		int runTests() {
			TestSuite::TestReportArray testReports = findAndExecuteTests();
			return showAndGetResults(testReports);
		}

		TestSuite::TestReportArray findAndExecuteTests() {
			std::vector<std::string> dirs;
			std::vector<std::string> extensions;
			prepareDependencies(dirs, extensions);
			auto tests = findTests(dirs, extensions);
			return executeTests(tests);
		}

		std::vector<TestCasePtr> findTests(std::vector<std::string> dirs, std::vector<std::string> extensions) {
			TestDiscover discover(dirPtr, dynamicLibraries, logger);
			discover.findAll(dirs, extensions);
			return discover.getTestsList();
		}

		TestSuite::TestReportArray executeTests(std::vector<TestCasePtr> tests) {
			TestExecutor executor(dirPtr, dynamicLibraries, logger);
			return executor.runTests(tests);
		}

		void prepareDependencies(std::vector<std::string>& dirs, std::vector<std::string>& extensions) {
			logger = chooseMessageLogger();
			dirs = getSearchDirs();
			extensions = getSearchExtensions();
		}

		std::shared_ptr<MessageLogger> chooseMessageLogger() {
			if(parser.getArgumentInfo("quiet").isUsed())
				return std::make_shared<QuietMessageLogger>();
			else
				return std::make_shared<ConsoleMessageLogger>();
		}

		std::vector<std::string> getSearchDirs() {
			if(parser.getUnnamedValues().size() == 1)
				return {parser.getUnnamedValues()[0]};
			else
				return {"."};
		}

		std::vector<std::string> getSearchExtensions() {
			return {".dll", ".so"};
		}

		int showAndGetResults(TestSuite::TestReportArray testReports) {
			int passing = 0, falling = 0;
			processResulsts(testReports, passing, falling);
			std::cout << "\n\nPassing tests: " << passing << "\nFalling tests: " << falling;
			return falling;
		}

		void processResulsts(TestSuite::TestReportArray testReports, int& passing, int& falling) {
			for(auto testReport : testReports) {
				showTestResult(testReport);
				increaceResultsCounters(passing, falling, testReport);
			}
		}

		void showTestResult(TestSuite::TestReportArray::value_type testReport) {
			std::cout << "[" << (testReport.getResult().isSuccess() ? "Success" : "Failure") << "] Cause: <"
			             << testReport.getResult().getCause() << "> Name: <" << testReport.getFullName() << ">";
			if(testReport.getResult().isFailure())
				std::cout << "Error: <" << testReport.getResult().getErrorMessage() << ">";
			std::cout << " Duration: <" << std::chrono::duration_cast<std::chrono::microseconds>(testReport.getResult().getDurationTime()).count() / 1000.0 << "ms>\n";
		}

		void increaceResultsCounters(int& passing, int& falling, TestSuite::TestReportArray::value_type testReport) {
			if(testReport.getResult().isSuccess())
				passing++;
			else
				falling++;
		}
	};
}}
