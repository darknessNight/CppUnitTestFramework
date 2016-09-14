#pragma once
#include "Exceptions.h"
#include <memory>
#include <map>

namespace darknessNight {
	namespace SharedLibrary {

		class DynamicLibrary {
		private:
			static std::unique_ptr<DynamicLibrary> instance;
			std::map<std::string, void*> modules;
		public:
			virtual ~DynamicLibrary();
			template <typename T> static T* ImportFunction(std::string libraryPath, std::string functionName);
			template <typename T> T* importFunction(std::string libraryPath, std::string functionName);
			static void FreeLibrary(std::string name);
			void freeLibrary(std::string name);
			void freeAllLibraries();
		protected:
			virtual void* getFunction(std::string &libraryPath, std::string &functionName);
			void* getFunctionFromModule(void* module, std::string &functionName);
			void throwIfNotLoadedFunction(void * func, std::string & functionName);
			void* getModuleAndLoadIfNeeded(std::string &libraryPath);
			bool moduleExists(std::string & libraryPath);
			void* loadModule(std::string &libraryPath);
			void throwIfNotLoadedLibrary(void* module, std::string & libraryPath);
			void* getFunctionSystemFunc(void* module, std::string&functionName);
			void *loadModuleSystemFunc(std::string&libraryPath);
		};

		template<typename T>
		inline T * DynamicLibrary::ImportFunction(std::string libraryPath, std::string functionName) {
			return instance->importFunction<T>(libraryPath, functionName);
		}
		template<typename T>
		inline T * DynamicLibrary::importFunction(std::string libraryPath, std::string functionName) {
			return (T*)getFunction(libraryPath, functionName);
		}

	}
}
