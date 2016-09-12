void getLibHeaders(IMAGE_DOS_HEADER * &pDOSHeader, BYTE * lpBaseAddress, IMAGE_NT_HEADERS * &pNTHeaders, IMAGE_SECTION_HEADER * &pSectionHeader);

void checkIsManagedLib(IMAGE_NT_HEADERS * pNTHeaders, IMAGE_DOS_HEADER * pDOSHeader, IMAGE_SECTION_HEADER * pSectionHeader, BOOL &bIsManaged);

void checkHasPNetHeader(IMAGE_DOS_HEADER * pDOSHeader, IMAGE_SECTION_HEADER * pSectionHeader, IMAGE_NT_HEADERS * pNTHeaders, const DWORD &dwNETHeaderTableLocation, BOOL & bIsManaged);

void mapLibFileAndCheckHasDotNetHeader(const HANDLE &hOpenFileMapping, BOOL &bIsManaged);

void getHeadersAndCheckHasDotNetHeader(BYTE * lpBaseAddress, BOOL & bIsManaged);

void mapLibIfCanAndCheckHasDotNetHeader(const HANDLE &hFile, BOOL &bIsManaged);
