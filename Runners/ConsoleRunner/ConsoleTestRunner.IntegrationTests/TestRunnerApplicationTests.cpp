#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ConsoleTestRunnerLibrary/TestRunnerApplication.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define showStream(stream) auto str=stream.str();Assert::Fail(std::wstring(str.begin(),str.end()).c_str());

namespace darknessNight { namespace ConsoleTestRunner { namespace IntegrationTests {
	TEST_CLASS(TestRunnerApplicationTests) {
	public:
		std::ostringstream stdStream,
		                   errStream,
		                   logStream;
		std::streambuf *backCout, *backCerr, *backClog;

		TEST_METHOD_INITIALIZE(SetUp) {
			clearBuffs();
			createBackups();
			setFakeBuffors();
		}

		void setFakeBuffors() const {
			std::cout.rdbuf(stdStream.rdbuf());
			std::cerr.rdbuf(errStream.rdbuf());
			std::clog.rdbuf(logStream.rdbuf());
		}

		void createBackups() {
			backCout = std::cout.rdbuf();
			backCerr = std::cerr.rdbuf();
			backClog = std::clog.rdbuf();
		}

		void clearBuffs() {
			stdStream.clear();
			errStream.clear();
			logStream.clear();
		}

		TEST_METHOD_CLEANUP(TearDown) {
			std::cout.rdbuf(backCout);
			std::cerr.rdbuf(backCerr);
			std::clog.rdbuf(backClog);
		}

		int executeApp(std::vector<const char*> argv) {
			TestRunnerApplication app;
			return app.startProgram(argv.size(), argv.data());
		}

		TEST_METHOD(StartProgram_HasUnexistsDir_CheckNoThrowAndShowErrors) {
			std::vector<const char*> argv = {"Test", "./UnexistsDirectory"};
			assertNotThrow([&]() { executeApp(argv); });
			assertStreamHasData(errStream);
		}

		void assertStreamHasData(std::ostringstream &buff) {
			auto errorMess = buff.str();
			Assert::IsTrue(0 < errorMess.size(), L"Stream is empty");
		}

		void assertNotThrow(std::function<void()> func) {
			try {
				func();
			}
			catch(std::exception &ex) {
				std::string str = "Exception: ";
				str += typeid(ex).name();
				str+= ex.what();
				Assert::Fail(std::wstring(str.begin(), str.end()).c_str());
			}
			catch(std::string str) {
				Assert::Fail(std::wstring(str.begin(), str.end()).c_str());
			}
			catch(...) {
					Assert::Fail(L"Throwed exception");
			}
		}

		TEST_METHOD(StartProgram_HasExistsDir_CheckShowLogs) {
			std::vector<const char*> argv = { "Test", "./" };
			assertNotThrow([&]() { executeApp(argv); });
			assertStreamIsEmpty(errStream);
			assertStreamHasData(logStream);
			assertStreamHasData(stdStream);
		}

		void assertStreamIsEmpty(std::ostringstream& buff) {
			auto errorMess = buff.str();
			Assert::IsTrue(0 == errorMess.size(), L"Stream is not empty");
		}

		TEST_METHOD(StartProgram_HasCorrectDir_CheckRunTests) {
			std::vector<const char*> argv = { "Test", "./" };
			auto failedTests=executeApp(argv);
			Assert::IsTrue(failedTests > 1);
		}

		TEST_METHOD(StartProgram_HasCorrectDir_CheckShowSummary) {
			std::vector<const char*> argv = { "Test", "./" };
			executeApp(argv);
			auto result=stdStream.str();
			assertContainSubstring(result, "Passing tests: 8");
			assertContainSubstring(result, "Falling tests: 7");
		}

		void assertContainSubstring(std::string string, std::string search) {
			int pos = string.find(search);
			Assert::IsTrue(pos >= 0);
		}

		TEST_METHOD(StartProgram_HasCorrectDir_CheckShowDefaultLogs) {
			std::vector<const char*> argv = { "Test", "./" };
			executeApp(argv);
			auto result = stdStream.str();
			assertContainSubstring(result, "Passing tests: 8");
		}

		TEST_METHOD(StartProgram_HasCorrectDir_CheckShowDefaultResultPattern) {
			std::vector<const char*> argv = { "Test", "./" };
			executeApp(argv);
			auto result = stdStream.str();
			std::string basicPattern = "\\[.*\\] Cause: <.*> Name: <.*> Message: <.*> Duration: <.*>";
			assertAppShowFormatedTestsResults(result, basicPattern);
		}

		int countLinesMatchPattern(std::regex &reg, std::vector<std::string> &lines) {
			int count = 0;
			for (auto line : lines) {
				if (std::regex_match(line, reg))
					count++;
				/*line += std::to_string(count);
				Assert::Fail(std::wstring(line.begin(), line.end()).c_str());*/
			}
			return count;
		}

		void assertAppShowFormatedTestsResults(std::string &result, std::string &pattern) {
			std::regex reg(pattern);
			auto lines = StringTools::split(result, '\n');
			auto matchedLines=countLinesMatchPattern(reg, lines);
			Assert::AreEqual(15, matchedLines);
		}

		TEST_METHOD(StartProgram_HasCorrectDirAndHasFormat_CheckShowFormattedOutput) {
			std::string patern = "\\{.*\\} because \\(.*\\) test: <.*>";
			std::vector<const char*> argv = { "Test", "./", "--format", "{%result} because (%cause) test: <%testName>" };
			assertNotThrow([&]() { executeApp(argv); });
			auto result = stdStream.str();
			assertAppShowFormatedTestsResults(result, patern);
		}
	};
}}}
