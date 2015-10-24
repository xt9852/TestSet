#pragma once



class CXTDC;

class CXTBackForth
{
public:
	CXTBackForth();
	virtual ~CXTBackForth();

private:
	HDC		m_hDC;		// 程序显示DC，窗体DC
	HDC		m_hCompDC;	// 有兼容位图的DC
	HDC		m_hBmpDC;	// 背景位图DC
	
	POINT	m_Pt;
	POINT	m_SrcLeftPt;
	POINT	m_SrcMedPt;
	POINT	m_SrcRightPt;
	POINT	m_BckLeftPt;
	POINT	m_BckMedPt;
	POINT	m_BckRightPt;
	SIZE	m_ItemSz;
	int		m_nAllItemCount;
	int		m_nItemCount;
	int		m_nInterval;

	int		m_nCurLeftPos;
	int		m_nCurRightPos;
	bool	m_bToRight;
	bool	m_bLeftOk;
	bool	m_bRightOk;

	UINT	m_nThreadId;
	HWND	m_hWnd;
	
	enum {LEFT, MED, RIGHT};

	static unsigned __stdcall DrawProgressThread(LPVOID pthis);
	

	void DrawDefaultImage(void);
	void DrawSuccessImage(void);

public:
	void SetDlgWnd(HWND hWnd) {m_hWnd = hWnd; }
	bool Initial(int x, int y, int nAllItemCount, int nItemCount, int nItemcx, 
		int nItemcy, int nInterval, int sx, int sy, CXTDC *pDBuffDC);
	
	bool Start(void);
	void Stop(void);
	void Success(void);
	
	void SetItem(int nItemId, int nItemType);
	void ResetItem(int nItemId);
};


