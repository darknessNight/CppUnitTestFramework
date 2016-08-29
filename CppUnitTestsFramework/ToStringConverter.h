#pragma once
#include <typeinfo>
#include <string>
#include <memory>
#include <map>

namespace darknessNight_CppUnitTestFramework {
	class ToStringConverter {
	private:
		static std::unique_ptr<ToStringConverter> instance;
		std::map<std::string, void*> funcArray;
	public:
		ToStringConverter();
		static std::string ToString(const char* obj);
		static std::string ToString(const wchar_t* obj);
		template <typename T> static std::string ToString(const T obj);
		template <typename T> static std::string ArrayToString(const T &obj) { return ""; }
		template <typename T> static std::string ArrayToString(const T* obj) { return ""; }
		template <typename T> static void RegisterConventerFunction(std::string(*convFunc)(const T));
	private:
		static std::string StringToString(std::string obj);
		static std::string WStringToString(std::wstring obj);
		template <typename T> void registerConverter(std::string(*convFunc)(const T));
		template<typename T> void saveFuncs(std::string &name, void * func, std::string &staticName);
		template <typename T> std::string(* /**/getMethod()/**/)(const T);//INFO: This is method return function based on template type
		template<typename T> std::map<std::string, void*>::iterator findTypeFunc();
		template <typename T> static std::string UnknowTypeToString(const T obj);
	};
}

#include "ToStringConverterImplem.h"