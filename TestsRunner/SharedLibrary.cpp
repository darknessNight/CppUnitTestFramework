#include "SharedLibrary.h"

using namespace darknessNight::SharedLibrary;
std::shared_ptr<SharedLibrary> SharedLibrary::instance = std::make_shared<SharedLibrary>();

#ifdef _WIN32
darknessNight::SharedLibrary::SharedLibrary::~SharedLibrary()
{
	for (auto module : modules) {
		FreeLibrary((HMODULE)module.second);
	}
}

void darknessNight::SharedLibrary::SharedLibrary::freeLibrary(std::string name) {
	if (instance->moduleExists(name))
		FreeLibrary((HMODULE)instance->modules[name]);
}

void* SharedLibrary::getModuleAndLoadIfNeeded(std::string &libraryPath) {
	if (moduleExists(libraryPath))
		return loadModule(libraryPath);
	else
		return modules[libraryPath];
}

bool darknessNight::SharedLibrary::SharedLibrary::moduleExists(std::string & libraryPath) {
	return modules.find(libraryPath) == modules.end();
}


void* SharedLibrary::loadModule(std::string &libraryPath)
{
	auto module = LoadLibraryA(libraryPath.c_str());
	if (module == nullptr)
		throw LibraryLoadException("Cannot load library: " + libraryPath);
	modules[libraryPath] = module;
	return module;
}

#endif
#ifdef __linux
#error Not supported yet
#endif