
#pragma once
#include "richole.h"
#include "comdef.h"

//---------------------------------------------------------------------------------
/*
WINOLEAPI  CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit);
#import "D:\\Program Files\\Tencent\\TM\\TMDLLS\\ImageOle.dll" named_guids
using namespace ImageOleLib;
*/
//---------------------------------------------------------------------------------



class _AFX_RICHEDITEX_STATE
{
public:
    _AFX_RICHEDITEX_STATE();
    virtual ~_AFX_RICHEDITEX_STATE();
    HINSTANCE m_hInstRichEdit20 ;
};


class CXTRichEdit : public CRichEditCtrl
{
public:
	CXTRichEdit();
	virtual ~CXTRichEdit();

	DECLARE_MESSAGE_MAP()

private:
	RECT m_Rect;

public:
	virtual BOOL Create(DWORD in_dwStyle, const RECT& in_rcRect, CWnd* in_pParentWnd, UINT in_nID);
	virtual BOOL CreateEx1(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam /* = NULL */);
	void InitSettings();
	//void InsertFace(CString strPicPath);	
	//int  GetGifCount(void);
	//bool GetGifFileName(int nIndex, int &nPos, CString &strGifName);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnEnMsgfilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
