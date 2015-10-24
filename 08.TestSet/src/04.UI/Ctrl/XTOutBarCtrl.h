
#pragma once
#include <afxcoll.h>
/*
#include "XTMenu.h"


#define ID_OUTBAR_SMALLICON			50000
#define ID_OUTBAR_LARGEICON			50001
#define ID_OUTBAR_RENAMEITEM		50002
#define ID_OUTBAR_REMOVEITEM		50003
#define STR_OUTBAR_SMALLICON		_T("小图标(&L)")
#define STR_OUTBAR_LARGEICON		_T("大图标(&S)")
#define STR_OUTBAR_RENAMEITEM		_T("重命名(&R)")
#define STR_OUTBAR_REMOVEITEM		_T("删除(&D)")

#define ID_OUTBAR_ADDGROUP			50005
#define ID_OUTBAR_DELGROUP			50006
#define ID_OUTBAR_RENAMEGROUP		50007
#define STR_OUTBAR_ADDGROUP		    _T("添加分组(&I)")
#define STR_OUTBAR_DELGROUP		    _T("删除分组(&D)")
#define STR_OUTBAR_RENAMEGROUP		_T("重命名组(&R)")

#define ID_OUTBAR_DELUSER			50008
#define STR_OUTBAR_DELUSER		    _T("从该组删除(&D)")

#define ID_OUTBAR_BROADFILE         50009
#define STR_OUTBAR_BROADFILE		_T("群发文件(&S)")


#define ID_OUTBAR_ADDUSER           50010
*/

#define NM_OB_ITEMCLICK				1
#define NM_OB_ITEMDBCLICK			2
#define NM_OB_ONLABELENDEDIT		3
#define NM_OB_ONGROUPENDEDIT		4
#define NM_OB_DRAGITEM				5
#define NM_FOLDERCHANGE				6


struct OUTBAR_INFO 
{
    const char *pszText;
    int         nFolder;
	int			nIndex;	
    int         nDragFromFolder;
    int         nDragToFolder;
	int			nDragFrom;
	int			nDragTo;
    int         nData;
};

typedef struct _tagActItem
{
    int         nFolder;
    int         nIndex;
}ACTITEM, *PACTITEM;

class CXTMenu;

class CXTOutBarCtrl : public CWnd
{
	DECLARE_DYNCREATE(CXTOutBarCtrl)

public:
	CXTOutBarCtrl();
    virtual ~CXTOutBarCtrl();

	enum {  fSmallIcon = 1 << 0, fLargeIcon = 1 << 1, fEditGroups = 1 << 2, fEditItems = 1 << 3,
			fRemoveGroups = 1 << 4, fRemoveItems = 1 << 5, fAddGroups = 1 << 6, 
			fDragItems = 1 << 7, fAnimation = 1 << 8, fSelHighlight = 1 << 9};

	enum { ircIcon = 1, ircLabel = 2, ircAll = 3 };

public:
	COLORREF	m_crBackGroundColor, m_crBackGroundColor1;
	COLORREF	m_crTextColor;
	COLORREF	m_cr3dFace, m_crLightBorder, m_crHilightBorder, m_crShadowBorder, m_crDkShadowBorder;
	int			m_nFolderHeight;

	int			m_xSmallIconLabelOffset, m_yLargeIconLabelOffset;
	int			m_ySmallIconSpacing, m_yLargeIconSpacing;
	int			m_xLeftMargin, m_yTopMargin;

	CRect		m_rcUpArrow, m_rcDownArrow;
    bool		m_bUpArrow, m_bDownArrow, m_bUpPressed, m_bDownPressed;	
	bool		m_bLooping;

	int			m_nHitInternal1, m_nHitInternal2;
	int			m_nAnimationTickCount;
	int			m_nLastSel;
	int			m_nSelAnimTiming;
	int			m_nSelAnimCount;
	int			m_nSelFolder;

	DWORD		m_dwFlags;
	CPtrArray	m_arFolder;

	int			m_nLastFolderHighlighted;
	int			m_nLastSelectedFolder;
	int			m_nFirstItem;
	int			m_nLastItemHighlighted;
	bool		m_bPressedHighlight;
	int			m_nLastDragItemDraw, m_nLastDragItemDrawType;

	class CBarItem
	{
	public:
		CBarItem(const char *pszName, const int nImage, DWORD dwData);
		virtual  ~CBarItem();
		int			m_nImage;
		char		*m_pszItem;
		DWORD		m_dwData;
	};

	class CBarFolder
	{
	public:
		CBarFolder(const char *pszName, DWORD dwData);
		virtual  ~CBarFolder();
		int GetItemCount();
		int InsertItem(int nIndex, const char *pszText, const int nImage, const DWORD dwData);
		char		*m_pszName;
		DWORD		m_dwData;
		CImageList	*m_pLargeImageList;
		CImageList	*m_pSmallImageList;
		CPtrArray	m_arItems;
		CWnd		*m_pWndChild;
	};

	CImageList		*m_pLargeImageList;
	CImageList		*m_pSmallImageList;

	HCURSOR			m_hHandCursor;
	HCURSOR			m_hDragCursor;
	HCURSOR			m_hNoDragCursor;

