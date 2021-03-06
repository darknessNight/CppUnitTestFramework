#pragma once
#include "ToStringConverter.h"
namespace darknessNight {
	namespace CppUnitTestFramework {

		template <typename T> std::string(*ToStringConverter::getMethod())(const T) {
			auto result = findTypeFunc<T>();
			if (result != funcArray.end())
				//return static_cast<std::string(*)(const T)>(result->second);
				return (std::string(*)(const T))result->second;
			else
				return &ToStringConverter::UnknowTypeToString<T>;
		}
		template<typename T> inline std::string ToStringConverter::ToString(const T obj) {
			auto func = (instance->getMethod<T>());
			return func(obj);
		}
		template<typename T> inline std::string ToStringConverter::ArrayToString(const T & obj) {
			return IterableToString(std::begin(obj), std::end(obj));
		}

		template<typename T> inline std::string ToStringConverter::ArrayToString(const T * obj, unsigned len) {
			return IterableToString(obj, &obj[len]);
		}

		template<typename T> inline std::string ToStringConverter::IterableToString(T iter, const T end) {
			std::string message = "";
			for (; iter != end; iter++) {
				message += ToString(*iter) + ", ";
			}
			return message;
		}

		template<typename T>
		inline void ToStringConverter::RegisterConventerFunction(std::string(*convFunc)(const T)) {
			instance->registerConverter<T>(convFunc);
		}
		template<typename T>
		inline void ToStringConverter::registerConverter(std::string(*convFunc)(const T)) {
			std::string name = typeid(T).name();
			std::string staticName = typeid(const T).name();
			//void* func = static_cast<void*>(convFunc);
			void* func = (void*)(convFunc);
			saveFuncs<T>(name, func, staticName);
		}
		template<typename T>
		inline void ToStringConverter::saveFuncs(std::string & name, void * func, std::string & staticName) {
			funcArray[name] = func;
			funcArray[staticName] = func;
		}
		template<typename T>
		inline std::map<std::string, void*>::iterator ToStringConverter::findTypeFunc() {
			std::string type = typeid(T).name();
			auto result = funcArray.find(type);
			return result;
		}
		template<typename T>
		inline std::string ToStringConverter::UnknowTypeToString(const T obj) {
			return typeid(obj).name();
		}
	}
}