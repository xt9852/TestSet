#include "stdafx.h"
#include "MemLoadDll.h"


/*

程序使用动态库DLL一般分为隐式加载和显式加载两种，分别对应两种链接情况。本文主要讨论显式加载的技术问题。
我们知道，要显式加载一个DLL，并取得其中导出的函数地址一般是通过如下步骤：
(1) 用LoadLibrary加载dll文件，获得该dll的模块句柄；
(2) 定义一个函数指针类型，并声明一个变量；
(3) 用GetProcAddress取得该dll中目标函数的地址，赋值给函数指针变量；
(4) 调用函数指针变量。

这 个方法要求dll文件位于硬盘上面。现在假设我们的dll已经位于内存中，比如通过脱壳、解密或者解压缩得到，
能不能不把它写入硬盘文件，而直接从内存加 载呢？答案是肯定的。经过多天的研究，非法操作了N次，修改了M个BUG，
死亡了若干脑细胞后，终于有了初步的结果，下面做个总结与大家共享。

一、加载的步骤

由 于没有相关的资料说明，只能凭借感觉来写。首先LoadLibrary是把dll的代码映射到exe进程的虚拟地址空间中，
我们要实现的也是这个。所以先 要弄清楚dll的文件结构。好在这个比较简单，它和exe一样也是PE文件结构，关于PE文件的资料很多，
阅读一番后，基本上知道了必须做的几个工作：
(1)判断内存数据是否是一个有效的DLL。这个功能通过函数CheckDataValide完成。原型是：
BOOL CMemLoadDll::CheckDataValide(void* lpFileData, int DataLength);
(2)计算加载该DLL所需的虚拟内存大小。这个功能通过函数CalcTotalImageSize完成。原型是：
int CMemLoadDll::CalcTotalImageSize();
(3)将DLL数据复制到所分配的虚拟内存块中。该功能通过函数CopyDllDatas完成。要注意段对齐。
void CMemLoadDll::CopyDllDatas(void* pDest, void* pSrc);
(4)修正基地重定位数据。这个功能通过函数DoRelocation完成。原型是：
void CMemLoadDll::DoRelocation( void *NewBase);
(5)填充该DLL的引入地址表。这个功能由函数FillRavAddress完成。原型是：
BOOL CMemLoadDll::FillRavAddress(void *pImageBase);
(6)根据DLL每个节的属性设置其对应内存页的读写属性。我这里做了简化，所有内存区域都设置成一样的读写属性。
(7)调用入口函数DllMain，完成初始化工作。这一步我一开始忽略了，所以总是发现自己加载的dll和LoadLibrary加载的dll有些不同
(我把整块内存区域保存到两个文件中进行比较，够晕的)。只是最近猜想到还需要这一步。
(8)保存dll的基地址（即分配的内存块起始地址）,用于查找dll的导出函数。从现在开始这个dll已经完全映射到了进程的虚拟地址空间，
可以使用它了。
(9)不需要dll的时候，释放所分配的虚拟内存。

二、要说明的几个问题

(1)目前CMemLoadDll仅仅针对win32 动态库，没有考虑mfc常规和扩展dll。
(2) 只考虑使用dll中的函数，对于导出类的dll，由于通常都是隐式链接，所以也没有考虑。导出变量的dll虽然也是隐式链接，
但是通过查找函数的方法也可 以找到该变量，不过在取值的时候一定要符合dll中对变量的定义，比如dll中导出的是一个int变量，
则得到该变量在dll中的地址后，需要强制转换成 int*指针，然后取值。
(3)查找函数的功能通过函数
FARPROC CMemLoadDll::MemGetProcAddress(LPCSTR lpProcName);
实现，参数是dll导出的函数（或者变量）的名字。这里必须注意函数名修饰，通常不加extern”C”的函数，
编译以后在dll中导出的都是修饰名，比如：
在dll头文件中: extern __declspec(dllexport) int nTestDll;
在.dll中的导出符号变成 ?nTestDll@@3HA
所以，为了能够找到我们需要的函数，必须在.h中添加extern “C”修饰。最好是给dll加一个def文件，里面明确给出每个函数的导出名字。
(4)PE中的内容比较多，有些细节没有考虑。比如CheckDataValide函数中没有考虑dll对操作系统版本的要求。
(5)PE文件中的节有很多种。可以从节表（或者叫做区块表）中一一找到。而且每个节的属性都不同。例如：
.text, .data, .rsrc, .crt等等。由于这个代码基于手头已有的pe文件资料，对于不熟悉的节，
在映射dll数据的时候没有考虑是否需要处理。
(6) 一开始把dll映射到进程的地址空间以后，我试图直接使用GetProcAddress查找函数。最初我认为LoadLibrary返回的 
HINSTANCE值是0x10000000，把它传递给GetProcAddress可以找到目标函数，而我也把dll映射到0x10000000这个 地址，
但是当我把这个值传递给GetProcAddress的时候，发现无法找到函数，用GetLastError得到错误码一看是无效句柄的错误，
这才 明白原来LoadLibrary在加载dll的时候，同时创建了一个句柄放入进程的句柄表，而我们要做这个工作是比较麻烦的，
所以只能自己写一个查找函 数。
(7)释放dll所占据的虚拟内存，原来我使用
VirtualFree((LPVOID)pImageBase, 0,MEM_FREE);
后来发现有问题，应该使用 VirtualFree((LPVOID)pImageBase, 0, MEM_RELEASE);
(8)MemGetProcAddress不仅支持通过函数名查找，还支持通过导出序号查找函数。例如下面的用法：
DLLFUNCTION fDll = (DLLFUNCTION)a.MemGetProcAddress((LPCTSTR)1);

*/


