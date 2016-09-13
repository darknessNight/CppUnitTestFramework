#include "TestsDiscover.h"
#include "ManagedLibraryChecker.h"

void darknessNight::TestsRunner::TestsDiscover::findAll(std::vector<std::string> paths, std::vector<std::string> extensions) {
	std::string pattern = prepareSearchPattern(extensions);
	searchLibraries(paths, pattern);
}

void darknessNight::TestsRunner::TestsDiscover::searchLibraries(std::vector<std::string>& paths, std::string & pattern) {
	for (auto path : paths) {
		auto dir = directory->get(path);
		auto tmp = dir->getPath();
		searchLibrariesInDir(dir, pattern);
	}
}

void darknessNight::TestsRunner::TestsDiscover::searchLibrariesInDir(std::shared_ptr<Directory>& directory, std::string & pattern) {
	for (auto dir : directory->searchElements(pattern)) {
		getTestsIfLibraryIsCorrect(dir.getPath());
	}
}

void darknessNight::TestsRunner::TestsDiscover::getTestsIfLibraryIsCorrect(std::string path) {
	try {
		if(!ManagedLibraryChecker::isManagedLib(path))
			tryGetTests(path);
	}
	catch (LibraryLoadException) {
	}
	catch (FunctionLoadException) {
		dynamicLibrary->freeLibrary(path);
	}
}

void darknessNight::TestsRunner::TestsDiscover::tryGetTests(std::string & path) {
	auto func = dynamicLibrary->importFunction<TestContainer*()>(path, dllFuncName);
	TestContainer* container = func();
	for (auto suite : container->getAllTestSuites())
		suites.push_back(suite);
}

std::string darknessNight::TestsRunner::TestsDiscover::prepareSearchPattern(std::vector<std::string>& extensions) {
	std::string pattern = ".*\\.(";
	addExtensionsToPattern(extensions, pattern);
	return pattern + ")";
}

void darknessNight::TestsRunner::TestsDiscover::addExtensionsToPattern(std::vector<std::string>& extensions, std::string & pattern) {
	for (auto ext : extensions) {
		deleteDotsAtBeginExt(ext);
		pattern += ext + "|";
	}
	pattern = pattern.substr(0, pattern.size() - 1);
}

void darknessNight::TestsRunner::TestsDiscover::deleteDotsAtBeginExt(std::string &ext) {
	while (ext.size() > 0 && ext[0] == '.')
		ext = ext.substr(1);
}

void darknessNight::TestsRunner::TestsDiscover::findInFile(std::string path) {
	
	getTestsIfLibraryIsCorrect(path);
}

std::vector<std::string> darknessNight::TestsRunner::TestsDiscover::getSuitesNames() {
	std::vector<std::string> names;
	for (auto suite : suites) {
		names.push_back(suite->getName());
	}
	return names;
}

std::vector<TestSuitePtr> darknessNight::TestsRunner::TestsDiscover::getSuites() {
	return suites;
}

std::vector<TestCasePtr> darknessNight::TestsRunner::TestsDiscover::getTestsList() {
	std::vector<TestCasePtr> tests;
	for (auto suite : suites) {
		for (auto test : suite->getTestCases())
			tests.push_back(test);
	}
	return tests;
}
