#include "stdafx.h"
#include <TextArgumentParser/ArgumentParser.h>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace NUnit;
using namespace NUnit::Framework;

namespace darknessNight::TextParser::UnitTests
{
	[TestFixture]
	public ref class UnitTest
	{
		const char* sampleParamName = "StartParam";
		const char* notUsedParamName= "ClearParam";
		const char* unxepectedParamName = "UnexpectedParam";
	public:
		[Test]
		void Parse_HasOneNameOnlyExpectedParam_CheckCorrectDetectArg() {
			auto parser = prepareParserWithSampleNameOnlyArg();
			actAndAssertDetectArgument(parser);
		}

		ArgumentParser prepareParserWithSampleNameOnlyArg() {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).asNameOnly();
			return parser;
		}

		void actAndAssertDetectArgument(darknessNight::TextParser::ArgumentParser &parser) {
			parser.parse({ sampleParamName });
			Assert::IsTrue(parser.getArgumentInfo(sampleParamName).isUsed());
		}

		[Test]
		void Parse_HasOneNameOnlyExpectedParam_CheckNotChangedOtherArgs() {
			auto parser = prepareParserForCheckNotChangedOtherArg();
			actAndAssertNotChangedOtherArg(parser);
		}

		void actAndAssertNotChangedOtherArg(darknessNight::TextParser::ArgumentParser &parser) {
			parser.parse({ sampleParamName });
			Assert::IsFalse(parser.getArgumentInfo(notUsedParamName).isUsed());
		}

		ArgumentParser prepareParserForCheckNotChangedOtherArg() {
			auto parser = prepareParserWithSampleNameOnlyArg();
			parser.registerArgument(notUsedParamName).asNameOnly();
			return parser;
		}

		[Test]
		void Parse_HasNameOnlyUnexpectedParam_CheckNoThrow() {
			auto parser = prepareParserWithSampleNameOnlyArg();
			assertNotThrowWhenHasUnexpectedArg(parser);
		}

		void assertNotThrowWhenHasUnexpectedArg(darknessNight::TextParser::ArgumentParser &parser) {
			try {
				parser.parse({ unxepectedParamName });
			}
			catch (...) {
				Assert::Fail();
			}
		}

		[Test]
		void Parse_HasArgWithBoolValue_CheckCorrectDetectValue() {
			ArgumentParser parser;
			parser.registerArgument(sampleParamName).withBoolParam();
			actAndAssertDetectBoolValue(parser);
		}
		void actAndAssertDetectBoolValue(darknessNight::TextParser::ArgumentParser &parser) {
			parser.parse({ std::string(sampleParamName) + " = true" });
			Assert::IsTrue(parser.getArgumentInfo(sampleParamName).isUsed(),"Not used");
			Assert::IsTrue(parser.getArgumentInfo(sampleParamName).getValue<bool>(), "Has not value");
		}
	};
}