	CPen			*m_pBlackPen;
/*
	CXTMenu			m_mFolder;
    CXTMenu			m_mFolder1;
	CXTMenu			m_mItem;
    CXTMenu			m_mItem1;
*/
public:
	enum { htNothing = -1, htFolder, htItem, htUpScroll, htDownScroll};

public:
    void PaintItems(CDC *pDC, const int nFolder, CRect rc);
    void PaintItemsEx(CDC *pDC, const int nFolder, CRect rc);
    void DrawItem(CDC * pDC, const int nFolder, CRect rc, const int nIndex, const bool bOnlyImage = false);
    void DrawDragArrow(CDC *pDC, const int nFrom, const int nTo);
	void DrawAnimItem(const int xoffset, const int yoffset, const int nIndex);
	void DrawActItem(const int xoffset, const int yoffset, const int nFolder, const int nIndex);
    
    void SetAnimationTickCount(const int nValue) { m_nAnimationTickCount = nValue; };
    int  GetAnimationTickCount() { return m_nAnimationTickCount; };
    void SetAnimSelHighlight(const int nTime);
    
	int  AddFolderBar(const char *pszName, CWnd *pWndChild, const DWORD dwData = 0);    
    int  AddFolder(const char *pszName, const DWORD dwData);
    int  InsertItem(const int nFolder, const int nIndex, const char *pszText, const int nImage = -1, const DWORD dwData = 0);
    void RemoveItem(const int nFolder, const int nIndex);
    void RemoveFolder(const int nIndex);
    void StartItemEdit(const int nIndex);    
    void StartGroupEdit(const int nIndex);
    void HighlightItem(const int nIndex, const bool bPressed = false);
    void HighlightFolder(const int index);    
    int  GetSelFolder() const;	
    void SetSelFolder(const int nIndex, bool bAnimate = true);

    int  GetFolderCount() const;
    int  GetItemCount(int nIndex = -1) const;
    
    void AnimateFolderScroll(const int nFrom, const int nTo);

    DWORD   GetFlag() const;    

    DWORD   GetFolderData(int nFolder = -1);
    CWnd*   GetFolderChild(int nFolder = -1);    
    bool    GetFolderRect(const int nIndex, CRect &rect) const;
    CString GetItemText(const int nIndex);
    int     GetItemImage(const int nIndex) const;
    DWORD   GetItemData(const int nIndex) const;    
    CSize   GetItemSize(const int nFolder, const int nIndex, const int nType);
    void    GetItemRect(const int nFolder, const int nIndex, CRect &rect);

    void SetFolderData(const int nIndex, DWORD dwData);
    void SetFolderText(const int nIndex, const char *pszText);
    void SetItemText(const int nIndex, const char *pszText);
    void SetItemImage(const int nIndex, const int nImage);
    void SetItemData(const int nIndex, const DWORD dwData);

    CImageList * SetImageList(CImageList *pImageList, int nImageList);
    CImageList * SetFolderImageList(const int nFolder, CImageList *pImageList, int nImageList);
    CImageList * GetImageList(CImageList *pImageList, int nImageList);
    CImageList * GetFolderImageList(const int nIndex, const bool bSmall) const;

    int  GetDragItemRect(const int nIndex, CRect &rect);
	bool IsValidItem(const int index, const int nFolder =  -1) const;
	void GetLabelRect(const int nFolder, const int nIIndex, CRect &rect);
	void GetIconRect(const int nFolder, const int nIIndex, CRect &rect);
    void GetVisibleRange(const int nFolder, int &nFirst, int &nLast);	
	void GetInsideRect(CRect &rect) const;
	int  GetCountPerPage() const;
    void SetSmallIconView(const bool bSet);
    bool IsSmallIconView() const;
	int  HitTestEx(const CPoint &point, int &nIndex);
	void ModifyFlag(const DWORD &dwRemove, const DWORD &dwAdd, const UINT nRedraw = 0);

    BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, 
		const DWORD dwFlag = fDragItems|fEditGroups|fEditItems|fRemoveGroups|fRemoveItems|fAddGroups|fAnimation|fSelHighlight);

    CArray<ACTITEM, ACTITEM> m_arActiveItem;

	void StartActiveItem(DWORD dwFolderIndex, DWORD dwUserIndex);
	void StopActiveItem(DWORD dwFolderIndex, DWORD dwUserIndex);

    void AddMenu(DWORD dwId, LPCTSTR psName);
    void ModMenu(DWORD dwId, LPCTSTR psName);
    void DelMenu(DWORD dwId);

protected:
	void DrawFolder(CDC *pDC, const int nIndex, CRect rect, const bool bSelected);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg long OnEndLabelEdit(WPARAM wParam, LPARAM lParam);
/*	afx_msg void OnOutBarLargeicon();
	afx_msg void OnUpdateOutBarLargeicon(CCmdUI* pCmdUI);
	afx_msg void OnOutBarSmallicon();
	afx_msg void OnUpdateOutBarSmallicon(CCmdUI* pCmdUI);
	afx_msg void OnOutBarRemoveitem();
	afx_msg void OnUpdateOutBarRemoveitem(CCmdUI* pCmdUI);
	afx_msg void OnOutBarRenameitem();
	afx_msg void OnUpdateOutBarRenameitem(CCmdUI* pCmdUI);	
	afx_msg void OnOutBarDelFriend();
	afx_msg void OnOutBarStartChat();
    afx_msg void OnOutBarAddGroup();
    afx_msg void OnOutBarDelGroup();
    afx_msg void OnOutBarRenameGroup();
    afx_msg void OnAddUserToFloder(UINT nCmd);
    afx_msg void OnDelUserFromFloder();
    afx_msg void OnBroadFile();
*/	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()	
};
