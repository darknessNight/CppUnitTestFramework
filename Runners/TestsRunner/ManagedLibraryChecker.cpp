#include "ManagedLibraryChecker.h"

bool ManagedLibraryChecker::isManagedLib(std::string path) {
#ifdef _WIN32
	std::wstring wPath;
	for(char c : path)
		wPath += c;
	return IsManaged(const_cast<wchar_t*>(wPath.c_str())) == TRUE;
#else
		return false;
#endif
}

#ifdef _WIN32

DWORD ManagedLibraryChecker::GetActualAddressFromRVA(IMAGE_SECTION_HEADER* pSectionHeader, IMAGE_NT_HEADERS* pNTHeaders, DWORD dwRVA) {
	DWORD dwRet = 0;
	for(int j = 0; j < pNTHeaders->FileHeader.NumberOfSections; j++ , pSectionHeader++) {
		DWORD cbMaxOnDisk = min(pSectionHeader->Misc.VirtualSize, pSectionHeader->SizeOfRawData);
		DWORD startSectRVA, endSectRVA;
		startSectRVA = pSectionHeader->VirtualAddress;
		endSectRVA = startSectRVA + cbMaxOnDisk;
		if((dwRVA >= startSectRVA) && (dwRVA < endSectRVA)) {
			dwRet = (pSectionHeader->PointerToRawData) + (dwRVA - startSectRVA);
			break;
		}
	}
	return dwRet;
}

BOOL ManagedLibraryChecker::IsManaged(LPTSTR lpszImageName) {
	BOOL bIsManaged = FALSE;
	HANDLE hFile = CreateFile(lpszImageName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE != hFile) {
		mapLibIfCanAndCheckHasDotNetHeader(hFile, bIsManaged);
		CloseHandle(hFile);
	}
	return bIsManaged;
}

void ManagedLibraryChecker::mapLibIfCanAndCheckHasDotNetHeader(const HANDLE& hFile, BOOL& bIsManaged) {
	HANDLE hOpenFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(hOpenFileMapping) {
		mapLibFileAndCheckHasDotNetHeader(hOpenFileMapping, bIsManaged);
		CloseHandle(hOpenFileMapping);
	}
}

void ManagedLibraryChecker::mapLibFileAndCheckHasDotNetHeader(const HANDLE& hOpenFileMapping, BOOL& bIsManaged) {
	BYTE* lpBaseAddress = NULL;
	lpBaseAddress = (BYTE*)MapViewOfFile(hOpenFileMapping, FILE_MAP_READ, 0, 0, 0);
	if(lpBaseAddress) {
		getHeadersAndCheckHasDotNetHeader(lpBaseAddress, bIsManaged);
	}
}

void ManagedLibraryChecker::getHeadersAndCheckHasDotNetHeader(BYTE* lpBaseAddress, BOOL& bIsManaged) {
	IMAGE_DOS_HEADER* pDOSHeader;
	IMAGE_NT_HEADERS* pNTHeaders;
	IMAGE_SECTION_HEADER* pSectionHeader;
	getLibHeaders(pDOSHeader, lpBaseAddress, pNTHeaders, pSectionHeader);
	checkIsManagedLib(pNTHeaders, pDOSHeader, pSectionHeader, bIsManaged);
	UnmapViewOfFile(lpBaseAddress);
}

void ManagedLibraryChecker::checkIsManagedLib(IMAGE_NT_HEADERS* pNTHeaders, IMAGE_DOS_HEADER* pDOSHeader, IMAGE_SECTION_HEADER* pSectionHeader, BOOL& bIsManaged) {
	if(pNTHeaders->Signature == IMAGE_NT_SIGNATURE) {
		DWORD dwNETHeaderTableLocation = pNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress;
		if(dwNETHeaderTableLocation) {
			checkHasPNetHeader(pDOSHeader, pSectionHeader, pNTHeaders, dwNETHeaderTableLocation, bIsManaged);
		}
	}
}

void ManagedLibraryChecker::checkHasPNetHeader(IMAGE_DOS_HEADER* pDOSHeader, IMAGE_SECTION_HEADER* pSectionHeader, IMAGE_NT_HEADERS* pNTHeaders, const DWORD& dwNETHeaderTableLocation, BOOL& bIsManaged) {
	IMAGE_COR20_HEADER* pNETHeader = (IMAGE_COR20_HEADER*)((BYTE*)pDOSHeader + GetActualAddressFromRVA(pSectionHeader, pNTHeaders, dwNETHeaderTableLocation));
	if(pNETHeader) {
		bIsManaged = TRUE;
	}
}

void ManagedLibraryChecker::getLibHeaders(IMAGE_DOS_HEADER*& pDOSHeader, BYTE* lpBaseAddress, IMAGE_NT_HEADERS*& pNTHeaders, IMAGE_SECTION_HEADER*& pSectionHeader) {
	pDOSHeader = (IMAGE_DOS_HEADER*)lpBaseAddress;
	pNTHeaders = (IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
	pSectionHeader = (IMAGE_SECTION_HEADER*)((BYTE*)pNTHeaders + sizeof(IMAGE_NT_HEADERS));
}
#endif 