#pragma once
#include "BasicAssert.h"
namespace darknessNight_CppUnitTestFramework {
	class AssertExceptionCatcher: protected virtual BasicAssert {
	public:
		template <typename Exception>static Exception Throws(void(*func)(), std::string message = "");

		//template<> static std::exception Throws(void(*func)(), std::string message);

		static void DoesNotThrow(void(*func)()) {
			try {
				func();
			}
			catch (std::exception &ex) {
				throwDoesNotThrowFailed(typeid(ex).name());
			}
			catch (...) {
				BasicAssert::Fail("Catched unexpected exception <"+ std::string("Unknow-type") +">");
			}
		}

		static void throwDoesNotThrowFailed(std::string type)
		{
			BasicAssert::Fail("Catched unexpected exception <" + type + ">");
		}

	private:
		template<typename Exception> static void throwCatchOtherException(std::exception & ex, std::string message);
		static void throwCatchUnknowException(std::string message);
		static void throwThrowFailedMessage(std::string message);
	};


#pragma warning(push)
#pragma warning(disable: 4715)
	template<typename Exception>
	inline Exception AssertExceptionCatcher::Throws(void(*func)(), std::string message) {
		try {
			func();
		}
		catch (Exception &ex) {
			return ex;
		}
		catch (std::exception &ex) {
			throwCatchOtherException<Exception>(ex, message);
		}
		catch (...) {
			throwCatchUnknowException(message);
		}

		throwThrowFailedMessage(message);
	}
	template<>
	inline std::exception AssertExceptionCatcher::Throws(void(*func)(), std::string message) {
		try {
			func();
		}
		catch (std::exception &ex) {
			return ex;
		}
		catch (...) {
			throwCatchUnknowException(message);
		}

		throwThrowFailedMessage(message);
	}
	template<typename Exception>
	inline void AssertExceptionCatcher::throwCatchOtherException(std::exception & ex, std::string userMessage)
	{
		std::string assertMessage = std::string("Wrong exception throwed. Catched <") + typeid(ex).name() + ">, but expected <" + typeid(Exception).name() + ">";
		std::string result = getAddOwnMessageIfExists(userMessage, assertMessage);
		BasicAssert::Fail(result);
	}
}
#pragma warning(pop)