#pragma warning(disable : 4311)
#pragma warning(disable : 4312)


CMemLoadDll::CMemLoadDll()
{
    isLoadOk = FALSE;
    pImageBase = NULL;
    pDllMain = NULL;
}

CMemLoadDll::~CMemLoadDll()
{
    if (isLoadOk)
    {
        ASSERT(pImageBase != NULL);
        ASSERT(pDllMain != NULL);
        //脱钩，准备卸载dll
        pDllMain((HINSTANCE)pImageBase,DLL_PROCESS_DETACH,0);
        VirtualFree((LPVOID)pImageBase, 0, MEM_RELEASE);
    }
}

//MemLoadLibrary函数从内存缓冲区数据中加载一个dll到当前进程的地址空间，缺省位置0x10000000
//返回值： 成功返回TRUE , 失败返回FALSE
//lpFileData: 存放dll文件数据的缓冲区
//DataLength: 缓冲区中数据的总长度
BOOL CMemLoadDll::MemLoadLibrary(void* lpFileData, int DataLength)
{
    if (pImageBase != NULL)
    {
        return FALSE; //已经加载一个dll，还没有释放，不能加载新的dll
    }
    //检查数据有效性，并初始化
    if (!CheckDataValide(lpFileData, DataLength))return FALSE;

    //计算所需的加载空间
    int ImageSize = CalcTotalImageSize();

    if (ImageSize == 0) return FALSE;

    // 分配虚拟内存
    void *pMemoryAddress = VirtualAlloc((LPVOID)0x20000000/*0x10000000*/, ImageSize, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    if (pMemoryAddress == NULL)
    {
        return FALSE;
    }
    else
    {
        CopyDllDatas(pMemoryAddress, lpFileData); //复制dll数据，并对齐每个段
        //重定位信息
        if(pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress >0
            && pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size>0)
        {
            DoRelocation(pMemoryAddress);
        }
        //填充引入地址表
        if(!FillRavAddress(pMemoryAddress)) //修正引入地址表失败
        {
            VirtualFree(pMemoryAddress,0,MEM_RELEASE);
            return FALSE;
        }
        //修改页属性。应该根据每个页的属性单独设置其对应内存页的属性。这里简化一下。
        //统一设置成一个属性PAGE_EXECUTE_READWRITE
        unsigned long old;
        VirtualProtect(pMemoryAddress, ImageSize, PAGE_EXECUTE_READWRITE,&old);
    }
    //修正基地址
    pNTHeader->OptionalHeader.ImageBase = (DWORD)pMemoryAddress;

    //接下来要调用一下dll的入口函数，做初始化工作。
    pDllMain = (ProcDllMain)(pNTHeader->OptionalHeader.AddressOfEntryPoint +(DWORD) pMemoryAddress);
    BOOL InitResult = pDllMain((HINSTANCE)pMemoryAddress,DLL_PROCESS_ATTACH,0);
    if (!InitResult) //初始化失败
    {
        pDllMain((HINSTANCE)pMemoryAddress,DLL_PROCESS_DETACH,0);
        VirtualFree(pMemoryAddress,0,MEM_RELEASE);
        pDllMain = NULL;
        return FALSE;
    }

    isLoadOk = TRUE;
    pImageBase = (DWORD)pMemoryAddress;
    return TRUE;
}

//MemGetProcAddress函数从dll中获取指定函数的地址
//返回值： 成功返回函数地址 , 失败返回NULL
//lpProcName: 要查找函数的名字或者序号
FARPROC CMemLoadDll::MemGetProcAddress(LPCSTR lpProcName)
{
    if (pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0 ||
        pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size == 0)
        return NULL;

    if (!isLoadOk) return NULL;

    DWORD OffsetStart = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    DWORD Size = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

    PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pImageBase + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
    int iBase = pExport->Base;
    int iNumberOfFunctions = pExport->NumberOfFunctions;
    int iNumberOfNames = pExport->NumberOfNames; //<= iNumberOfFunctions
    LPDWORD pAddressOfFunctions = (LPDWORD)(pExport->AddressOfFunctions + pImageBase);
    LPWORD pAddressOfOrdinals = (LPWORD)(pExport->AddressOfNameOrdinals + pImageBase);
    LPDWORD pAddressOfNames = (LPDWORD)(pExport->AddressOfNames + pImageBase);

    int iOrdinal = -1;

    if (((DWORD)lpProcName & 0xFFFF0000) == 0) //IT IS A ORDINAL!
    {
        iOrdinal = (DWORD)lpProcName & 0x0000FFFF - iBase;
    }
    else //use name
    {
        int iFound = -1;

        for (int i=0;i < iNumberOfFunctions; i++)
        {
            char* pName= (char* )(pAddressOfNames[i] + pImageBase);
            if(strcmp(pName, lpProcName) == 0)
            {
                iFound = i; break;
            }
        }
        if (iFound >= 0)
        {
            iOrdinal = (int)(pAddressOfOrdinals[iFound]);
        }
    }

    if (iOrdinal < 0 || iOrdinal >= iNumberOfFunctions )
    {
        return NULL;
    }
    else
    {
        DWORD pFunctionOffset = pAddressOfFunctions[iOrdinal];
        if(pFunctionOffset > OffsetStart && pFunctionOffset < (OffsetStart+Size))//maybe Export Forwarding
            return NULL;
        else return (FARPROC)(pFunctionOffset + pImageBase);
    }

}

// 重定向PE用到的地址
void CMemLoadDll::DoRelocation( void *NewBase)
{
    /* 重定位表的结构：
    // DWORD sectionAddress, DWORD size (包括本节需要重定位的数据)
    // 例如 1000节需要修正5个重定位数据的话，重定位表的数据是
    // 00 10 00 00 14 00 00 00 xxxx xxxx xxxx xxxx xxxx 0000
    // ———– ———– —-
    // 给出节的偏移 总尺寸=8+6*2 需要修正的地址 用于对齐4字节
    // 重定位表是若干个相连，如果address 和 size都是0 表示结束
    // 需要修正的地址是12位的，高4位是形态字，intel cpu下是3
    */
    //假设NewBase是0x600000,而文件中设置的缺省ImageBase是0x400000,则修正偏移量就是0x200000
    DWORD Delta = (DWORD)NewBase - pNTHeader->OptionalHeader.ImageBase;

    //注意重定位表的位置可能和硬盘文件中的偏移地址不同，应该使用加载后的地址
    PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)NewBase
        + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

    while ((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0) //开始扫描重定位表
    {
        WORD *pLocData = (WORD *)((int)pLoc + sizeof(IMAGE_BASE_RELOCATION));
        //计算本节需要修正的重定位项（地址）的数目
        int NumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);
        for(int i=0 ; i < NumberOfReloc; i++)
        {
            if ((DWORD)(pLocData[i] & 0xF000) == 0x00003000) //这是一个需要修正的地址
            {
                // 举例：
                // pLoc->VirtualAddress = 0x1000;
                // pLocData[i] = 0x313E; 表示本节偏移地址0x13E处需要修正
                // 因此 pAddress = 基地址 + 0x113E
                // 里面的内容是 A1 ( 0c d4 02 10) 汇编代码是： mov eax , [1002d40c]
                // 需要修正1002d40c这个地址
                DWORD * pAddress = (DWORD *)((unsigned long)NewBase + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
                *pAddress += Delta;
            }
        }
        //转移到下一个节进行处理
        pLoc = (PIMAGE_BASE_RELOCATION)((DWORD)pLoc + pLoc->SizeOfBlock);
    }
}

//填充引入地址表
BOOL CMemLoadDll::FillRavAddress(void *pImageBase)
{
    // 引入表实际上是一个 IMAGE_IMPORT_DESCRIPTOR 结构数组，全部是0表示结束
    // 数组定义如下：
    //
    // DWORD OriginalFirstThunk; // 0表示结束，否则指向未绑定的IAT结构数组
    // DWORD TimeDateStamp;
    // DWORD ForwarderChain; // -1 if no forwarders
    // DWORD Name; // 给出dll的名字
    // DWORD FirstThunk; // 指向IAT结构数组的地址(绑定后，这些IAT里面就是实际的函数地址)
    unsigned long Offset = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress ;
    
    if (Offset == 0) return TRUE; //No Import Table
   
    PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((unsigned long) pImageBase + Offset);
    
    while (pID->Characteristics != 0)
    {
        PIMAGE_THUNK_DATA pRealIAT = (PIMAGE_THUNK_DATA)((unsigned long)pImageBase + pID->FirstThunk);
        PIMAGE_THUNK_DATA pOriginalIAT = (PIMAGE_THUNK_DATA)((unsigned long)pImageBase + pID->OriginalFirstThunk);
        
        //获取dll的名字
        int i = 0;
        char buf[256]; //dll name;
        BYTE* pName = (BYTE*)((unsigned long)pImageBase + pID->Name);

        for (; i < 256; i++)
        {
            buf[i] = pName[i];
            if (pName[i] == 0) break;
        }

        HMODULE hDll = GetModuleHandle(buf);
        if (hDll == NULL)
        {
            hDll = LoadLibrary(buf);
            if (hDll == NULL) return FALSE; //NOT FOUND DLL
        }
        
        //获取DLL中每个导出函数的地址，填入IAT
        //每个IAT结构是 ：
        // union { PBYTE ForwarderString;
        // PDWORD Function;
        // DWORD Ordinal;
        // PIMAGE_IMPORT_BY_NAME AddressOfData;
        // } u1;
        // 长度是一个DWORD ，正好容纳一个地址。
        for (i=0; ; i++)
        {
            if (pOriginalIAT[i].u1.Function == 0) break;

            FARPROC lpFunction = NULL;

            if (pOriginalIAT[i].u1.Ordinal & IMAGE_ORDINAL_FLAG) //这里的值给出的是导出序号
            {
                lpFunction = GetProcAddress(hDll, (LPCSTR)(pOriginalIAT[i].u1.Ordinal & 0x0000FFFF));
            }
            else //按照名字导入
            {
                //获取此IAT项所描述的函数名称
                PIMAGE_IMPORT_BY_NAME pByName = (PIMAGE_IMPORT_BY_NAME)
                    ((DWORD)pImageBase + (DWORD)(pOriginalIAT[i].u1.AddressOfData));
                // if(pByName->Hint !=0)
                // lpFunction = GetProcAddress(hDll, (LPCSTR)pByName->Hint);
                // else
                lpFunction = GetProcAddress(hDll, (char *)pByName->Name);
            }

            if (lpFunction != NULL) //找到了！
            {
                pRealIAT[i].u1.Function = (DWORD)(PDWORD)lpFunction;
            }
            else
            {
                return FALSE;
            }
        }

        //move to next
        pID = (PIMAGE_IMPORT_DESCRIPTOR)( (DWORD)pID + sizeof(IMAGE_IMPORT_DESCRIPTOR));
    }
    return TRUE;
}

//CheckDataValide函数用于检查缓冲区中的数据是否有效的dll文件
//返回值： 是一个可执行的dll则返回TRUE，否则返回FALSE。
//lpFileData: 存放dll数据的内存缓冲区
//DataLength: dll文件的长度
BOOL CMemLoadDll::CheckDataValide(void* lpFileData, int DataLength)
{
    //检查长度
    if (DataLength < sizeof(IMAGE_DOS_HEADER)) return FALSE;
    pDosHeader = (PIMAGE_DOS_HEADER)lpFileData; // DOS头
    //检查dos头的标记
    if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) return FALSE; //0x5A4D : MZ

    //检查长度
    if ((DWORD)DataLength < (pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS)) ) return FALSE;
    //取得pe头
    pNTHeader = (PIMAGE_NT_HEADERS)( (unsigned long)lpFileData + pDosHeader->e_lfanew); // PE头
    //检查pe头的合法性
    if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) return FALSE; //0x00004550 : PE00
    if ((pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL) == 0) //0x2000 : File is a DLL
        return FALSE;
    if ((pNTHeader->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0) //0×0002 : 指出文件可以运行
        return FALSE;
    if (pNTHeader->FileHeader.SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER)) return FALSE;

    //取得节表（段表）
    pSectionHeader = (PIMAGE_SECTION_HEADER)((int)pNTHeader + sizeof(IMAGE_NT_HEADERS));
    //验证每个节表的空间
    for (int i=0; i< pNTHeader->FileHeader.NumberOfSections; i++)
    {
        if ((pSectionHeader[i].PointerToRawData + pSectionHeader[i].SizeOfRawData) > (DWORD)DataLength) return FALSE;
    }
    return TRUE;
}

