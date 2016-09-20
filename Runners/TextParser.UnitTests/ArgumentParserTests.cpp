#include "stdafx.h"
#include <functional>
#include "CppUnitTest.h"
#include "../TextArgumentParser/ArgumentParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {
	template<>
	inline std::wstring ToString<std::vector<std::string>>(const std::vector<std::string>& tab) {
		std::wstring ret;
		for(auto el : tab) {
			std::wstring str(el.begin(), el.end());
			ret += str + L", ";
		}
		return ret.substr(0, ret.size() - 2);
	};
}}}

namespace darknessNight { namespace TextParser { namespace UnitTests {
	TEST_CLASS(ArgumentParserTests) {
		const char* sampleParamName = "StartParam";
		const char* notUsedParamName = "ClearParam";
		const char* unexpectedParamName = "UnexpectedParam";
	public:
		TEST_METHOD(Parse_HasOneNameOnlyExpectedParam_CheckCorrectDetectArg) {
			auto parser = prepareParserWithSampleNameOnlyArg();
			parser.parse({sampleParamName});
			assertDetectArgument(parser);
		}

		darknessNight::TextParser::ArgumentParser prepareParserWithSampleNameOnlyArg() {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).asNameOnly();
			return parser;
		}

		void assertDetectArgument(darknessNight::TextParser::ArgumentParser& parser) {
			Assert::IsTrue(parser.getArgumentInfo(sampleParamName).isUsed());
		}

		TEST_METHOD(Parse_HasOneNameOnlyExpectedParam_CheckNotChangedOtherArgs) {
			auto parser = prepareParserForCheckNotChangedOtherArg();
			actAndAssertNotChangedOtherArg(parser);
		}

		void actAndAssertNotChangedOtherArg(darknessNight::TextParser::ArgumentParser& parser) {
			parser.parse({sampleParamName});
			Assert::IsFalse(parser.getArgumentInfo(notUsedParamName).isUsed());
		}

		ArgumentParser prepareParserForCheckNotChangedOtherArg() {
			auto parser = prepareParserWithSampleNameOnlyArg();
			parser.registerArgument(notUsedParamName).asNameOnly();
			return parser;
		}

		TEST_METHOD(Parse_HasOneLineArgWithBoolValue_CheckCorrectDetectValue) {
			auto parser = prepareParserWithParamArg();
			try {
				parser.parse({std::string(sampleParamName) + " = true"});
			}
			catch(std::string str) {
				std::wstring wstr(str.begin(), str.end());
				Assert::Fail(wstr.c_str());
			}
			assertDetectBoolValue(parser);
		}

		ArgumentParser prepareParserWithParamArg() {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).withParam();
			return parser;
		}

		void assertDetectBoolValue(darknessNight::TextParser::ArgumentParser& parser) {
			Assert::IsTrue(parser.getArgumentInfo(sampleParamName).isUsed(), L"Not used");
			Assert::IsTrue(parser.getArgumentInfo(sampleParamName).getValue<bool>(), L"Has not value");
		}

		TEST_METHOD(Parse_HasTwoLineArgWithBoolValue_CheckCorrectDetectValue) {
			auto parser = prepareParserWithParamArg();
			parser.parse({std::string(sampleParamName), "true"});
			assertDetectBoolValue(parser);
		}

		TEST_METHOD(Parse_HasTwoLineArgWithBoolValueWithMiddleDelimiter_CheckCorrectDetectValue) {
			auto parser = prepareParserWithParamArg();
			parser.parse({std::string(sampleParamName), " = ", "true"});
			assertDetectBoolValue(parser);
		}

		TEST_METHOD(Parse_HasOneLineArgWithArray_CheckCorrectDetectValues) {
			auto parser = prepareParserWithArrayArg();
			parser.parse({std::string(sampleParamName) + " = true, false , one, three"});
			auto array = parser.getArgumentInfo(sampleParamName).getArray<std::string>();
			assertCorrectDetectArrayArg(array);
		}

		ArgumentParser prepareParserWithArrayArg() {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).withArrayParam();
			return parser;
		}

		void assertCorrectDetectArrayArg(std::vector<std::string>& array) {
			Assert::AreEqual<unsigned>(4, array.size());
			Assert::AreEqual<std::vector<std::string>>({"true", "false", "one","three"}, array);
		}

		TEST_METHOD(Parse_HasTwoLineArgWithArray_CheckCorrectDetectValues) {
			auto parser = prepareParserWithArrayArg();
			parser.parse({std::string(sampleParamName), "true, false , one, three"});
			auto array = parser.getArgumentInfo(sampleParamName).getArray<std::string>();
			assertCorrectDetectArrayArg(array);
		}

		TEST_METHOD(Parse_HasTwoLineArgWithArrayWithMiddleAssignOperator_CheckCorrectDetectValues) {
			auto parser = prepareParserWithArrayArg();
			parser.parse({std::string(sampleParamName), " = ", "true, false , one, three"});
			auto array = parser.getArgumentInfo(sampleParamName).getArray<std::string>();
			assertCorrectDetectArrayArg(array);
		}

