#include "SharedLibrary.h"

using namespace darknessNight::SharedLibrary;
std::shared_ptr<DynamicLibrary> DynamicLibrary::instance = std::make_shared<DynamicLibrary>();

#ifdef _WIN32
darknessNight::SharedLibrary::DynamicLibrary::~DynamicLibrary()
{
	for (auto module : modules) {
		FreeLibrary((HMODULE)module.second);
	}
}

void darknessNight::SharedLibrary::DynamicLibrary::freeLibrary(std::string name) {
	if (instance->moduleExists(name))
		FreeLibrary((HMODULE)instance->modules[name]);
}

void * darknessNight::SharedLibrary::DynamicLibrary::getFunction(std::string & libraryPath, std::string & functionName) {
	HMODULE module = (HMODULE)instance->getModuleAndLoadIfNeeded(libraryPath);
	return getFunctionFromModule(module, functionName);
}

void * darknessNight::SharedLibrary::DynamicLibrary::getFunctionFromModule(void * module, std::string & functionName) {
	auto func = (void*)GetProcAddress((HMODULE)module, functionName.c_str());
	if (func == nullptr)
		throw FunctionLoadException("Not found function: " + functionName);
	return func;
}

void* DynamicLibrary::getModuleAndLoadIfNeeded(std::string &libraryPath) {
	if (!moduleExists(libraryPath))
		return loadModule(libraryPath);
	else
		return modules[libraryPath];
}

bool darknessNight::SharedLibrary::DynamicLibrary::moduleExists(std::string & libraryPath) {
	return modules.find(libraryPath) != modules.end();
}


void* DynamicLibrary::loadModule(std::string &libraryPath)
{
	auto module = LoadLibraryA(libraryPath.c_str());
	if (module == nullptr)
		throw LibraryLoadException("Cannot load library: " + libraryPath);
	modules[libraryPath] = module;
	return module;
}

#endif
#ifdef __linux
//#ifdef _DEBUG
#include <dlfcn.h>

darknessNight::SharedLibrary::DynamicLibrary::~DynamicLibrary()
{
	for (auto module : modules) {
		dlclose(module.second);
	}
}

void darknessNight::SharedLibrary::DynamicLibrary::freeLibrary(std::string name) {
    if (instance->moduleExists(name))
		dlclose(instance->modules[name]);
}

void * darknessNight::SharedLibrary::DynamicLibrary::getFunction(std::string & libraryPath, std::string & functionName) {
	void* module = instance->getModuleAndLoadIfNeeded(libraryPath);
	return getFunctionFromModule(module, functionName);
}

void * darknessNight::SharedLibrary::DynamicLibrary::getFunctionFromModule(void * module, std::string & functionName) {
	auto func = (void*)dlsym(module, functionName.c_str());
	if (func == nullptr)
		throw FunctionLoadException("Not found function: " + functionName);
	return func;
}

void* DynamicLibrary::getModuleAndLoadIfNeeded(std::string &libraryPath) {
	if (!moduleExists(libraryPath))
		return loadModule(libraryPath);
	else
		return modules[libraryPath];
}

bool darknessNight::SharedLibrary::DynamicLibrary::moduleExists(std::string & libraryPath) {
	return modules.find(libraryPath) != modules.end();
}


void* DynamicLibrary::loadModule(std::string &libraryPath)
{
    auto module = dlopen("/opt/lib/libctest.so", RTLD_LAZY);
	if (module == nullptr)
		throw LibraryLoadException("Cannot load library: " + libraryPath);
	modules[libraryPath] = module;
	return module;
}
#endif
