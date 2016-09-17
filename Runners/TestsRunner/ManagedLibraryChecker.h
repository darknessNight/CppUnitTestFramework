#pragma once
#include <string>
#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4091)
#include <windows.h>
#include <tchar.h>
#include <winnt.h>
#include <cor.h>
#pragma warning( pop ) 
#endif
namespace darknessNight {
	namespace TestsRunner {
		class ManagedLibraryChecker {
		public:
			static bool isManagedLib(std::string path);
#ifdef _WIN32
		private:
			static DWORD GetActualAddressFromRVA(IMAGE_SECTION_HEADER* pSectionHeader, IMAGE_NT_HEADERS* pNTHeaders, DWORD dwRVA);
			static BOOL IsManaged(LPTSTR lpszImageName);
			static void mapLibIfCanAndCheckHasDotNetHeader(const HANDLE& hFile, BOOL& bIsManaged);
			static void mapLibFileAndCheckHasDotNetHeader(const HANDLE& hOpenFileMapping, BOOL& bIsManaged);
			static void getHeadersAndCheckHasDotNetHeader(BYTE* lpBaseAddress, BOOL& bIsManaged);
			static void checkIsManagedLib(IMAGE_NT_HEADERS* pNTHeaders, IMAGE_DOS_HEADER* pDOSHeader, IMAGE_SECTION_HEADER* pSectionHeader, BOOL& bIsManaged);
			static void checkHasPNetHeader(IMAGE_DOS_HEADER* pDOSHeader, IMAGE_SECTION_HEADER* pSectionHeader, IMAGE_NT_HEADERS* pNTHeaders, const DWORD& dwNETHeaderTableLocation, BOOL& bIsManaged);
			static void getLibHeaders(IMAGE_DOS_HEADER* & pDOSHeader, BYTE* lpBaseAddress, IMAGE_NT_HEADERS* & pNTHeaders, IMAGE_SECTION_HEADER* & pSectionHeader);
#endif
		};
	}
}