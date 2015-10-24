
#pragma once


typedef BOOL (__stdcall *ProcDllMain)(HINSTANCE, DWORD, LPVOID );

class CMemLoadDll
{
public:
    CMemLoadDll();
    ~CMemLoadDll();
    BOOL MemLoadLibrary( void* lpFileData , int DataLength); // Dll file data buffer
    FARPROC MemGetProcAddress(LPCSTR lpProcName);
private:
    BOOL isLoadOk;
    BOOL CheckDataValide(void* lpFileData, int DataLength);
    int CalcTotalImageSize();
    void CopyDllDatas(void* pDest, void* pSrc);
    BOOL FillRavAddress(void* pBase);
    void DoRelocation(void* pNewBase);
    int GetAlignedSize(int Origin, int Alignment);
private:
    ProcDllMain pDllMain;

private:
    DWORD pImageBase;
    PIMAGE_DOS_HEADER pDosHeader;
    PIMAGE_NT_HEADERS pNTHeader;
    PIMAGE_SECTION_HEADER pSectionHeader;
};