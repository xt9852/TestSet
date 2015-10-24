
#pragma once

#define CPN_SELCHANGE        WM_USER + 1001        // Color Picker Selection change
#define CPN_DROPDOWN         WM_USER + 1002        // Color Picker drop down
#define CPN_CLOSEUP          WM_USER + 1003        // Color Picker close up
#define CPN_SELENDOK         WM_USER + 1004        // Color Picker end OK
#define CPN_SELENDCANCEL     WM_USER + 1005        // Color Picker end (cancelled)

// To hold the colors and their names
typedef struct
{
	COLORREF	crColor;
	TCHAR *		szName;
	int			nSystemColor;
}
ColorTableEntry;


// CXtColourPopup window
class CXTColorPopup : public CWnd
{
public:
	CXTColorPopup();

	CXTColorPopup(CWnd * pParentWnd,
		CPoint p,
		COLORREF crColor = RGB(255,255,255),
		COLORREF * pCustomColors = NULL,
		int nSelectedRow = -1,
		int nSelectedCol = -1,
		LPCTSTR szCustomText = NULL);

	virtual ~CXTColorPopup();

public:
	BOOL Create(CPoint p, COLORREF crColor, CWnd * pParentWnd,
		LPCTSTR szCustomText = NULL);

	virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:
	void Init();
	BOOL GetCellRect(int row, int col, const LPRECT & rect);
	void SetWindowSize();
	void CreateToolTips();
	void ChangeSelection(int row, int col);
	void EndSelection(int nMessage);
	void DrawCell(CDC * pDC, int row, int col);
	COLORREF GetColor(int row, int col)
	{
		return (0x00FFFFFF & m_crColors[row * m_nNumColumns + col].crColor);
	}
	void SetColor(int row, int col, COLORREF rgb)
	{
		int nColorId = row * m_nNumColumns + col;

		m_crColors[nColorId].crColor = rgb;

		CRect rect;
		if (!GetCellRect(row, col, rect))
			return;

		CString strColorName(GetColorName(row, col));
		strColorName.AppendFormat(_T(",RGB=%06X"), GetColor(row, col));

		m_ToolTip.DelTool(this, nColorId);
		VERIFY(m_ToolTip.AddTool(this, strColorName, rect, nColorId));
	}
	LPCTSTR GetColorName(int row, int col)
	{
		return m_crColors[row * m_nNumColumns + col].szName;
	}

protected:
	static ColorTableEntry m_crColors[];
	COLORREF *     m_pCustomColors;
	int            m_nNumColors;
	int            m_nNumColumns, m_nNumRows;
	int            m_nBoxSize, m_nMargin;
	int            m_nCurrentRow, m_nCurrentCol;
	int            m_nSelectedRow, m_nSelectedCol;
	BOOL           m_bShowCustom;
	CString        m_strCustomText;
	CRect          m_TextRect, m_WindowRect, m_DividerRect;
	CFont          m_Font;
	COLORREF       m_crInitialColor, m_crColor;
	CToolTipCtrl   m_ToolTip;
	CWnd *         m_pParent;

protected:
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};

//------------------------------------------------------------------------------------------------------------
// CXtColorPicker window
void AFXAPI DDX_ColorPicker(CDataExchange * pDX, int nIDC, COLORREF & crColor);
void AFXAPI DDX_ColorPickerCustom(CDataExchange * pDX, int nIDC, CString & strCustomColors);

class CXTColorPicker : public CButton
{
	DECLARE_DYNCREATE(CXTColorPicker);
public:
	CXTColorPicker();
	virtual ~CXTColorPicker();

public:
	int m_nSelectedRow, m_nSelectedCol;
	void SetColor(COLORREF crColor);
	COLORREF GetColor();
	void SetCustomColors(COLORREF * pCustomColors);
	void GetCustomColors(COLORREF * pCustomColors);
	void SetCustomColors(LPCTSTR lpszCustomColors);
	CString GetCustomColors();

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();

	CSize GetArrowSize();

protected:
	BOOL	 m_bTrackSelection;
	COLORREF m_crColor;
	COLORREF m_crEnabledColor;
	COLORREF m_CustomColors[16];
	CRect    m_ArrowRect;

	COLORREF m_DefaultColor;
	BOOL	 m_bPopupActive;

protected:
	afx_msg BOOL OnClicked();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg LONG OnSelEndOK(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSelEndCancel(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSelChange(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

