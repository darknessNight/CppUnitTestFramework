#pragma once
#include "Exceptions.h"
#include <memory>
#include <map>

namespace darknessNight {
	namespace SharedLibrary {

		class DynamicLibrary {
		private:
			static std::shared_ptr<DynamicLibrary> instance;
			std::map<std::string, void*> modules;
		public:
			~DynamicLibrary();
			template <typename T> static T* ImportFunction(std::string libraryPath, std::string functionName);
			template <typename T> T* importFunction(std::string libraryPath, std::string functionName);
			static void freeLibrary(std::string name);
		protected:
			virtual void* getFunction(std::string &libraryPath, std::string &functionName);
			void* getFunctionFromModule(void* module, std::string &functionName);
			void* getModuleAndLoadIfNeeded(std::string &libraryPath);
			bool moduleExists(std::string & libraryPath);
			void* loadModule(std::string &libraryPath);
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
