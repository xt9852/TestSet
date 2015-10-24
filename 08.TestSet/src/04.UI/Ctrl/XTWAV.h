#pragma once



class CXTEdit : public CEdit
{
	DECLARE_DYNAMIC(CXTEdit)

public:
	CXTEdit();
	virtual ~CXTEdit();

protected:
	COLORREF	m_clrBkg;
	HBRUSH		m_hBrush;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void SetBkgColor(COLORREF clrBkg);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};


