#pragma once
#include "Exceptions.h"
#include <memory>
#include <map>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace darknessNight {
	namespace SharedLibrary {

		class SharedLibrary {
		private:
			static std::shared_ptr<SharedLibrary> instance;
			std::map<std::string, void*> modules;
		public:
			~SharedLibrary();
			template <typename T> static T* importFunction(std::string libraryPath, std::string functionName);
			template<typename T> static T * loadFuncFromModule(const HMODULE &module, std::string &functionName);

		private:
			void* getModuleAndLoadIfNeeded(std::string &libraryPath);
			void* loadModule(std::string &libraryPath);
		};


		//implem
#ifdef _WIN32
		template<typename T>
		inline T * SharedLibrary::importFunction(std::string libraryPath, std::string functionName) {
			HMODULE module = (HMODULE)instance->getModuleAndLoadIfNeeded(libraryPath);
			return loadFuncFromModule<T>(module, functionName);
		}
		template<typename T>
		inline T * SharedLibrary::loadFuncFromModule(const HMODULE &module, std::string &functionName) {
			auto func = GetProcAddress(module, functionName.c_str());
			if (func == nullptr)
				throw FunctionLoadException("Not found function: " + functionName);
			return (T*)func;
		}

#endif
#ifdef __linux
#error Not supported yet
#endif
	}
}