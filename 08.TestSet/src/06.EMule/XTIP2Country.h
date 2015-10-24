
#pragma once
#include <atlcoll.h>

typedef struct _tagCountry
{
    INT         nBegin;
    BYTE        byCount;
    SHORT		shFlagIndex;
}COUNTRY;


typedef struct _tagIPRange
{
	DWORD		dwIpStart;
	DWORD		dwIpEnd;
	DWORD		dwCityOffset;
	COUNTRY		*pCountry;	
}IPRANG;

class CXTIP2Country
{
public:
	CXTIP2Country();
	~CXTIP2Country();

private:
	char								*m_pszFile;
	IPRANG								*m_pRange;
	COUNTRY								*m_pCountry;

	HWND								m_hWnd;
	CImageList							m_CountryFlagImageList;

    CString                             m_strCountry;   // 国家名
    CString                             m_strProvince;  // 省名

	CRBMap<DWORD, IPRANG*>						m_IpRangeMap;
	CMap<CString, LPCTSTR, COUNTRY*, COUNTRY*>	m_CountryMap;

	static unsigned __stdcall IP2CountryThread(LPVOID pthis);	
	bool LoadCountryFlagLib();
	bool LoadFromFile();
	bool AddIPRange(DWORD dwIpFrom, DWORD dwIpTo, CString &strCountryName, DWORD dwCityOffset);
	void GetCountryInfo(void);

public:
	CImageList* GetFlagImageList() {return &m_CountryFlagImageList;}
	void GetCountryFromIP(DWORD dwIP, WORD &wFlag, CString &strAddr);
	void SetOwner(HWND hWnd);
};
