#include "TestDiscover.h"
#include <CppUnitTestFramework/Version.h>
#include "ManagedLibraryChecker.h"

darknessNight::TestsRunner::TestDiscover::TestDiscover(std::shared_ptr<Directory> dir, std::shared_ptr<DynamicLibrary> dynLibs, MessageLogger& messageLogger) {
	dynamicLibrary = dynLibs;
	directory = dir;
	logger = &messageLogger;
}

darknessNight::TestsRunner::TestDiscover::~TestDiscover() {
	suites.clear();
}

void darknessNight::TestsRunner::TestDiscover::findAll(std::vector<std::string> paths, std::vector<std::string> extensions) {
	auto pattern = prepareSearchPattern(extensions);
	searchLibraries(paths, pattern);
}

void darknessNight::TestsRunner::TestDiscover::searchLibraries(std::vector<std::string>& paths, std::string & pattern) {
	for (auto path : paths) {
		auto dir = directory->get(path);
		auto tmp = dir->getPath();
		searchLibrariesInDir(dir, pattern);
	}
}

void darknessNight::TestsRunner::TestDiscover::searchLibrariesInDir(std::shared_ptr<Directory>& directory, std::string & pattern) {
	for (auto dir : directory->searchElements(pattern)) {
		getTestsIfLibraryIsCorrect(dir.getPath());
	}
}

void darknessNight::TestsRunner::TestDiscover::getTestsIfLibraryIsCorrect(std::string path) {
	try {
		if(isCorrectLibrary(path))
			tryGetTests(path);
	}
	catch (LibraryLoadException) {
	}
	catch (FunctionLoadException) {
		dynamicLibrary->freeLibrary(path);
	}
}

bool darknessNight::TestsRunner::TestDiscover::isCorrectLibrary(std::string path) {
	return !ManagedLibraryChecker::isManagedLib(path) && isCorrectLibVersion(path);
}

bool darknessNight::TestsRunner::TestDiscover::isCorrectLibVersion(std::string path) {
	auto func = dynamicLibrary->importFunction<const char*()>(path, dllVersionFuncName);
	std::string dllLibVersion = func();
	std::string programLibVersion = CPPUNITTEST_LIBRARY_VERSION;
	return dllLibVersion == programLibVersion;
}

void darknessNight::TestsRunner::TestDiscover::tryGetTests(std::string & path) {
	auto func = dynamicLibrary->importFunction<TestContainer*()>(path, dllFuncName);
	TestContainer* container = func();
	for (auto suite : container->getAllTestSuites())
		suites.push_back(suite);		
}

std::string darknessNight::TestsRunner::TestDiscover::prepareSearchPattern(std::vector<std::string>& extensions) {
	std::string pattern = ".*\\.(";
	addExtensionsToPattern(extensions, pattern);
	return pattern + ")";
}

void darknessNight::TestsRunner::TestDiscover::addExtensionsToPattern(std::vector<std::string>& extensions, std::string & pattern) {
	for (auto ext : extensions) {
		deleteDotsAtBeginExt(ext);
		pattern += ext + "|";
	}
	pattern = pattern.substr(0, pattern.size() - 1);
}

void darknessNight::TestsRunner::TestDiscover::deleteDotsAtBeginExt(std::string &ext) {
	while (ext.size() > 0 && ext[0] == '.')
		ext = ext.substr(1);
}

void darknessNight::TestsRunner::TestDiscover::findInFile(std::string path) {
	getTestsIfLibraryIsCorrect(path);
}

std::vector<std::string> darknessNight::TestsRunner::TestDiscover::getSuitesNames() {
	std::vector<std::string> names;
	for (auto suite : suites) {
		names.push_back(suite->getName());
	}
	return names;
}

std::vector<TestSuitePtr> darknessNight::TestsRunner::TestDiscover::getSuites() {
	return suites;
}

std::vector<TestCasePtr> darknessNight::TestsRunner::TestDiscover::getTestsList() {
	std::vector<TestCasePtr> tests;
	for (auto suite : suites) {
		for (auto test : suite->getTestCases())
			tests.push_back(test);
	}
	return tests;
}

void darknessNight::TestsRunner::TestDiscover::safeClear() {
	suites.clear();
	dynamicLibrary->freeAllLibraries();
}
