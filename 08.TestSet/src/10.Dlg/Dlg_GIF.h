
#pragma once
#include "UI/Ctrl/XTRichEdit.h"
#include "UI/Html/DemoView.h"
#include "UI/GIF.h"



UINT GifThread(LPVOID gifDC);

class CDlg_GIF : public CDialog
{
    DECLARE_DYNAMIC(CDlg_GIF)

public:
    CDlg_GIF(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlg_GIF();

    enum { IDD = IDD_DLG_GIF };

private:
    CDemoView	m_Browser;
    CXTRichEdit	m_RichEdit;

    CGIF		m_gif;

    KEY_AREA	*m_pKeyFile[5];

protected:
    virtual BOOL OnInitDialog();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    LRESULT OnHtmlClick(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedGifBtnGif();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnPaint();	
    afx_msg void OnBnClickedGifBtnCallJavascript();
};