		TEST_METHOD(Parse_HasNameOnlyUnexpectedArg_CheckNoThrow) {
			auto parser = prepareParserWithSampleNameOnlyArg();
			assertNotThrow([&]() {
				               parser.parse({unexpectedParamName});
			               });
		}

		void assertNotThrow(std::function<void()> func) {
			try {
				func();
			}
			catch(std::exception& ex) {
				std::string str = "<" + std::string(typeid(ex).name()) + ">";
				str += ex.what();
				std::wstring wstr(str.begin(), str.end());
				Assert::Fail(wstr.c_str());
			}
			catch(...) {
				Assert::Fail(L"Exception throwed");
			}
		}

		TEST_METHOD(Parse_HasUnExpectedSimpleOneLineArg_CheckNoThrow) {
			auto parser = prepareParserWithParamArg();
			assertNotThrow([&]() {
				               parser.parse({std::string(unexpectedParamName) + " = true"});
			               });
		}

		TEST_METHOD(Parse_HasUnExpectedSimpleTwoLineArg_CheckNoThrow) {
			auto parser = prepareParserWithParamArg();
			assertNotThrow([&]() {
				               parser.parse({std::string(unexpectedParamName), "true", sampleParamName});
			               });
		}

		TEST_METHOD(Parse_HasUnExpectedSimpleTwoLineArgWithInMiddleAssign_CheckNoThrow) {
			auto parser = prepareParserWithParamArg();
			assertNotThrow([&]() {
				               parser.parse({std::string(unexpectedParamName), "=", "true"});
			               });
		}

		TEST_METHOD(Parse_HasUnExpectedSimpleTwoLineArgWithInMiddleAssign_CheckCorrectReadNext) {
			auto parser = prepareParserWithParamArg();
			assertNotThrow([&]() {
				               parser.parse({std::string(unexpectedParamName), "=", "true", sampleParamName});
			               });
			assertDetectArgument(parser);
		}

		TEST_METHOD(Parse_HasUnExpectedArgAndSettedNoThrowOnUnexpected_CheckNoThrow) {
			auto parser = prepareParserWithParamArg();
			parser.setThrowOnUnexpectedArg(false);
			assertNotThrow([&]() {
				               parser.parse({std::string(unexpectedParamName), "=", "true", sampleParamName});
			               });
		}

		TEST_METHOD(Parse_HasUnExpectedArgAndSettedThrowOnUnexpected_CheckThrow) {
			auto parser = prepareParserWithParamArg();
			parser.setThrowOnUnexpectedArg(true);
			auto ex = assertThrow<UnexpectedArgumentException>([&]() {
				                                                   parser.parse({std::string(unexpectedParamName), "=", "true", sampleParamName});
			                                                   });
			Assert::AreEqual<std::string>(unexpectedParamName, ex.getUnexpectedArg());
		}

		template<typename exception>
		exception assertThrow(std::function<void()> func) {
			try {
				func();
				Assert::Fail(L"Not throw");
			}
			catch(exception& ex) {
				return ex;
			}
		}

		TEST_METHOD(Parse_HasUnExpectedArgAndSettedLoggerFunc_CheckHasLog) {
			auto parser = prepareParserWithParamArg();
			bool used = false;
			parser.setLoggerFunc([&](std::string argName) {
				                     used = true;
			                     });
			parser.parse({std::string(unexpectedParamName), "=", "true", sampleParamName});
			Assert::IsTrue(used);
		}

		TEST_METHOD(Parse_HasUnExpectedArgWithParamAndSettedLoggerFunc_CheckCorrectLog) {
			auto parser = prepareParserWithParamArg();
			std::vector<std::string> unexpectedArgs;
			parser.setLoggerFunc([&](std::string argName) {
				                     unexpectedArgs.push_back(argName);
			                     });
			parser.parse({std::string(unexpectedParamName), "=", "true", sampleParamName});
			Assert::AreEqual<std::vector<std::string>>({unexpectedParamName}, unexpectedArgs);
		}

		TEST_METHOD(Parse_SettedRequiredArgAndHasThisArg_CheckNoThrow) {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).asNameOnly().isRequired(true);
			parser.registerArgument(sampleParamName + std::string("2")).asNameOnly().isRequired(false);
			assertNotThrow([&]() {
				               parser.parse({sampleParamName});
			               });
		}

		TEST_METHOD(Parse_SettedRequiredArgAndHasNotThisArg_CheckThrow) {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).asNameOnly().isRequired(true);
			parser.registerArgument(sampleParamName + std::string("2")).asNameOnly().isRequired(true);
			assertThrow<IncompleteArgsCollectionException>([&]() {
				               parser.parse({sampleParamName + std::string("2")});
			               });
		}

		TEST_METHOD(Parse_SettedDefaultValArgAndNoUseVal_CheckHasDefValue) {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).asNameOnly().withDefaultValue("DefVal");
			parser.parse({ unexpectedParamName });
			Assert::IsFalse(parser.getArgumentInfo(sampleParamName).isUsed());
			Assert::AreEqual<std::string>("DefVal", parser.getArgumentInfo(sampleParamName).getValue<std::string>());
		}
	};
}}}