//计算对齐边界
int CMemLoadDll::GetAlignedSize(int Origin, int Alignment)
{
    return (Origin + Alignment - 1) / Alignment * Alignment;
}
//计算整个dll映像文件的尺寸
int CMemLoadDll::CalcTotalImageSize()
{
    int Size;
    if(pNTHeader == NULL)return 0;
    int nAlign = pNTHeader->OptionalHeader.SectionAlignment; //段对齐字节数

    // 计算所有头的尺寸。包括dos, coff, pe头 和 段表的大小
    Size = GetAlignedSize(pNTHeader->OptionalHeader.SizeOfHeaders, nAlign);
    // 计算所有节的大小
    for (int i=0; i < pNTHeader->FileHeader.NumberOfSections; ++i)
    {
        //得到该节的大小
        int CodeSize = pSectionHeader[i].Misc.VirtualSize ;
        int LoadSize = pSectionHeader[i].SizeOfRawData;
        int MaxSize = (LoadSize > CodeSize)?(LoadSize):(CodeSize);

        int SectionSize = GetAlignedSize(pSectionHeader[i].VirtualAddress + MaxSize, nAlign);
        if (Size < SectionSize)
            Size = SectionSize; //Use the Max;
    }
    return Size;
}
//CopyDllDatas函数将dll数据复制到指定内存区域，并对齐所有节
//pSrc: 存放dll数据的原始缓冲区
//pDest:目标内存地址
void CMemLoadDll::CopyDllDatas(void* pDest, void* pSrc)
{
    // 计算需要复制的PE头+段表字节数
    int HeaderSize = pNTHeader->OptionalHeader.SizeOfHeaders;
    int SectionSize = pNTHeader->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
    int MoveSize = HeaderSize + SectionSize;
    //复制头和段信息
    memmove(pDest, pSrc, MoveSize);

    //复制每个节
    for (int i = 0; i < pNTHeader->FileHeader.NumberOfSections; ++i)
    {
        if (pSectionHeader[i].VirtualAddress == 0 || pSectionHeader[i].SizeOfRawData == 0) continue;
        // 定位该节在内存中的位置
        void *pSectionAddress = (void *)((unsigned long)pDest + pSectionHeader[i].VirtualAddress);
        // 复制段数据到虚拟内存
        memmove((void *)pSectionAddress,
            (void *)((DWORD)pSrc + pSectionHeader[i].PointerToRawData),
            pSectionHeader[i].SizeOfRawData);
    }

    //修正指针，指向新分配的内存
    //新的dos头
    pDosHeader = (PIMAGE_DOS_HEADER)pDest;
    //新的pe头地址
    pNTHeader = (PIMAGE_NT_HEADERS)((int)pDest + (pDosHeader->e_lfanew));
    //新的节表地址
    pSectionHeader = (PIMAGE_SECTION_HEADER)((int)pNTHeader + sizeof(IMAGE_NT_HEADERS));
    return ;
}

#pragma warning(default : 4311)
#pragma warning(default : 4312)
