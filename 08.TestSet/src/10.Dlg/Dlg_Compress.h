
#pragma once
#include "resource.h"

typedef CMap<CString, LPCTSTR, CString, CString> MAP_CODE;


class CDlg_Compress : public CDialog
{
    DECLARE_DYNAMIC(CDlg_Compress)

public:
    CDlg_Compress(CWnd* pParent = NULL);
    virtual ~CDlg_Compress();

    enum { IDD = IDD_DLG_COMPRESS };

	DWORD		m_dwTimeD;
	DWORD		m_dwTimeDown;
	DWORD		m_dwTimeUp;
	CString		m_strCode;

	MAP_CODE	m_mapCode;
	BOOL		m_bDown;
	int			m_nLen;
	void Down(void);

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnCompress();
    afx_msg void OnBnClickedBtnUncompress();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	afx_msg void OnBnClickedCompressBtnMors();
	afx_msg void OnBnClickedCompressBtnUnmors();
};
