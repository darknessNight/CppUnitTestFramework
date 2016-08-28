#pragma once

template<typename T>
inline void BasicAssert::IsNull(T val, std::string message) {
	if (val != nullptr) {
		std::string mess = getAddOwnMessageIfExists(message, "Expected nullptr, but was <" + ToStringConverter::ToString(val) + ">");
		Fail(mess);
	}
}

template<typename T>
inline void BasicAssert::IsNotNull(T val, std::string message) {
	if (val == nullptr) {
		std::string mess = getAddOwnMessageIfExists(message, "Expected non null value");
		Fail(mess);
	}
}

template<typename T>
inline int BasicAssert::defaultComparerWithTolerance(T expected, T result, T tolerance) {
	if (expected + tolerance < result)
		return -1;
	else if (expected - tolerance > result)
		return 1;
	else return 0;

}

template<typename T>
inline int BasicAssert::defaulComparer(const T & expected, const T & result) {
	if (expected < result)
		return -1;
	else if (expected == result)
		return 0;
	else return 1;
}