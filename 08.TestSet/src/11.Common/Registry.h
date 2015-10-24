//
// Registry.h
//

#pragma once

class CRegistry 
{
// Construction
public:
	CRegistry();
	~CRegistry();
	
// Operations
public:
	CString GetString(LPCTSTR pszSection, LPCTSTR pszName, LPCTSTR pszDefault = NULL);
	int		GetInt(LPCTSTR pszSection, LPCTSTR pszName, int nDefault = 0);
	DWORD	GetDword(LPCTSTR pszSection, LPCTSTR pszName, DWORD dwDefault = 0);
	double	GetFloat(LPCTSTR pszSection, LPCTSTR pszName, double fDefault = 0.0f);
	CString GetPath( void );
public:
	BOOL	SetString(LPCTSTR pszSection, LPCTSTR pszName, LPCTSTR pszValue);
	BOOL	SetInt(LPCTSTR pszSection, LPCTSTR pszName, int nValue);
	BOOL	SetRealInt(LPCTSTR pszSection, LPCTSTR pszName, int  nValue);
	BOOL    SetRealString(LPCTSTR pszSection, LPCTSTR pszName, LPCTSTR pszValue);

// Implementation
protected:
	void	DisplayErrorMessageBox(DWORD nErrorCode);
};
