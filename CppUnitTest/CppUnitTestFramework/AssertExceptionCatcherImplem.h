#pragma once


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
		throwCatchedUnexpectedException<Exception>(ex, message);
	}
	catch (...) {
		throwCatchUnknowException(message);
	}

	throwThrowFailedMessage(message);
}


template<typename Exception>
inline void AssertExceptionCatcher::throwCatchedUnexpectedException(std::exception & ex, std::string &message)
{
	helper.throwFailedExceptionFromPattern("Wrong exception throwed. Catched <%result>, but expected <%expected>",
									std::string(typeid(Exception).name()),
									std::string(typeid(ex).name()), message);
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
#pragma warning(pop)