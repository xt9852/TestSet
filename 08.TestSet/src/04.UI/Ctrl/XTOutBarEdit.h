
#pragma once

class CXTOuBarEdit : public CEdit
{
public:
	CXTOuBarEdit();

public:
	BOOL	m_bEscapeKey;
	CString m_strText;
	WPARAM	m_msgSend;
	bool	m_bNoDown;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PostNcDestroy();

public:
	int m_nIndex;
	virtual ~CXTOuBarEdit();

protected:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};
