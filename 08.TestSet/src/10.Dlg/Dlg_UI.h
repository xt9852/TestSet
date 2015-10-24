#pragma once
#include "resource.h"
#include "UI/Ctrl/XTDC.h"
#include "UI/Ctrl/XTColorPicker.h"
#include "UI/Ctrl/XTMenu.h"
#include "UI/Ctrl/XTOutBarCtrl.h"
#include "UI/Ctrl/XTToolBar.h"
#include "UI/Ctrl/XTCPUStatus.h"
#include "UI/Ctrl/XTRichEdit.h"
#include "UI/Html/DemoView.h"
#include "UI/GIF.h"


class CDlg_Skin_Dlg1;
class CDlg_Skin_Dlg2;
class CDlg_Skin_Dlg3;
class CTaskbarNotifier;

class CDlg_UI : public CDialog
{
    DECLARE_DYNAMIC(CDlg_UI)

public:
    CDlg_UI(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_UI();

    // 对话框数据
    enum { IDD = IDD_DLG_UI };

private:

    HMODULE				m_hResource;

    CXTColorPicker		m_btnColor;
    COLORREF			m_rgbColor;

    CDlg_Skin_Dlg1		*m_pSkinDlg1;
    CDlg_Skin_Dlg2		*m_pSkinDlg2;
    CDlg_Skin_Dlg3		*m_pSkinDlg3;
    CTaskbarNotifier	*m_pSkinDlg4;

    //---------------------------------------------------------------

    CXTMenu				m_menu;
    CXTMenu				m_menuSubIcon;
    CXTMenu				m_menuSubColor;

    //---------------------------------------------------------------

    CXTDC				m_xtDC;
    HDC					m_hDC;
    HDC					m_hCompDC;
    HDC					m_hBmpDC;

	BOOL				m_bShowImage;
    HGLOBAL				m_hGlobal;
    HBITMAP				m_hBmp;
	BITMAP				m_BmpInfo;

    CXTOutBarCtrl		m_wndOutlookBar;
    CXTToolbar			m_wndToolBar;
    CToolBarComboBoxButton *pComboBox;
    CToolBarEditButton	*pEdit;

    CStatusBar			m_StatusBar;
    CXTCPUStatus		m_CPUStatus;
    //CListCtrl			m_FastList;

	CDemoView			m_Browser;
	CXTRichEdit			m_RichEdit;

	CGIF				m_gif;

	KEY_AREA			*m_pKeyFile[5];

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	BOOL SetJpg(LPCTSTR pFileName, HGLOBAL &hGlobal, HBITMAP &hBmp);
	LRESULT OnHtmlClick(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnToolBarCommand();
    afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);   
    afx_msg void OnLvnGetdispinfoUiList(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedDlg1();
    afx_msg void OnBnClickedDlg2();
    afx_msg void OnBnClickedDlg3();
    afx_msg void OnBnClickedDlg4();
    afx_msg void OnBnClickedSongword();
    afx_msg void OnBnClickedShowWord();
    afx_msg void OnBnClickedShowJpg();
    afx_msg void OnBnClickedLeft();
    afx_msg void OnBnClickedRight();
    afx_msg void OnBnClickedScreenCap();
	afx_msg void OnBnClickedMessageBox();
	afx_msg void OnBnClickedPng();
	afx_msg void OnBnClickedGif();
	afx_msg void OnBnClickedJS();
};
